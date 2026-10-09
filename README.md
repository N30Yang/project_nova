# Project Nova

"My place in space" hackathon demo. A Nova ESP32 quadruped robot acts out how it
would move under the gravity of the Moon, Mars, Earth and Jupiter, triggered from
the robot's phone web page.

Nova is built on top of the open-source Nova robot, [dorianborian/sesame-robot](https://github.com/dorianborian/sesame-robot).

## Layout

| Path | What |
|---|---|
| [CHECKLIST.md](CHECKLIST.md) | Everything to do before, during and after the demo |
| [firmware/](firmware/) | Nova firmware files (modified upstream Nova firmware) (planet animations, web buttons, serial shortcuts) |
| [panel/](panel/) | OLED planet-viewer sketch (Earth, Mars, Moon, Saturn, Jupiter) with servo |
| [docs/planet-notes.md](docs/planet-notes.md) | Gravity model, tuning numbers, durations |
| [docs/firmware-setup.md](docs/firmware-setup.md) | Install toolchain, pick board pins, build, flash, Wi-Fi, API test |
| [docs/motor-testing.md](docs/motor-testing.md) | Servo test and leg calibration before assembly |
| [docs/control-panel.md](docs/control-panel.md) | Control the robot from your own HTML panel (API, CORS, what works) |
| [tools/firmware.py](tools/firmware.py), [tools/api-test.py](tools/api-test.py) | Setup/build/flash script and JSON API smoke test |
| [tests/](tests/) | pytest tests for the tools (`python -m pytest tests`) |
| [tools/planet-sim/](tools/planet-sim/) | Offline simulator that runs the real animation code against a fake clock |

## Firmware files

The three files below are the ones changed from upstream. `face-bitmaps.h` and
`debugging-firmware/motor-tester.ino` are unmodified upstream files (Apache-2.0)
so the repo now builds and flashes on its own: see [docs/firmware-setup.md](docs/firmware-setup.md).

- `movement-sequences.h`: the PLANETS block (all tuning numbers at the top)
- `firmware-main.ino`: `moon`/`mars`/`earth`/`jupiter` dispatch and `rn mo|ma|ea|ju`
- `captive-portal.h`: Planets buttons, slider lock fix on STOP

All numbers are UNTESTED on hardware.

## Run the simulator

```sh
sh tools/planet-sim/run.sh
```

Needs g++. Checks angle ranges, STOP interrupts, ends-in-stand, setting restore,
and that the planet walk matches the stock walk.

## Quick tuning

Edit the top of the PLANETS block in `firmware/movement-sequences.h`:

- Too wobbly: lower `PLANET_INTENSITY` (0.5 to 0.3)
- Motion too small: raise it (0.5 to 0.8)
- Too slow/fast: that planet's `tempo`
- Brownout: that planet's `motorDelay`
