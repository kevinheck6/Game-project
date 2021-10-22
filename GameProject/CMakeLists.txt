cmake_minimum_required(VERSION 3.20)
project(Game-projecttest)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Game-projecttest "Source Files/main.cpp" "Source Files/Game.cpp" "Head Files/Game.h" "States/State.cpp" "States/State.h" "States/GameState.cpp" "States/GameState.h")

target_link_libraries(Game-projecttest sfml-graphics sfml-audio)
