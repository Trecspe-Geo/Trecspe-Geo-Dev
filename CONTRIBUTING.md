# Contributing

Thank you for looking at **Trecspe Geo**. This is a public embedded firmware portfolio and development project. Feedback and careful pull requests help, and they do not change the license.

The source remains **proprietary / All Rights Reserved**. See [`LICENSE`](LICENSE). This document explains how to participate. It does **not** grant extra rights to use, copy, redistribute, or sublicense the code.

Contact: [kamdema86@gmail.com](mailto:kamdema86@gmail.com)

## Ways to contribute

- Bug reports
- Documentation improvements
- Architectural feedback
- Feature proposals
- Testing
- Hardware and bring-up notes
- Pull requests for focused fixes or docs

## Before contributing

For a typo or a small, obvious fix, a pull request is enough.

For anything larger — a new driver, a new module (GSM, MQTT, storage), or a change to the IO object model — **open an issue or discussion first** and wait for a response before implementing it. That avoids work that does not fit the firmware constraints or the license.

Read the existing style in `Src/hw_desc/` and `main.c` before editing.

## Pull requests

1. Fork the repository.
2. Create a branch from the current default branch.
3. Make a focused change.
4. Build locally with the project toolchain (AVR-GCC / MPLAB, ATmega4809).
5. Document what you changed, including hardware notes when relevant.
6. Open a pull request using the repository template.
7. Explain **what** changed and **why**.

A pull request is a suggestion. Merging it, if it is merged, does not transfer ownership of the existing project to you.

**Submitting a pull request does not grant you permission** to use, redistribute, or sublicense this project’s existing source code beyond what [`LICENSE`](LICENSE) already permits. Do not copy drivers or libraries from this repository into another product or publication unless you have separate written permission.

If your pull request includes **your** original work, you confirm that you have the right to submit it and that the maintainer may include it in this proprietary project. Do not submit code you do not have the right to offer.

## Code quality

Embedded C in this tree should stay small and predictable:

- Keep each change focused on one problem.
- Follow the existing naming and file layout. Do not restyle unrelated code.
- Avoid drive-by refactors.
- Comment non-obvious hardware or timing decisions (pin, register, why a flag must match across files).
- Do not add blocking waits on paths that must stay responsive, except where the existing bring-up code already uses a deliberate delay.
- Respect RAM, flash, timing, and power limits of an ATmega4809-class MCU.
- There is no automated test suite yet. If you add one, keep it buildable. Otherwise describe the manual check you ran (build, and hardware result if you flashed a board).
- `main.c` and `hw_desc_io.c` must keep the same struct-layout flags (`-fpack-struct`, `-fshort-enums`, and the debug flags already listed in `cmake/HALGPS/TrecspeGeo/user.cmake`). A mismatch breaks function pointers.

## Hardware-related contributions

If a change depends on a board or module, state:

- Hardware used (board name or a short description)
- MCU / platform (expect **ATmega4809** unless the issue says otherwise)
- Peripherals involved (GPIO, UART, GSM module, sensor, debugger)
- Wiring or configuration, if someone else must reproduce it
- What you assumed, and what you did not test

Do not claim a feature works on hardware you did not run.

## Communication

Keep discussion technical and respectful. Disagree on design with concrete constraints (flash, pins, timing, field coverage), not personal comments. Issues and pull requests are the preferred record; email [kamdema86@gmail.com](mailto:kamdema86@gmail.com) for licensing questions.
