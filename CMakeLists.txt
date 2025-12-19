cmake_minimum_required(VERSION 3.20)
project(temp_monitor VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(temp-monitor
  src/main.cpp
  src/parser.cpp
)

target_include_directories(temp-monitor PRIVATE src)

target_compile_options(temp-monitor PRIVATE -Wall -Wextra -Wpedantic)
