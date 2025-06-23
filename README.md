# EPGC10
## **E**xpandable **P**rogrammable **G**raphing **C**alculator 10
An open-source programmable graphing calculator that is based on the ESP32-S3 microcontroller

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
