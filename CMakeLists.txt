cmake_minimum_required(VERSION 3.20)
project(NTU_MA4830_RealtimeSoftwareForMechatronicSystems C)

set(CMAKE_C_STANDARD 11)

include_directories(ca1/datatypes)
include_directories(ca1/functions)
include_directories(ca2/functions)

add_executable(NTU_MA4830_RealtimeSoftwareForMechatronicSystems
        ca1/datatypes/enum.h
        ca1/datatypes/struct.h
        ca1/functions/calculation.h
        ca1/functions/print.h
        ca1/functions/selection.h
        ca1/main.c
        ca2/functions/wave_generator_pcie.h
        ca2/main.c)
