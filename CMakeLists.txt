cmake_minimum_required(VERSION 3.31.6)

project(EPGC10 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

include_directories(src/core/interpreter/)
include_directories(src/core/grapher/)
include_directories(third_party/unity/src)

# Test executables
add_executable(test_lexer test/test_lexer.c src/core/interpreter/lexer.c third_party/Unity/src/unity.c)
