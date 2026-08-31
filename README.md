<p align="center">
  <img src="docs/gallery/banner.png" width="100%">
</p>

# Expandable Programmable Graphing Calculator v1.0

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](#)
![](https://img.shields.io/badge/platform-ESP32-blue)
![](https://img.shields.io/badge/status-active-success)

## Introduction & Motivation
An open-source, expandable graphing calculator based on the ESP32 microcontroller.

## Features
- A custom mathematical expression interpreter with many built-in
  functions 
- 2D graphing
- Extensible and modular

## 🛠 Hardware
<img src="hardware/schematic.png" align="top">

The calculator is based on the ESP32 microcontroller, it features a TFT ILI9341 Display and 54 buttons dedicated to various functions.
4AAA batteries power all electronics.

## Repository Overview
[src/](src) => Shared source code that includes the interpreter and the UI\
[src/port/](src/port) => Platform ports: the ESP32 firmware and the SDL simulator\
[sim/](sim) => CMake build for the PC simulator\
[components/](components) => Contains LVGL and drivers\
[fonts/](fonts) => Contains fonts used in the UI\
[hardware/](hardware) => Contains schematics and designs\
[docs/](docs) => Documentation and pictures

## Instructions
Assembly and firmware installation instructions can be found [here](docs/hardware.md).

## Emulator
The PC Emulator builds from this branch:
```
cmake -S sim -B build-sim && cmake --build build-sim
./build-sim/ui
```
Otherwise a web simulator is available [here](https://ramez-hammad.github.io) 

## Gallery
<figure>
  <img src="docs/gallery/1.png">
  <figcaption><b>Figure 1:</b> The menu in the simulator </figcaption>
</figure>
<figure>
  <img src="docs/gallery/2.png">
  <figcaption><b>Figure 2:</b> Default screen in the simulator </figcaption>
</figure>
<figure>
  <img src="docs/gallery/3.png">
  <figcaption><b>Figure 3:</b> Variable definition menu </figcaption>
</figure>
<figure>
  <img src="docs/gallery/4.png">
  <figcaption><b>Figure 4:</b> Graph of sin(x) </figcaption>
</figure>
<figure>
  <img src="docs/gallery/5.png">
  <figcaption><b>Figure 5:</b> Graphs of sin(x), cos(x), tan(x) </figcaption>
</figure>
<figure>
  <img src="docs/gallery/6.png">
  <figcaption><b>Figure 6:</b> The function toolbox </figcaption>
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
