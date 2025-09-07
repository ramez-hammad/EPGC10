file(GLOB_RECURSE UI_SRC "ui/*.c" "core/*.c")

idf_component_register(
        SRCS "main.c" ${UI_SRC}
        INCLUDE_DIRS "." "ui" "core"
        REQUIRES lvgl lvgl_esp32_drivers
)
