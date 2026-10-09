#!/usr/bin/env python3
"""Set up, build and flash the Nova firmware with arduino-cli.
The firmware sources in firmware/ are never modified. For each build the
sketch is copied to a temp folder and the pin block is written into the copy,
so the build always uses the ESP32 Dev Module pins.
    python tools/firmware.py setup
    python tools/firmware.py ports
    python tools/firmware.py build  --board devkit
    python tools/firmware.py upload --board devkit --port COM5
    python tools/firmware.py motors --board devkit --port COM5
"""
from __future__ import annotations
import argparse
import json
import os
import re
import shutil
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Callable, Optional, Sequence
TOOLS_DIR = Path(__file__).resolve().parent
if str(TOOLS_DIR) not in sys.path:
    sys.path.insert(0, str(TOOLS_DIR))
import embed_panel
REPO_ROOT = Path(__file__).resolve().parent.parent
FIRMWARE_DIR = REPO_ROOT / "firmware"
MOTOR_TESTER = FIRMWARE_DIR / "debugging-firmware" / "motor-tester.ino"
PANEL_SOURCE = REPO_ROOT / "panel" / "ui-new.html"
BUILD_DIR = REPO_ROOT / ".build"
MAIN_SKETCH = "firmware-main"
TESTER_SKETCH = "motor-tester"
ESP32_INDEX_URL = (
    "https://raw.githubusercontent.com/espressif/arduino-esp32/"
    "gh-pages/package_esp32_index.json"
)
ESP32_CORE = "esp32:esp32"
LIBRARIES = ("ESP32Servo@3.0.9", "Adafruit SSD1306", "Adafruit GFX Library")
ESP32_USB_VIDS = frozenset({"0X303A", "0X10C4", "0X1A86", "0X0403"})
@dataclass(frozen=True)
class Board:
    fqbn: str
    servo_pins: tuple[int, ...]
    sda: int
    scl: int
BOARDS = {
    "devkit": Board("esp32:esp32:esp32", (15, 2, 23, 19, 4, 16, 17, 18), 21, 22),
}
PIN_LINE_PATTERNS = {
    "sda": re.compile(r"^\s*(//\s*)?#define\s+I2C_SDA\b"),
    "scl": re.compile(r"^\s*(//\s*)?#define\s+I2C_SCL\b"),
    "pins": re.compile(r"^\s*(//\s*)?const\s+int\s+servoPins\s*\[\s*8\s*\]"),
}
class ToolError(Exception):
    """A problem the user can fix; reported without a traceback."""
def find_cli(explicit: Optional[str]) -> str:
    candidate = explicit or os.environ.get("ARDUINO_CLI") or shutil.which("arduino-cli")
    if not candidate:
        raise ToolError(
            "arduino-cli not found. Install it from "
            "https://arduino.github.io/arduino-cli/latest/installation/ , or pass "
            "--cli PATH or set ARDUINO_CLI."
        )
    return candidate
def run_cli(cli: str, *args: str, capture: bool = False) -> str:
    command = [cli, *args]
    print("$ " + " ".join(command), flush=True)
    try:
        result = subprocess.run(
            command, capture_output=capture, text=True, encoding="utf-8", errors="replace"
        )
    except OSError as err:
        raise ToolError(f"cannot run {cli!r}: {err}") from err
    if result.returncode != 0:
        detail = ((result.stderr or result.stdout or "").strip()) if capture else ""
        raise ToolError(f"arduino-cli failed (exit {result.returncode}). {detail}".strip())
    return result.stdout if capture else ""
def patch_pins(source: str, board: Board) -> str:
    """Return source with the I2C and servo pin definitions replaced for board.
    The first matching line of each kind is replaced; any further matches
    (commented alternatives for other boards) are dropped.
    """
    replacements = {
        "sda": f"#define I2C_SDA {board.sda}",
        "scl": f"#define I2C_SCL {board.scl}",
        "pins": f"const int servoPins[8] = {{{', '.join(map(str, board.servo_pins))}}};",
    }
    seen: set[str] = set()
    out: list[str] = []
    for line in source.splitlines():
        key = next((k for k, p in PIN_LINE_PATTERNS.items() if p.match(line)), None)
        if key is None:
            out.append(line)
        elif key not in seen:
            seen.add(key)
            out.append(replacements[key])
    if "pins" not in seen:
        raise ToolError("Could not find the servoPins definition to patch.")
    return "\n".join(out) + "\n"
def stage_main_sketch(workdir: Path, board: Board) -> Path:
    sketch = workdir / MAIN_SKETCH
    sketch.mkdir()
    for path in FIRMWARE_DIR.iterdir():
        if path.suffix in (".h", ".ino"):
            shutil.copy2(path, sketch / path.name)
    ino = sketch / f"{MAIN_SKETCH}.ino"
    if not ino.exists():
        raise ToolError(f"{ino.name} missing from {FIRMWARE_DIR}")
    ino.write_text(patch_pins(ino.read_text(encoding="utf-8"), board), encoding="utf-8")
    return sketch
