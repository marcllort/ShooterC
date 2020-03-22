# cmake_minimum_required(VERSION <specify CMake version here>)
project(ShooterC C)

set(CMAKE_C_STANDARD 99)

add_executable(ShooterC main.c src/FAT16.c src/EXT2.c src/MainUtils.c include/EXT2.h include/FAT16.h include/MainUtils.h include/Types.h src/Utils.c include/Utils.h)