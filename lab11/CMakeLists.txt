cmake_minimum_required(VERSION 3.10)
project(Lab11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Werror -pedantic)

add_executable(lab11 main.cpp)
