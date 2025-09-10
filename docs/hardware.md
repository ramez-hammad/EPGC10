# Hardware Documentation

## Purpose
This file contains an overview of the hardware and instructions for assembly and installation.

## Overview / Schematic
<img src="../hardware/schematic.png" align="top">

## Bill of Materials
| Item | Description               | Quantity | Notes                                                         |
|------|---------------------------|----------|---------------------------------------------------------------|
| 1    | **NodeMCU-32S (ESP32)**   | 1        | Main microcontroller running the calculator firmware          |
| 2    | **Push button switches**  | 54       | Used for calculator input                                     |
| 3    | **ILI9341 TFT LCD (SPI)** | 1        | 2.8″ SPI display module                                       |
| 4    | **4×AAA Battery Holder**  | 1        | Provides ~6V before ESP32 onboard regulator                   |
| 5    | **AAA Batteries**         | 4        | Power source for portable operation                           |
| 6    | **Wires**                 | ~        | For connections                                               |
| 7    | **Power Switch**          | 1        | ~                                                             |
| 8    | **Perfboard**             | 1        | ~                                                             |
| 9    | **Sockets**               | 2        | Solder them on and connect ESP32, LCD to ensure repairability |
| 10   | **Enclosure** (optional)  | 1        | Get creative!                                                 |

## Assembly / Installation Instructions 

### 1) Prepare components
Lay out the ESP32 board, keypad, LCD, wires, battery holder, sockets and perfboard.

### 2) Wiring the LCD and ESP32
Solder the sockets on to the perfboard, connect each pin to the ESP32 according to the schematic.

### 3) Wiring the keypad
The keypad is a matrix of rows and columns, there are 9 rows and 6 columns, connect each row and column to the appropriate ESP32 pin according to the schematic.

### 4) Power wiring
Battery + ->  ESP32 5V\
Battery - ->  ESP32 GND

Place switch inline on the positive wire.

### Optional
Design and 3D print an enclosure to house the hardware.

### 5)
Insert 4 AAA batteries\
Power on the unit\
Upload firmware via USB using ESP-IDF

If issues arise, create an issue on Github.