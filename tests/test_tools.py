"""Tests for tools/firmware.py and tools/api-test.py. Run: python -m pytest tests"""
import importlib.util
import json
import sys
import threading
from http.server import BaseHTTPRequestHandler, HTTPServer
from pathlib import Path
import pytest
TOOLS = Path(__file__).resolve().parent.parent / "tools"
FIRMWARE = TOOLS.parent / "firmware"
def load(name: str, filename: str):
    spec = importlib.util.spec_from_file_location(name, TOOLS / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module
firmware = load("firmware_tool", "firmware.py")
api_test = load("api_test_tool", "api-test.py")
def active_lines(source: str) -> list[str]:
    return [ln.strip() for ln in source.splitlines() if ln.strip() and not ln.strip().startswith("//")]
class TestPatchPins:
    def source(self) -> str:
        return (FIRMWARE / "firmware-main.ino").read_text(encoding="utf-8")
    def test_devkit_sets_v1_pins(self):
        out = firmware.patch_pins(self.source(), firmware.BOARDS["devkit"])
        active = active_lines(out)
        assert "#define I2C_SDA 21" in active
        assert "#define I2C_SCL 22" in active
        assert "const int servoPins[8] = {15, 2, 23, 19, 4, 16, 17, 18};" in active
    def test_s2mini_keeps_repo_defaults(self):
        out = firmware.patch_pins(self.source(), firmware.BOARDS["s2mini"])
        active = active_lines(out)
        assert "#define I2C_SDA 33" in active
        assert "#define I2C_SCL 35" in active
        assert "const int servoPins[8] = {1, 2, 4, 6, 8, 10, 13, 14};" in active
    def test_exactly_one_definition_of_each_remains(self):
        out = firmware.patch_pins(self.source(), firmware.BOARDS["devkit"])
        assert out.count("#define I2C_SDA") == 1
        assert out.count("const int servoPins[8]") == 1
    def test_does_not_touch_other_lines(self):
        src = self.source()
        out = firmware.patch_pins(src, firmware.BOARDS["devkit"])
        def non_pin(text):
            return [ln for ln in text.splitlines()
                    if not any(p.match(ln) for p in firmware.PIN_LINE_PATTERNS.values())]
        assert non_pin(out) == non_pin(src)
    def test_missing_servo_pins_raises(self):
        with pytest.raises(firmware.ToolError):
            firmware.patch_pins("void setup() {}\n", firmware.BOARDS["devkit"])
    def test_motor_tester_is_patched(self):
        src = firmware.MOTOR_TESTER.read_text(encoding="utf-8")
        out = firmware.patch_pins(src, firmware.BOARDS["devkit"])
        assert out.count("const int servoPins[8]") == 1
        assert "{15, 2, 23, 19, 4, 16, 17, 18}" in out
class TestPorts:
    def test_parse_and_detect_esp32(self):
        raw = json.dumps(
            {
                "detected_ports": [
                    {"port": {"address": "COM3", "protocol_label": "Serial Port"}},
                    {
                        "port": {
                            "address": "COM7",
                            "protocol_label": "Serial Port (USB)",
                            "properties": {"vid": "0x10c4", "pid": "0xEA60"},
                        }
                    },
                ]
            }
        )
        ports = firmware.parse_ports(raw)
        assert [firmware.is_esp32_usb(p) for p in ports] == [False, True]
    def test_parse_accepts_bare_list(self):
        assert firmware.parse_ports('[{"port": {"address": "COM1"}}]') == [{"address": "COM1"}]
    def test_empty_output(self):
        assert firmware.parse_ports("{}") == []
    def test_invalid_json_raises_tool_error(self):
        with pytest.raises(firmware.ToolError, match="invalid JSON"):
            firmware.parse_ports("not json")
    def test_null_properties_is_not_esp32(self):
        assert firmware.is_esp32_usb({"address": "COM1", "properties": None}) is False
class TestFindCli:
    def test_explicit_path_wins(self):
        assert firmware.find_cli("/x/arduino-cli") == "/x/arduino-cli"
    def test_missing_cli_raises(self, monkeypatch):
        monkeypatch.delenv("ARDUINO_CLI", raising=False)
        monkeypatch.setattr(firmware.shutil, "which", lambda _: None)
        with pytest.raises(firmware.ToolError):
            firmware.find_cli(None)
class MockRobot(BaseHTTPRequestHandler):
    commands: list = []
    def log_message(self, *args):
        pass
    def reply(self, payload, code=200):
        data = json.dumps(payload).encode()
        self.send_response(code)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(data)))
        self.end_headers()
        self.wfile.write(data)
    def do_GET(self):
        if self.path == "/api/status":
            self.reply({"currentCommand": "stop", "currentFace": "default"})
        else:
            self.reply({}, 404)
    def do_OPTIONS(self):
        self.send_response(204)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Content-Length", "0")
        self.end_headers()
    def do_POST(self):
        length = int(self.headers.get("Content-Length", 0))
        raw = self.rfile.read(length).decode()
        assert '"command": "' in raw or '"face": "' in raw
        MockRobot.commands.append(json.loads(raw))
        self.reply({"status": "ok"})
