cmake_minimum_required(VERSION 3.20)
project(GameProject)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(GameProject main.cpp Game.cpp Game.h)

target_link_libraries(GameProject sfml-graphics sfml-audio)