def stage_tester_sketch(workdir: Path, board: Board) -> Path:
    if not MOTOR_TESTER.exists():
        raise ToolError(f"{MOTOR_TESTER} is missing")
    sketch = workdir / TESTER_SKETCH
    sketch.mkdir()
    ino = sketch / f"{TESTER_SKETCH}.ino"
    ino.write_text(patch_pins(MOTOR_TESTER.read_text(encoding="utf-8"), board), encoding="utf-8")
    return sketch
def refresh_panel_header() -> None:
    """Re-embed the control panel so the robot never serves a stale page."""
    try:
        embed_panel.build(PANEL_SOURCE, embed_panel.DEFAULT_OUT, check=False)
    except embed_panel.EmbedError as err:
        raise ToolError(f"control panel: {err}") from err
def cmd_setup(args: argparse.Namespace) -> int:
    cli = find_cli(args.cli)
    if args.reset_config:
        run_cli(cli, "config", "init", "--overwrite")
    run_cli(cli, "config", "add", "board_manager.additional_urls", ESP32_INDEX_URL)
    run_cli(cli, "core", "update-index")
    run_cli(cli, "core", "install", ESP32_CORE)
    run_cli(cli, "lib", "install", *LIBRARIES)
    print("\nSetup done. Next: python tools/firmware.py ports")
    return 0
def parse_ports(raw_json: str) -> list[dict]:
    """Extract the port records from `arduino-cli board list --format json`."""
    try:
        data = json.loads(raw_json)
    except json.JSONDecodeError as err:
        raise ToolError(f"arduino-cli board list returned invalid JSON: {err}") from err
    entries = data.get("detected_ports", []) if isinstance(data, dict) else data
    return [entry.get("port", {}) for entry in entries]
def is_esp32_usb(port: dict) -> bool:
    vid = str((port.get("properties") or {}).get("vid", "")).upper()
    return vid in ESP32_USB_VIDS
def cmd_ports(args: argparse.Namespace) -> int:
    ports = parse_ports(run_cli(find_cli(args.cli), "board", "list", "--format", "json", capture=True))
    for port in ports:
        tag = "  <- looks like an ESP32 board" if is_esp32_usb(port) else ""
        print(f"{port.get('address', '?'):10} {port.get('protocol_label', '')}{tag}")
    if any(is_esp32_usb(p) for p in ports):
        return 0
    print(
        "\nNo ESP32 USB device found. Check: (1) the USB cable carries data, not just "
        "power; (2) try another USB port; (3) install the CP210x or CH340 driver; "
        "(4) hold the BOOT button while plugging in."
    )
    return 1
def build_or_flash(
    args: argparse.Namespace,
    stager: Callable[[Path, Board], Path],
    *,
    upload: bool,
) -> None:
    cli = find_cli(args.cli)
    board = BOARDS[args.board]
    if upload and not args.port:
        raise ToolError("--port is required to upload (see: python tools/firmware.py ports)")
    shutil.rmtree(BUILD_DIR, ignore_errors=True)
    BUILD_DIR.mkdir(parents=True)
    sketch = stager(BUILD_DIR, board)
    compile_args = ["compile", "--fqbn", board.fqbn]
    if upload:
        compile_args += ["--upload", "--port", args.port]
    run_cli(cli, *compile_args, str(sketch))
    print("\nUpload complete." if upload else "\nBuild OK.")
def cmd_build(args: argparse.Namespace) -> int:
    refresh_panel_header()
    build_or_flash(args, stage_main_sketch, upload=False)
    return 0
def cmd_upload(args: argparse.Namespace) -> int:
    refresh_panel_header()
    build_or_flash(args, stage_main_sketch, upload=True)
    return 0
def cmd_motors(args: argparse.Namespace) -> int:
    build_or_flash(args, stage_tester_sketch, upload=True)
    print("Open the serial monitor at 115200 baud and type: 0,90   (or all,90 / stop)")
    return 0
def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("--cli", help="path to arduino-cli (default: PATH or $ARDUINO_CLI)")
    sub = parser.add_subparsers(dest="command", required=True)
    setup = sub.add_parser("setup", help="install the ESP32 core and pinned libraries")
    setup.add_argument("--reset-config", action="store_true", help="recreate the arduino-cli config first")
    setup.set_defaults(func=cmd_setup)
    sub.add_parser("ports", help="list serial ports and spot the ESP32").set_defaults(func=cmd_ports)
    for name, func, helptext in (
        ("build", cmd_build, "compile only"),
        ("upload", cmd_upload, "compile and flash the main firmware"),
        ("motors", cmd_motors, "flash the servo motor tester"),
    ):
        p = sub.add_parser(name, help=helptext)
        p.add_argument("--board", choices=sorted(BOARDS), default="devkit")
        p.add_argument("--port", help="serial port, e.g. COM5 or /dev/ttyUSB0")
        p.set_defaults(func=func)
    return parser
def main(argv: Optional[Sequence[str]] = None) -> int:
    args = build_parser().parse_args(argv)
    try:
        return args.func(args)
    except ToolError as err:
        print(f"error: {err}", file=sys.stderr)
        return 1
if __name__ == "__main__":
    sys.exit(main())