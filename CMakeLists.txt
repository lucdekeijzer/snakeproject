cmake_minimum_required(VERSION 3.20)
project(snakeproject)

set(CMAKE_CXX_STANDARD 14)

add_executable(snakeproject main.cpp grid.h snake.h fruits.h graphics.h)
