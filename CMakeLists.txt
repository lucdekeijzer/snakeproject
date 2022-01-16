cmake_minimum_required(VERSION 3.20)
project(snakeproject)

set(CMAKE_CXX_STANDARD 14)

add_executable(snakeproject main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR D:/Universiteit/Jaar 3 Sem 1/C++/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(D:/Universiteit/Jaar 3 Sem 1/C++/SFML-2.5.1/include)
target_link_libraries(snakeproject sfml-system sfml-window sfml-graphics sfml-audio)