<h1 align="center">EPGC10</h1>
<p align="center">
  <b>Expandable Programmable Graphing Calculator</b><br>
  An open-source programmable graphing calculator, built from the ground up
</p>

## It aims to offer:
- A lightning fast modular mathematical expression interpreter with many built in
  functions 
- A modern and responsive UI using LVGL
- 2D graphing, with touchscreen panning and zooming
- An experience that is designed to be fully expandable

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
