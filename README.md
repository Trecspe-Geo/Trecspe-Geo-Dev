# Trecspe-Geo-Dev

<p align="center">
  <img src="https://img.shields.io/badge/Trecspe%20Geo-Embedded%20IoT%20Firmware-0B3D91?style=for-the-badge" alt="Trecspe Geo"/>
  <img src="https://img.shields.io/badge/MCU-ATmega4809-C41230?style=for-the-badge" alt="ATmega4809"/>
  <img src="https://img.shields.io/badge/Language-C%20(OOP%20style)-00599C?style=for-the-badge" alt="C OOP"/>
  <img src="https://img.shields.io/badge/License-Proprietary-111111?style=for-the-badge" alt="Proprietary"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Focus-Cameroon%20%7C%20Low%20%2F%20No%20coverage-2E8B57?style=flat-square" alt="Cameroon"/>
  <img src="https://img.shields.io/badge/Stack-AVR--GCC%20%7C%20CMake%20%7C%20MPLAB-6A5ACD?style=flat-square" alt="Toolchain"/>
  <img src="https://img.shields.io/badge/Status-Early%20development-F4A261?style=flat-square" alt="Early development"/>
</p>

**Trecspe Geo** is a public embedded/IoT firmware portfolio for field devices that must stay useful in **Cameroon** where cellular coverage is weak or absent.

| | |
|--|--|
| **Platform** | AVR **ATmega4809**, register-level drivers |
| **Language** | C, with an object-oriented style (structs + function pointers) |
| **Toolchain** | AVR-GCC, CMake, MPLAB X / VS Code |
| **Status** | Early development — digital IO HAL and board bring-up are in tree; GSM, MQTT, and product logic are the intended direction and are **not implemented yet** |
| **License** | Proprietary, All Rights Reserved ([`LICENSE`](LICENSE)) — this is **not** an open-source project |

