# cmake_minimum_required(VERSION <specify CMake version here>)
project(ShooterC C)

set(CMAKE_C_STANDARD 99)

add_executable(ShooterC main.c src/FAT16.c src/EXT2.c src/Utils.c include/EXT2.h include/FAT16.h include/Utils.h include/Types.h)