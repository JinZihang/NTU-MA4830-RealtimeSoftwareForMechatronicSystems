cmake_minimum_required(VERSION 3.20)
project(ca1 C)

set(CMAKE_C_STANDARD 11)

include_directories(datatypes)
include_directories(functions)

add_executable(ca1
        datatypes/enum.h
        datatypes/struct.h
        functions/calculation.h
        functions/print.h
        functions/selection.h
        main.c)
