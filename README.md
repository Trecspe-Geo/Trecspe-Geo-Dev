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
  <img src="https://img.shields.io/badge/Links-GSM%20%7C%20MQTT%20%7C%20Modules-FF8C00?style=flat-square" alt="Connectivity"/>
</p>

Low-level **embedded IoT firmware** for **Trecspe Geo**.

Built for devices that must keep working in **hard field conditions** across **Cameroon** — including places with **weak or no cellular coverage**, using **MCU + modules (GSM / radio) + MQTT** when the network is back.

---

## Mission

Design and implement firmware that:

- Runs on constrained MCU hardware (**AVR / ATmega4809**)
- Drives **external modules** (GSM modem, sensors, radios) over UART/SPI/I²C and GPIO
- Publishes / subscribes with **MQTT** when connectivity exists
- **Stores data offline** when the network is unavailable, then syncs later
- Stays robust on power, RF, and long unattended deployments

Same toolbox (MCU, GSM module, MQTT, sensors, OOP-in-C drivers) can power many products — not one single application.

---

## What you can build with this stack

Your tools: **MCU (AVR)** · **GSM module** · **optional location module** · **MQTT** · **GPIO/sensors** · **offline store-and-forward**.

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

### Innovative references (same class of tools)

- **Emergency alert + tracking over MQTT/GSM** — ESP32 + A9G-style GSM/GPS module, SOS SMS + MQTT ([IEEE ICTMIM 2025](https://doi.org/10.1109/ictmim65579.2025.10987939))
- **Hydro-Orbit** — solar, sensors, **MQTT**, offline-friendly farm irrigation ([GitHub](https://github.com/kawacukennedy/hydro_orbit))
- **Smart Irri-Kit** — MCU + **GSM**, soil moisture, solar irrigation (Makerere / field Africa research)
- **Long-life asset trackers** — MCU + GSM module + motion wake + cloud/MQTT-style backends (e.g. industrial GAT designs)

Use them as **inspiration only** — this repo’s code stays proprietary (see License).

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
| `LICENSE` | Full proprietary license text |

---

## Setup

### 1. Requirements

- **Authorized** access to this private repository
- [MPLAB X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide) (or VS Code + MPLAB / AVR extensions)
- **AVR-GCC** toolchain for `atmega4809`
- Microchip **ATmega_DFP** pack
- Debug probe (Curiosity / SNAP / ICE, etc.)
- Optional for full product tests: **GSM module**, MQTT broker access, sensors

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

---

## Contributing (internal team)

- Feature branches, clear commits  
- Hardware-test IO, modem, MQTT, storage, power changes  
- Keep compile flags consistent across shared structs  
- Pull request before merge  

---

## License

* [Proprietary — All Rights Reserved](LICENSE)

This project is **not** open source.  
Full terms: [`LICENSE`](LICENSE). Unauthorized use or reuse of the libraries is prohibited.
