cmake_minimum_required(VERSION 3.20)
project(Game-projecttest)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Game-projecttest "Source Files/main.cpp" "Source Files/Game.cpp" "Head Files/Game.h" "States/State.cpp" "States/State.h" "States/GameState.cpp" "States/GameState.h" Entities/Entity.cpp Entities/Entity.h States/MainMenuState.cpp States/MainMenuState.h Resources/Button.cpp Resources/Button.h Entities/Player.cpp Entities/Player.h Components/MovementComponent.cpp Components/MovementComponent.h Components/AnimationComponent.cpp Components/AnimationComponent.h "States/EditorState.cpp" "States/EditorState.h" Components/HitBoxComponent.cpp Components/HitBoxComponent.h Tile/Tile.cpp Tile/Tile.h GUI/PauseMenu.cpp GUI/PauseMenu.h States/SettingsState.cpp States/SettingsState.h Map/TileMap.cpp Map/TileMap.h "Head Files/PreCompiledHeaders.cpp" "Head Files/PreCompiledHeaders.h")

target_link_libraries(Game-projecttest sfml-graphics sfml-audio)
