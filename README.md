# Project Nova

Kiwi Hacks Hackathon project by James Street. This follows the prompt of "my place in space".

We are building a Nova ESP32 quadruped robot that acts how it would move under the gravity of different planets triggered by its control panel via a phone web page..

## Layout

| Path | What |
|---|---|
| [CHECKLIST.md](CHECKLIST.md) | Everything to do before, during and after the demo |
| [firmware/](firmware/) | Nova firmware files (planet animations, web buttons, serial shortcuts) |
| [panel/](panel/) | OLED planet-viewer sketch (Earth, Mars, Moon, Saturn, Jupiter) with servo |
| [panel/controller_template.html](panel/controller_template.html) | The Nova control panel: built into the firmware and served at http://192.168.4.1 |
| [docs/planet-notes.md](docs/planet-notes.md) | Gravity model, tuning numbers, durations |
| [docs/firmware-setup.md](docs/firmware-setup.md) | Install toolchain, pick board pins, build, flash, Wi-Fi, API test |
| [docs/motor-testing.md](docs/motor-testing.md) | Servo test and leg calibration before assembly |
| [docs/control-panel.md](docs/control-panel.md) | Control the robot from your own HTML panel (API, CORS, what works) |
| [tools/firmware.py](tools/firmware.py), [tools/api-test.py](tools/api-test.py), [tools/embed_panel.py](tools/embed_panel.py) | Setup/build/flash script, JSON API smoke test, panel embedder |
| [tests/](tests/) | pytest tests for the tools (`python -m pytest tests`) |
| [tools/planet-sim/](tools/planet-sim/) | Offline simulator that runs the real animation code against a fake clock |

## Firmware files

The files below are the ones changed from upstream. `face-bitmaps.h` is an unmodified upstream
file (Apache-2.0), included so the repo builds and flashes on its own: see
[docs/firmware-setup.md](docs/firmware-setup.md). The firmware is set up for the ESP32 Dev Module
(ESP32-WROOM-32) with SG90 servos only.

- `movement-sequences.h`: the PLANETS block (all tuning numbers at the top)
- `firmware-main.ino`: `moon`/`mars`/`earth`/`jupiter` dispatch and `rn mo|ma|ea|ju`, ESP32 Dev
  Module pins, SG90 pulse range, `/setSettings` rejects negative and out-of-range values
- `debugging-firmware/motor-tester.ino`: ESP32 Dev Module pins, SG90 pulse range
- `captive-portal.h`: Planets buttons, slider lock fix on STOP
- `planet-display.h` (new): while a planet pose runs, the OLED shows that planet spinning instead of the
  robot's face. When the pose ends or STOP is pressed the normal face returns. Textures and the sphere
  renderer are the same ones as in `panel/`.

All numbers are UNTESTED on hardware. The OLED planet display compiles and the simulator passes, but it has
not run on the robot yet.

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
