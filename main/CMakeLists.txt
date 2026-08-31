file(GLOB UI_SRC "../src/ui/*.c")
file(GLOB INTERPRETER_SRC "../src/core/interpreter/*.c")
list(REMOVE_ITEM INTERPRETER_SRC "${CMAKE_CURRENT_LIST_DIR}/../src/core/interpreter/repl.c")
file(GLOB PORT_SRC "../src/port/esp32/*.c")
file(GLOB FONT_SRC "../fonts/*.c")

idf_component_register(
        SRCS ${UI_SRC} ${INTERPRETER_SRC} ${PORT_SRC} ${FONT_SRC}
        INCLUDE_DIRS "../src/ui" "../src/core" "../src/core/interpreter" "../src/port" "../src/port/esp32"
        REQUIRES lvgl driver esp_lcd
)

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-parentheses -Wno-char-subscripts -Wno-switch)
