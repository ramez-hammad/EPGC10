<p align="center">
  <img src="docs/gallery/banner.png" width="100%">
</p>

# Expandable Programmable Graphing Calculator v1.0

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](#)
[![CI](https://github.com/ramez-hammad/EPGC10/actions/workflows/ci.yml/badge.svg)](https://github.com/ramez-hammad/EPGC10/actions/workflows/ci.yml)
![](https://img.shields.io/badge/platform-ESP32%20%7C%20PC-blue)
[![License](https://img.shields.io/badge/license-GPL--3.0-brightgreen)](LICENSE)

### ▶ [Try it in your browser](https://ramez-hammad.github.io) — no install, no hardware

<p align="center">
  <img src="docs/gallery/demo.gif" width="300">
</p>

## What this is

A graphing calculator built from scratch: a hand-written expression interpreter
(lexer → recursive-descent parser → evaluator) driving an LVGL user interface,
running either on an ESP32 with a 240x320 ILI9341 display or as a desktop
program on your PC. Both are built from the same source tree, so the calculator
you run in a window is the calculator that runs on the device.

It exists because a graphing calculator is a satisfyingly complete little
system — parsing, numerics, UI, and embedded hardware in one project — and
because every part of it is meant to be read and modified. If you want to see
how `sin(2x+1)` gets from a keypress to a plotted curve, the whole interpreter
is about 1200 lines of C.

**What works today**

* The interpreter: `+ - * / ^ !`, implicit multiplication, parentheses,
  `sin cos tan`, their inverse and hyperbolic forms, `ln log sqrt abs`, `pi`,
  variables `A`–`Z`, `Ans`, and degree/radian/gradian modes.
* Graphing up to five functions with panning.
* The PC simulator, which is fully usable with a mouse.

**What does not, yet**

* The ESP32 firmware **compiles and links, but has never been run on hardware**
  by the maintainers of this tree, and there is **no keypad scanning code** —
  the 9x6 matrix described in [docs/hardware.md](docs/hardware.md) is wired to
  GPIOs that no firmware reads. Build the hardware knowing that the input
  driver is the missing piece.
* Degree-mode trigonometry shows floating-point artefacts
  (`cos(90)` → `6.123234e-17`).

## Quick start (PC simulator)

Needs a C compiler, CMake 3.20+, and SDL2.

```bash
sudo apt install build-essential cmake libsdl2-dev   # Debian/Ubuntu

git clone --recurse-submodules https://github.com/ramez-hammad/EPGC10.git
cd EPGC10

cmake -S sim -B build-sim
cmake --build build-sim

./build-sim/ui        # the calculator
./build-sim/repl      # the interpreter alone, in your terminal
```

Already cloned without submodules? `git submodule update --init --recursive`.

Tests (they need no display and no hardware):

```bash
./build-sim/test_lexer
./build-sim/test_evaluator
```

## Firmware

Requires ESP-IDF v5.5.1:

```bash
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

Assembly and wiring instructions are in [docs/hardware.md](docs/hardware.md).

## Hardware

<img src="hardware/schematic.png" align="top">

The calculator is based on the ESP32 microcontroller, it features a TFT ILI9341 Display and 54 buttons dedicated to various functions.
4AAA batteries power all electronics.

## Documentation

[docs/overview.md](docs/overview.md) is the place to start: the layering, the
port contract between the shared code and the two platforms, how a keypress
reaches the display, and the known gaps.
[docs/interpreter.md](docs/interpreter.md) and [docs/lexer.md](docs/lexer.md)
cover the expression engine.

## Repository overview

[src/core/](src/core) => The interpreter: lexer, parser, evaluator\
[src/ui/](src/ui) => Screens, keypad handling, formatting, graphing\
[src/port/](src/port) => Platform ports: the ESP32 firmware and the SDL simulator\
[sim/](sim) => CMake build for the PC simulator\
[test/](test) => Host tests for the interpreter\
[components/](components) => Contains LVGL and drivers\
[fonts/](fonts) => Contains fonts used in the UI\
[hardware/](hardware) => Contains schematics and designs\
[docs/](docs) => Documentation and pictures

## Gallery

<p align="center">
  <img src="docs/gallery/5.png" width="30%">
  <img src="docs/gallery/6.png" width="30%">
  <img src="docs/gallery/3.png" width="30%">
</p>
<p align="center"><i>Multiple plots · the function toolbox · the variable menu</i></p>

<details>
<summary>More screenshots</summary>

<figure>
  <img src="docs/gallery/1.png">
  <figcaption><b>Figure 1:</b> The menu in the simulator </figcaption>
</figure>
<figure>
  <img src="docs/gallery/2.png">
  <figcaption><b>Figure 2:</b> Default screen in the simulator </figcaption>
</figure>
<figure>
  <img src="docs/gallery/4.png">
  <figcaption><b>Figure 4:</b> Graph of sin(x) </figcaption>
</figure>
<figure>
  <img src="docs/gallery/7.png">
  <figcaption><b>Figure 7:</b> Sample expression with evaluation </figcaption>
</figure>
<figure>
  <img src="docs/gallery/8.png">
  <figcaption><b>Figure 8:</b> Demonstrating implicit multiplication </figcaption>
</figure>
<figure>
  <img src="docs/gallery/9.png">
  <figcaption><b>Figure 9:</b> Angle measure menu </figcaption>
</figure>
<figure>
  <img src="docs/gallery/10.png">
  <figcaption><b>Figure 10:</b> Ans variable showcase </figcaption>
</figure>
<figure>
  <img src="docs/gallery/11.png">
  <figcaption><b>Figure 11:</b> Syntax error pop-up </figcaption>
</figure>
<figure>
  <img src="docs/gallery/12.png">
  <figcaption><b>Figure 12:</b> Invalid input pop-up </figcaption>
</figure>

</details>

## License

[GPL-3.0](LICENSE).
