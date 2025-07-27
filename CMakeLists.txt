cmake_minimum_required(VERSION 3.31.6)

project(EPGC10 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SRC_LVGL third_party/lvgl/src/*.c)

include_directories(
        third_party/lvgl/
        src/core/
        src/ui/
)

set(SRC_UI
        src/ui/ui.c
        src/core/interpreter.c
        src/core/parser.c
        src/core/lexer.c
        src/core/evaluator.c
        src/ui/button_matrix.c
        src/ui/button_matrix_callbacks.c
        src/ui/text.c
        src/ui/input_area.c
        src/ui/status_bar.c
        src/ui/screen_menu.c
        fonts/noto_sans_regular_14.c
        fonts/noto_sans_regular_16.c
        fonts/noto_sans_math_regular_comb_14.c
        fonts/noto_sans_math_regular_comb_16.c
)

set(SRC_TEST
        test/test_lexer.c
        src/core/lexer.c
        third_party/Unity/src/unity.c
)

# SDL2
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

# Build target
add_executable(ui ${SRC_UI} ${SRC_LVGL})
add_executable(test_lexer ${SRC_TEST})

# Link SDL2
target_link_libraries(ui ${SDL2_LIBRARIES} m)
