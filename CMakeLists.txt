cmake_minimum_required(VERSION 3.16)

# lvgl_esp32_drivers targets LVGL v8 and is not built; the display driver
# lives in main/ili9341.c on top of esp_lcd.
set(COMPONENTS main)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(EPGC10)

# LVGL logs use LV_PRIu32 which newlib's printf flags as -Wformat
idf_component_get_property(lvgl_lib lvgl COMPONENT_LIB)
target_compile_options(${lvgl_lib} PRIVATE -Wno-format)
