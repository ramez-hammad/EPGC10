<h1 align="center">EPGC10</h1>

## Expandable Programmable Graphing Calculator
An open-source programmable graphing calculator, built from the ground up

## It aims to offer:
- A lightning fast modular mathematical expression interpreter with many built in
  functions 
- A modern and responsive UI using LVGL
- 2D graphing, with touchscreen panning and zooming
- An experience that is designed to be fully expandable

## Project Structure
├── src/core/ # Interpreter\
├── tests/ # Unit tests using Unity\
├── docs/ # Documentation\
└── third_party/Unity/ # Unity git submodule\ 

## Planned Project Structure
├── src/core/ # Interpreter\
├── src/ui/ # UI\
├── tests/ # Unit tests using Unity\
├── third_party/Unity/ # Unity git submodule\ 
├── docs/ # Documentation\
├── platform/pc/ # UI initialization code for the PC simulator\ 
├── platform/esp32/ # UI initization code for the ESP32\
└── hardware/ # Hardware related files (Schematics, 3D models, etc.)\

## Development Plan

### Phase 1
1. Develop, test, and optimize the expression interpreter

2. Implement the graphing and other core calculator features

### Phase 2
1. Develop the modular UI using LVGL 
2. Integrate it with the interpreter and
core features 

### Phase 3
1. Choose hardware 
2. Design a schematic
3. Create 3D models for the case

### Phase 4
1. Integrate the UI software with the hardware

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
