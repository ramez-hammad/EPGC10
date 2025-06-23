cmake_minimum_required(VERSION 4.0)

project(EPGC10 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

include_directories(src/core/)
include_directories(third_party/unity/src)

# Test executables
add_executable(test_lexer test/test_lexer.c src/core/lexer.c third_party/Unity/src/unity.c)
