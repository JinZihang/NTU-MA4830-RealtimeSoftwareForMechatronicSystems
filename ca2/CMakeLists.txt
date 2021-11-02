cmake_minimum_required(VERSION 3.20)
project(metronome)

set(CMAKE_C_STANDARD 11)

add_executable(metronome main.c)
add_library(metronome_lib initialization.c wave_generator_pcie.c helper.c)
target_link_libraries(metronome metronome_lib)
