<h1 align="center">EPGCv1.0</h1>

## Expandable Programmable Graphing Calculator
### Introduction
An open-source, expandable, graphing calculator, built from the ground up, 
based on the ESP32 microcontroller. The source code and the schematics have been released under the 
GPLv3 license.

## It aims to offer:
- A custom, lightning fast modular mathematical expression interpreter with many built-in
  functions 
- A modern and responsive UI built using LVGL
- 2D graphing
- An experience that is designed to be fully expandable and customizable

## Hardware
<img src="hardware/schematic.png" align="top">

The calculator is based on the ESP32 microcontroller, it features a TFT ILI9341 Display and 54  buttons dedicated to various functions.
The calculator is power by 4AAA batteries.

## Repository Overview
[main/](main) => Source code that includes the interpreter and the UI\
[components/](components) => Contains LVGL and drivers\
[fonts/](fonts) => Contains fonts used in the UI\
[hardware/](hardware) => Contains schematics and designs\
[docs/](docs) => Documentation and pictures

## Emulator
There exists also an emulator to allow users to have a look at the calculator before building it.

Instructions to install the PC Emulator can be found in the pc-simulator branch, otherwise a web simulator is available [here](https://ramez-hammad.github.io) 

## Gallery
Some screenshots from the calculator.
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