@pytest.fixture
def robot(monkeypatch):
    monkeypatch.setattr(api_test, "SETTLE_SECONDS", 0)
    MockRobot.commands = []
    server = HTTPServer(("127.0.0.1", 0), MockRobot)
    thread = threading.Thread(target=server.serve_forever, daemon=True)
    thread.start()
    yield f"127.0.0.1:{server.server_port}"
    server.shutdown()
    server.server_close()
class TestApiTest:
    def test_default_run_does_not_move(self, robot):
        assert api_test.main(["--host", robot]) == 0
        assert MockRobot.commands == [{"face": "happy"}]
    def test_move_sends_stand_wave_stop(self, robot):
        assert api_test.main(["--host", robot, "--move"]) == 0
        sent = [c.get("command") for c in MockRobot.commands]
        assert sent == [None, "stand", "wave", "stop"]
    def test_custom_command_then_stop(self, robot):
        assert api_test.main(["--host", robot, "--command", "moon"]) == 0
        assert [c.get("command") for c in MockRobot.commands][-2:] == ["moon", "stop"]
    def test_unreachable_robot_returns_error(self, capsys):
        assert api_test.main(["--host", "127.0.0.1:1"]) == 1
        assert "cannot reach" in capsys.readouterr().err
class TestCliCommands:
    """Drive the subcommands with arduino-cli replaced by a recorder."""
    @pytest.fixture
    def calls(self, monkeypatch):
        recorded = []
        recorded_panel = self.recorded_panel = []
        def fake_run_cli(cli, *args, capture=False):
            recorded.append(args)
            return self.ports_json if capture else ""
        self.ports_json = '{"detected_ports": []}'
        monkeypatch.setattr(firmware, "run_cli", fake_run_cli)
        monkeypatch.setattr(firmware, "refresh_panel_header", lambda: recorded_panel.append(1))
        monkeypatch.setattr(firmware, "find_cli", lambda explicit: "arduino-cli")
        return recorded
    def test_setup_installs_core_and_pinned_libs(self, calls):
        assert firmware.main(["setup"]) == 0
        assert ("core", "install", "esp32:esp32") in calls
        assert ("lib", "install", *firmware.LIBRARIES) in calls
        assert any("ESP32Servo@3.0.9" in c for c in calls)
    def test_setup_reset_config(self, calls):
        firmware.main(["setup", "--reset-config"])
        assert calls[0] == ("config", "init", "--overwrite")
    def test_ports_reports_missing_esp32(self, calls, capsys):
        assert firmware.main(["ports"]) == 1
        assert "No ESP32 USB device found" in capsys.readouterr().out
    def test_ports_finds_esp32(self, calls, capsys):
        self.ports_json = json.dumps(
            {"detected_ports": [{"port": {"address": "COM9", "protocol_label": "USB",
                                          "properties": {"vid": "0x1A86"}}}]}
        )
        assert firmware.main(["ports"]) == 0
        assert "COM9" in capsys.readouterr().out
    def test_build_compiles_with_board_fqbn(self, calls):
        assert firmware.main(["build", "--board", "devkit"]) == 0
        compile_call = calls[-1]
        assert compile_call[:3] == ("compile", "--fqbn", "esp32:esp32:esp32")
        assert "--upload" not in compile_call
    def test_upload_requires_port(self, calls, capsys):
        assert firmware.main(["upload", "--board", "devkit"]) == 1
        assert "--port is required" in capsys.readouterr().err
    def test_upload_passes_port(self, calls):
        assert firmware.main(["upload", "--board", "s2mini", "--port", "COM5"]) == 0
        assert "--upload" in calls[-1] and "COM5" in calls[-1]
    def test_motors_flashes_tester(self, calls, capsys):
        assert firmware.main(["motors", "--board", "devkit", "--port", "COM5"]) == 0
        assert calls[-1][-1].endswith("motor-tester")
        assert "serial monitor" in capsys.readouterr().out
    def test_staged_sketch_has_patched_pins_and_bitmaps(self, tmp_path):
        sketch = firmware.stage_main_sketch(tmp_path, firmware.BOARDS["devkit"])
        assert (sketch / "face-bitmaps.h").exists()
        text = (sketch / "firmware-main.ino").read_text(encoding="utf-8")
        assert "{15, 2, 23, 19, 4, 16, 17, 18}" in text
    def test_source_files_are_not_modified(self, tmp_path):
        before = (FIRMWARE / "firmware-main.ino").read_bytes()
        firmware.stage_main_sketch(tmp_path, firmware.BOARDS["devkit"])
        assert (FIRMWARE / "firmware-main.ino").read_bytes() == before
