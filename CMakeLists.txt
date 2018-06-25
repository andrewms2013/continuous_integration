cmake_minimum_required(VERSION 3.10)
project(continuous_integration C)

set(CMAKE_C_STANDARD 99)

add_library(continuous_integration library.c library.h)