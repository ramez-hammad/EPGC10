file(GLOB UI_SRC "ui/*.c")
file(GLOB INTERPRETER_SRC "core/interpreter/*.c")
list(REMOVE_ITEM INTERPRETER_SRC "${CMAKE_CURRENT_LIST_DIR}/core/interpreter/repl.c")
file(GLOB FONT_SRC "../fonts/*.c")

idf_component_register(
        SRCS "main.c" "ili9341.c" ${UI_SRC} ${INTERPRETER_SRC} ${FONT_SRC}
        INCLUDE_DIRS "." "ui" "core" "core/interpreter"
        REQUIRES lvgl driver esp_lcd
)

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-parentheses -Wno-char-subscripts -Wno-switch)
