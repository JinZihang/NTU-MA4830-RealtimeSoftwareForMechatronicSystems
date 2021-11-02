cmake_minimum_required(VERSION 3.20)
project(ca2 C)

set(CMAKE_C_STANDARD 11)

include_directories(functions)

add_executable(ca2
        functions/wave_generator_pcie.h
        main.c)
