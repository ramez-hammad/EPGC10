<h1 align="center">EPGC10</h1>

## Expandable Programmable Graphing Calculator
An open-source, expandable, not yet programmable graphing calculator, built from the ground up

## It aims to offer:
- A lightning fast modular mathematical expression interpreter with many built in
  functions 
- A modern and responsive UI using LVGL
- 2D graphing
- An experience that is designed to be fully expandable

Currently, only the PC simulator has been implemented. In the future, an ESP32 version is planned for a physical calculator

## Install instructions
Dependencies: SDL for the PC simulator

Linux

```
git clone --recurse-submodules https://github.com/ramez-hammad/EPGC10.git
cd EPGC10
mkdir build && cd build
cmake ..
make
./EPGC10
```

## Unit Testing

To build and run unit tests:

```
git clone --recurse-submodules https://github.com/ramez-hammad/EPGC10.git
cd EPGC10
mkdir build && cd build
cmake ..
make
./test_$(TEST_NAME)
```
