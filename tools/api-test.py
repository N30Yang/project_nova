#!/usr/bin/env python3
"""Smoke-test the robot's JSON API (GET /api/status, POST /api/command).
Join the robot's Wi-Fi first (default AP: Nova-Controller), then:
    python tools/api-test.py                  # status + face change only (robot does not move)
    python tools/api-test.py --move           # also stand, wave, stop
    python tools/api-test.py --host nova-robot.local
    python tools/api-test.py --command moon   # send one custom command, then stop
Uses only the standard library.
"""
from __future__ import annotations
import argparse
import json
import sys
import time
import urllib.error
import urllib.request
from typing import Any, Optional, Sequence
DEFAULT_HOST = "192.168.4.1"
TIMEOUT_SECONDS = 5
SETTLE_SECONDS = 3
PANEL_ORIGIN = "http://panel.test"
OPENER = urllib.request.build_opener(urllib.request.ProxyHandler({}))
class ApiError(Exception):
    """The robot could not be reached or answered with an error."""
def request_json(url: str, payload: Optional[dict[str, Any]] = None) -> dict[str, Any]:
    body = None if payload is None else json.dumps(payload).encode("utf-8")
    headers = {"Content-Type": "application/json"} if body else {}
    req = urllib.request.Request(url, data=body, headers=headers)
    try:
        with OPENER.open(req, timeout=TIMEOUT_SECONDS) as resp:
            return json.loads(resp.read().decode("utf-8") or "{}")
    except urllib.error.HTTPError as err:
        raise ApiError(f"{url} returned HTTP {err.code}") from err
    except (urllib.error.URLError, TimeoutError, OSError) as err:
        raise ApiError(
            f"cannot reach {url} ({err}). Is the robot on, and is this computer on its Wi-Fi?"
        ) from err
    except json.JSONDecodeError as err:
        raise ApiError(f"{url} did not return JSON") from err
def send(base: str, payload: dict[str, Any]) -> None:
    reply = request_json(f"{base}/api/command", payload)
    print(f"  POST {payload} -> {reply}")
def check_cors(base: str) -> None:
    """Confirm an external HTML panel may call the API (preflight + Allow-Origin)."""
    req = urllib.request.Request(
        f"{base}/api/command",
        method="OPTIONS",
        headers={
            "Origin": PANEL_ORIGIN,
            "Access-Control-Request-Method": "POST",
            "Access-Control-Request-Headers": "content-type",
        },
    )
    try:
        with OPENER.open(req, timeout=TIMEOUT_SECONDS) as resp:
            allowed = resp.headers.get("Access-Control-Allow-Origin")
    except urllib.error.HTTPError as err:
        raise ApiError(f"CORS preflight rejected with HTTP {err.code}; reflash the latest firmware") from err
    except (urllib.error.URLError, TimeoutError, OSError) as err:
        raise ApiError(f"cannot reach {base} for the CORS check ({err})") from err
    if allowed not in ("*", PANEL_ORIGIN):
        raise ApiError("robot sends no Access-Control-Allow-Origin header; reflash the latest firmware")
    print(f"  CORS OK (Access-Control-Allow-Origin: {allowed})")
def stop_quietly(base: str) -> None:
    """Best-effort stop so a failed test never leaves the robot moving."""
    try:
        send(base, {"command": "stop"})
    except ApiError as err:
        print(f"  warning: could not send stop: {err}", file=sys.stderr)
def run(base: str, *, move: bool, command: Optional[str]) -> None:
    print("GET /api/status")
    print(f"  {request_json(f'{base}/api/status')}")
    print("CORS preflight (needed by an external control panel)")
    check_cors(base)
    print("Face-only update (robot should not move)")
    send(base, {"face": "happy"})
    time.sleep(SETTLE_SECONDS)
    sequence: list[dict[str, Any]] = []
    if command:
        sequence = [{"command": command}]
    elif move:
        sequence = [{"command": "stand"}, {"command": "wave", "face": "happy"}]
    if not sequence:
        print("API OK")
        return
    try:
        for step in sequence:
            print("Movement command (keep the robot on a stand)")
            send(base, step)
            time.sleep(SETTLE_SECONDS)
    finally:
        stop_quietly(base)
    print("API OK")
def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("--host", default=DEFAULT_HOST, help=f"robot IP or hostname (default {DEFAULT_HOST})")
    parser.add_argument("--move", action="store_true", help="also stand, wave and stop")
    parser.add_argument("--command", help="send one custom command (e.g. forward, moon), then stop")
    return parser
def main(argv: Optional[Sequence[str]] = None) -> int:
    args = build_parser().parse_args(argv)
    try:
        run(f"http://{args.host}", move=args.move, command=args.command)
    except ApiError as err:
        print(f"error: {err}", file=sys.stderr)
        return 1
    except KeyboardInterrupt:
        print("interrupted", file=sys.stderr)
        return 130
    return 0
if __name__ == "__main__":
    sys.exit(main())