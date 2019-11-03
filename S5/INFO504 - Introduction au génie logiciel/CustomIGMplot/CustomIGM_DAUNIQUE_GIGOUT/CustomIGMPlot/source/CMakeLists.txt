
cmake_minimum_required(VERSION 3.9)
project(igmplot)

set(VMDFILEGENERATOR vmdFileGenerator.cpp vmdFileGenerator.h)
set(OUTPUT output.cpp output.h)
set(READER reader.cpp reader.h)
set(MAIN main.cpp main.h)

add_executable(igmplot ${MAIN} ${READER} ${OUTPUT} ${VMDFILEGENERATOR})

target_compile_options(igmplot PRIVATE -Werror  -ansi -Wall  -pedantic -std=c++11 -O2 -pg -g -DNo_OpenMP)