class TestRunCli:
    def test_failure_raises_tool_error(self, monkeypatch):
        class Result:
            returncode = 2
            stdout = ""
            stderr = "boom"
        monkeypatch.setattr(firmware.subprocess, "run", lambda *a, **k: Result())
        with pytest.raises(firmware.ToolError, match="boom"):
            firmware.run_cli("arduino-cli", "version", capture=True)
    def test_success_returns_stdout(self, monkeypatch):
        class Result:
            returncode = 0
            stdout = "ok"
            stderr = ""
        monkeypatch.setattr(firmware.subprocess, "run", lambda *a, **k: Result())
        assert firmware.run_cli("arduino-cli", "version", capture=True) == "ok"
class TestRunCliErrors:
    def test_missing_binary_raises_tool_error(self):
        with pytest.raises(firmware.ToolError, match="cannot run"):
            firmware.run_cli("/definitely/not/arduino-cli", "version")
    def test_failure_falls_back_to_stdout(self, monkeypatch):
        class Result:
            returncode = 1
            stdout = "from stdout"
            stderr = ""
        monkeypatch.setattr(firmware.subprocess, "run", lambda *a, **k: Result())
        with pytest.raises(firmware.ToolError, match="from stdout"):
            firmware.run_cli("arduino-cli", "x", capture=True)
class FailingRobot(MockRobot):
    """Status works, commands fail (HTTP 500) except stop."""
    def do_POST(self):
        length = int(self.headers.get("Content-Length", 0))
        body = json.loads(self.rfile.read(length))
        MockRobot.commands.append(body)
        if body.get("command") == "stop":
            self.reply({"status": "ok"})
        else:
            self.reply({"error": "boom"}, 500)
class RejectsForward(MockRobot):
    """Accepts face updates and stop, fails on the movement command."""
    def do_POST(self):
        length = int(self.headers.get("Content-Length", 0))
        body = json.loads(self.rfile.read(length))
        MockRobot.commands.append(body)
        self.reply({"error": "boom"} if body.get("command") == "forward" else {"status": "ok"},
                   500 if body.get("command") == "forward" else 200)
class TextRobot(MockRobot):
    def do_GET(self):
        data = b"<html>not json</html>"
        self.send_response(200)
        self.send_header("Content-Length", str(len(data)))
        self.end_headers()
        self.wfile.write(data)
def serve(handler):
    server = HTTPServer(("127.0.0.1", 0), handler)
    threading.Thread(target=server.serve_forever, daemon=True).start()
    return server
