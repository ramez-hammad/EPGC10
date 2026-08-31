cmake_minimum_required(VERSION 3.20)

project(EPGC10 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(REPO_ROOT ${CMAKE_CURRENT_LIST_DIR}/..)

add_compile_definitions(EPGC10_SDL)

file(GLOB_RECURSE SRC_LVGL ${REPO_ROOT}/components/lvgl/src/*.c)

file(GLOB SRC_UI ${REPO_ROOT}/src/ui/*.c)
file(GLOB SRC_INTERPRETER ${REPO_ROOT}/src/core/interpreter/*.c)
list(REMOVE_ITEM SRC_INTERPRETER ${REPO_ROOT}/src/core/interpreter/repl.c)
file(GLOB SRC_FONTS ${REPO_ROOT}/fonts/*.c)
file(GLOB SRC_PORT ${REPO_ROOT}/src/port/sdl/*.c)

include_directories(
        ${REPO_ROOT}/components/lvgl
        ${REPO_ROOT}/src/ui
        ${REPO_ROOT}/src/core/interpreter
        ${REPO_ROOT}/src/port
        ${REPO_ROOT}/src/port/sdl
)

set(SRC_TEST
        ${REPO_ROOT}/test/test_lexer.c
        ${REPO_ROOT}/src/core/interpreter/lexer.c
        ${REPO_ROOT}/third_party/Unity/src/unity.c
)

# SDL2
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

# Build targets
add_executable(ui ${SRC_UI} ${SRC_INTERPRETER} ${SRC_FONTS} ${SRC_PORT} ${SRC_LVGL})
add_executable(test_lexer ${SRC_TEST})
add_executable(repl ${REPO_ROOT}/src/core/interpreter/repl.c ${SRC_INTERPRETER})

target_include_directories(test_lexer PRIVATE ${REPO_ROOT}/third_party/Unity/src)

# Link SDL2
target_link_libraries(ui ${SDL2_LIBRARIES} m)
target_link_libraries(repl m)
