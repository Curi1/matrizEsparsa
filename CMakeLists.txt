cmake_minimum_required(VERSION 3.25)
project(matrizEsparsa C)

set(CMAKE_C_STANDARD 11)

add_executable(matrizEsparsa main.c matriz.h matriz.c)