class TestApiFailures:
    def test_http_error_reported(self, monkeypatch, capsys):
        monkeypatch.setattr(api_test, "SETTLE_SECONDS", 0)
        MockRobot.commands = []
        server = serve(FailingRobot)
        try:
            assert api_test.main(["--host", f"127.0.0.1:{server.server_port}"]) == 1
        finally:
            server.shutdown()
            server.server_close()
        assert "HTTP 500" in capsys.readouterr().err
    def test_stop_sent_even_when_command_fails(self, monkeypatch):
        monkeypatch.setattr(api_test, "SETTLE_SECONDS", 0)
        MockRobot.commands = []
        server = serve(RejectsForward)
        try:
            base = f"http://127.0.0.1:{server.server_port}"
            with pytest.raises(api_test.ApiError):
                api_test.run(base, move=False, command="forward")
        finally:
            server.shutdown()
            server.server_close()
        sent = [c.get("command") for c in MockRobot.commands]
        assert sent == [None, "forward", "stop"]
    def test_non_json_reply_reported(self, capsys):
        server = serve(TextRobot)
        try:
            assert api_test.main(["--host", f"127.0.0.1:{server.server_port}"]) == 1
        finally:
            server.shutdown()
            server.server_close()
        assert "did not return JSON" in capsys.readouterr().err
    def test_stop_quietly_swallows_errors(self, capsys):
        api_test.stop_quietly("http://127.0.0.1:1")
        assert "could not send stop" in capsys.readouterr().err
    def test_keyboard_interrupt_returns_130(self, monkeypatch):
        def boom(*a, **k):
            raise KeyboardInterrupt
        monkeypatch.setattr(api_test, "run", boom)
        assert api_test.main([]) == 130
class NoCorsRobot(MockRobot):
    """Old firmware: OPTIONS falls into the POST-only handler and gets 405."""
    def do_OPTIONS(self):
        self.reply({"error": "Method not allowed"}, 405)
class CorsWithoutHeader(MockRobot):
    def do_OPTIONS(self):
        self.send_response(204)
        self.send_header("Content-Length", "0")
        self.end_headers()
class TestCors:
    def test_cors_ok(self, robot, capsys):
        api_test.check_cors(f"http://{robot}")
        assert "CORS OK" in capsys.readouterr().out
    @pytest.mark.parametrize("handler,needle", [(NoCorsRobot, "HTTP 405"), (CorsWithoutHeader, "no Access-Control")])
    def test_cors_failures_tell_user_to_reflash(self, handler, needle):
        server = serve(handler)
        try:
            with pytest.raises(api_test.ApiError, match=needle):
                api_test.check_cors(f"http://127.0.0.1:{server.server_port}")
        finally:
            server.shutdown()
            server.server_close()
    def test_unreachable(self):
        with pytest.raises(api_test.ApiError, match="cannot reach"):
            api_test.check_cors("http://127.0.0.1:1")
class TestPanelEmbedding:
    def test_embedded_header_matches_panel_source(self):
        """Fails if panel/controller_template.html changed without re-embedding."""
        assert firmware.embed_panel.main([str(firmware.PANEL_SOURCE), "--check"]) == 0
    def test_build_and_upload_refresh_the_panel(self, monkeypatch):
        refreshed = []
        monkeypatch.setattr(firmware, "refresh_panel_header", lambda: refreshed.append(1))
        monkeypatch.setattr(firmware, "run_cli", lambda *a, **k: "")
        monkeypatch.setattr(firmware, "find_cli", lambda explicit: "arduino-cli")
        firmware.main(["build", "--board", "devkit"])
        firmware.main(["upload", "--board", "devkit", "--port", "COM5"])
        assert len(refreshed) == 2
    def test_refresh_reports_embed_errors(self, monkeypatch, tmp_path):
        monkeypatch.setattr(firmware, "PANEL_SOURCE", tmp_path / "missing.html")
        with pytest.raises(firmware.ToolError, match="control panel"):
            firmware.refresh_panel_header()
    def test_panel_posts_only_to_known_robot_endpoints(self):
        """Every URL the panel can request must exist in the firmware."""
        html = firmware.PANEL_SOURCE.read_text(encoding="utf-8")
        ino = (FIRMWARE / "firmware-main.ino").read_text(encoding="utf-8")
        for path in ("/cmd?", "/setSettings?"):
            assert path in html
            assert f'server.on("{path.rstrip("?")}"' in ino
    def test_panel_has_no_external_resources(self):
        html = firmware.PANEL_SOURCE.read_text(encoding="utf-8")
        assert firmware.embed_panel.external_references(html) == []