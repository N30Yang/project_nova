"""Tests for tools/embed_panel.py. Run: python -m pytest tests"""
import importlib.util
import sys
from pathlib import Path
import pytest
TOOLS = Path(__file__).resolve().parent.parent / "tools"
spec = importlib.util.spec_from_file_location("embed_panel_tool", TOOLS / "embed_panel.py")
embed = importlib.util.module_from_spec(spec)
sys.modules["embed_panel_tool"] = embed
spec.loader.exec_module(embed)
PAGE = "<!doctype html><title>Nova</title><script>fetch('/api/status')</script>\n"
@pytest.fixture
def page(tmp_path):
    path = tmp_path / "panel.html"
    path.write_text(PAGE, encoding="utf-8")
    return path
def test_render_wraps_html_in_raw_string():
    out = embed.render_header(PAGE, "web/panel.html")
    assert 'R"nova_panel(' + PAGE + ')nova_panel";' in out
    assert out.startswith("#ifndef CONTROL_PANEL_H")
    assert "//" not in out.replace(PAGE, "")
def test_render_rejects_reserved_delimiter():
    with pytest.raises(embed.EmbedError, match="reserved"):
        embed.render_header('x )nova_panel" y', "p.html")
def test_render_rejects_empty():
    with pytest.raises(embed.EmbedError, match="empty"):
        embed.render_header("  \n", "p.html")
@pytest.mark.parametrize(
    "html",
    [
        '<script src="https://cdn.example/x.js"></script>',
        '<link href="//fonts.googleapis.com/css" rel="stylesheet">',
        "<style>@import url('https://x.test/a.css');</style>",
        "<style>body{background:url(http://x.test/a.png)}</style>",
    ],
)
def test_external_references_found(html):
    assert embed.external_references(html)
def test_local_references_not_flagged():
    html = '<script src="app.js"></script><a href="/api/status">x</a><img src="data:image/png;base64,AA">'
    assert embed.external_references(html) == []
def test_normalise_line_endings():
    assert embed.normalise("a\r\nb\rc\n") == "a\nb\nc\n"
def test_build_writes_header(page, tmp_path, capsys):
    out = tmp_path / "control-panel.h"
    assert embed.main([str(page), "--out", str(out)]) == 0
    assert "panel_html[] PROGMEM" in out.read_text(encoding="utf-8")
    assert "wrote" in capsys.readouterr().out
def test_check_detects_stale_and_fresh(page, tmp_path, capsys):
    out = tmp_path / "control-panel.h"
    assert embed.main([str(page), "--out", str(out), "--check"]) == 1
    embed.main([str(page), "--out", str(out)])
    assert embed.main([str(page), "--out", str(out), "--check"]) == 0
    page.write_text(PAGE + "<!-- changed -->", encoding="utf-8")
    assert embed.main([str(page), "--out", str(out), "--check"]) == 1
    assert "out of date" in capsys.readouterr().err
def test_crlf_source_gives_same_header(tmp_path):
    lf = tmp_path / "lf.html"
    crlf = tmp_path / "crlf.html"
    lf.write_bytes(b"<p>a</p>\n<p>b</p>\n")
    crlf.write_bytes(b"<p>a</p>\r\n<p>b</p>\r\n")
    assert embed.render_header(embed.read_source(lf), "x") == embed.render_header(embed.read_source(crlf), "x")
def test_warns_on_external_and_large(tmp_path, capsys):
    path = tmp_path / "big.html"
    path.write_text('<script src="https://x.test/a.js"></script>' + "a" * (embed.SIZE_WARN_BYTES + 1), encoding="utf-8")
    embed.main([str(path), "--out", str(tmp_path / "o.h")])
    err = capsys.readouterr().err
    assert "external link" in err and "minifying" in err
def test_missing_source_is_reported(tmp_path, capsys):
    assert embed.main([str(tmp_path / "nope.html"), "--out", str(tmp_path / "o.h")]) == 1
    assert "cannot read" in capsys.readouterr().err