The repository is public so engineers and recruiters can read the architecture and code. Reading it here does not grant a license to reuse the libraries. See [License](#license).

---

## Mission

Design and implement firmware that:

- Runs on constrained MCU hardware (**AVR / ATmega4809**)
- Drives **external modules** (GSM modem, sensors, radios) over UART/SPI/I²C and GPIO
- Publishes / subscribes with **MQTT** when connectivity exists
- **Stores data offline** when the network is unavailable, then syncs later
- Stays robust on power, RF, and long unattended deployments

Same toolbox (MCU, GSM module, MQTT, sensors, OOP-in-C drivers) can power many products — not one single application. Those links and protocols are the design target. They are not present as drivers in this repository today.

---

## Current status

What is in the tree now:

- `Src/hw_desc/` — digital IO library: pin objects, function-pointer methods, direct AVR port registers
- `main.c` — bring-up that initializes one output pin and toggles it
- `cmake/HALGPS/TrecspeGeo/user.cmake` — build hook so MPLAB/CMake compiles the IO source with the same struct ABI flags as the application

What is not in the tree yet: GSM/modem drivers, MQTT client, offline storage, and a finished product application.

---

## What you can build with this stack

Intended product directions for this hardware class: **MCU (AVR)** · **GSM module** · **optional location module** · **MQTT** · **GPIO/sensors** · **offline store-and-forward**.

| Product idea | Why it fits Cameroon / low coverage |
|--------------|-------------------------------------|
| **Asset / vehicle anti-theft beacon** | Log movement offline; SMS/MQTT alert when GSM returns |
| **Cold-chain / vaccine fridge monitor** | Temp + door events → MQTT; buffer during outages |
| **Farm pump & tank controller** | Soil/level sensors + GSM commands; solar-friendly sleep |
| **Motorcycle / taxi fleet logger** | Trip + idle logs; sync in town when signal exists |
| **SOS / personal safety pendant** | Button → SMS + last known fix when network allows |
| **Shared solar mini-grid meter** | Energy pulses + MQTT billing events, offline queue |
| **Wildlife / livestock collar (low rate)** | Rare uplinks to save battery; store tracks offline |
| **Border / depot geofence logger** | Enter/leave events buffered, flushed over GSM/MQTT |

### References in the same class of tools

These are external projects, not part of this repository. They are listed only as technical context:

- **Emergency alert + tracking over MQTT/GSM** — ([IEEE ICTMIM 2025](https://doi.org/10.1109/ictmim65579.2025.10987939))
- **Hydro-Orbit** — sensors and MQTT for irrigation ([GitHub](https://github.com/kawacukennedy/hydro_orbit))
- **Smart Irri-Kit** — MCU and GSM irrigation work associated with Makerere field research
- Long-life asset devices that sleep and uplink over GSM when coverage returns

Use them as **inspiration only**. This repository’s code stays under its stated proprietary license.

---

## Engineering approach

### OOP in C

Hardware is modeled with an object-oriented style in plain C:

| Idea | In this project |
|------|-----------------|
| Object | `sDio_t` struct (pin state + config) |
| Methods | Function pointers: `pfvLevelOn`, `pfvLevelOff`, `pfvToggle`, `pfbGetLevel` |
| Constructor | `vInitPin(...)` binds the object to a pin and its register operations |

See `Src/hw_desc` — IO through the object interface, not scattered raw port writes.

### Register-level control

Critical paths talk to **hardware registers** directly (port direction, OUTSET/OUTCLR, pull-ups, peripherals).  
Predictable timing, power, and debug on the metal.

---

## Repository layout

| Path | Role |
|------|------|
| `main.c` | Application entry / bring-up |
| `Src/hw_desc/` | OOP-in-C IO library + register access |
| `cmake/HALGPS/TrecspeGeo/` | CMake / MPLAB project customization (`user.cmake`) |
| `Makefile` / `nbproject/` | MPLAB build support |
| `CONTRIBUTING.md` | How to report issues and propose changes |
| `LICENSE` | Full proprietary license text |

---

## Setup

The repository is public. You can clone it to inspect and try the current bring-up build. That does not change the [license](#license).

### 1. Requirements

- [MPLAB X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide) (or VS Code + MPLAB / AVR extensions)
- **AVR-GCC** toolchain for `atmega4809`
- Microchip **ATmega_DFP** pack
- Debug probe (Curiosity / SNAP / ICE, etc.) if you flash hardware
- Optional later, when those drivers exist: **GSM module**, MQTT broker access, sensors

### 2. Clone

```bash
git clone https://github.com/Trecspe-Geo/Trecspe-Geo-Dev.git
cd Trecspe-Geo-Dev
```

### 3. Open the project

1. Open MPLAB X (or VS Code in this folder)
2. Load the **HALGPS / TrecspeGeo** project under `cmake/HALGPS/TrecspeGeo`
3. Confirm `user.cmake` adds the IO source:

```cmake
target_sources(HALGPS_TrecspeGeo_image_DJF9GR8v PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../Src/hw_desc/src/hw_desc_io.c"
)
```

### 4. Important compile flags

`main.c` and `hw_desc_io.c` **must** share the same struct ABI flags:

```text
-mmcu=atmega4809
-g -gdwarf-2
-fpack-struct
-fshort-enums
-O0
-fno-inline
```

Set in `cmake/HALGPS/TrecspeGeo/user.cmake` — keep aligned with the main image.

### 5. Build

- **MPLAB X**: TrecspeGeo configuration → **Build**
- Or CMake/Ninja under `_build/HALGPS/TrecspeGeo`

### 6. Flash & debug

1. Connect board + debug tool  
2. Program the device  
3. Breakpoints in `main.c` and `Src/hw_desc/src/hw_desc_io.c`  
4. If the IDE looks under `_build/` for sources, open the file from `Src/` and set the breakpoint there  

### 7. Minimal smoke test

```c
sDio_t sDigIO = {0};
vInitPin(&sDigIO, IO_PORT_A_PIN_00, IO_DIR_OUTPUT, PULL_NONE);

if (sDigIO.pfvLevelOn != NULL)
{
    sDigIO.pfvLevelOn();   /* PA00 via OOP-in-C + registers */
}
```

There is no automated test suite in this repository yet. Hardware check is: the selected pin toggles as driven by `main.c` or the snippet above.

---

## Reporting bugs and proposals

- **Bugs, build failures, and hardware notes:** open a [GitHub issue](https://github.com/Trecspe-Geo/Trecspe-Geo-Dev/issues) (bug report template).
- **Feature or architecture ideas:** open an issue with the proposal or architecture template **before** a large pull request.
- **Direct contact:** [kamdema86@gmail.com](mailto:kamdema86@gmail.com)

---

## Contributions

Feedback, bug reports, architectural suggestions and pull requests are welcome.

Before submitting a pull request, please read [`CONTRIBUTING.md`](CONTRIBUTING.md).

This project is currently maintained as a public portfolio/development project. The source code remains under its stated license.

Participation (issues, discussions, or a pull request) does not grant any right to use, copy, redistribute, or sublicense the existing source beyond what [`LICENSE`](LICENSE) already permits.

---

## License

* [Proprietary — All Rights Reserved](LICENSE)

This project is **not** open source.

The source is published so it can be inspected. [`LICENSE`](LICENSE) still reserves all rights. Without prior written permission you may not reuse the libraries or drivers in another product or project.

Licensing questions: [kamdema86@gmail.com](mailto:kamdema86@gmail.com).
