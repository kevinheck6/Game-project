# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/169/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/169/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kevin/CLionProjects/Game-projecttest/GameProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Game-projecttest.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Game-projecttest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Game-projecttest.dir/flags.make

CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.o: ../Source\ Files/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.o -c "/home/kevin/CLionProjects/Game-projecttest/GameProject/Source Files/main.cpp"

CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/kevin/CLionProjects/Game-projecttest/GameProject/Source Files/main.cpp" > CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.i

CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/kevin/CLionProjects/Game-projecttest/GameProject/Source Files/main.cpp" -o CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.s

CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.o: ../Source\ Files/Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.o -c "/home/kevin/CLionProjects/Game-projecttest/GameProject/Source Files/Game.cpp"

CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/kevin/CLionProjects/Game-projecttest/GameProject/Source Files/Game.cpp" > CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.i

CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/kevin/CLionProjects/Game-projecttest/GameProject/Source Files/Game.cpp" -o CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.s

CMakeFiles/Game-projecttest.dir/States/State.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/States/State.cpp.o: ../States/State.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Game-projecttest.dir/States/State.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/States/State.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/States/State.cpp

CMakeFiles/Game-projecttest.dir/States/State.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/States/State.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/States/State.cpp > CMakeFiles/Game-projecttest.dir/States/State.cpp.i

CMakeFiles/Game-projecttest.dir/States/State.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/States/State.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/States/State.cpp -o CMakeFiles/Game-projecttest.dir/States/State.cpp.s

CMakeFiles/Game-projecttest.dir/States/GameState.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/States/GameState.cpp.o: ../States/GameState.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Game-projecttest.dir/States/GameState.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/States/GameState.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/States/GameState.cpp

CMakeFiles/Game-projecttest.dir/States/GameState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/States/GameState.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/States/GameState.cpp > CMakeFiles/Game-projecttest.dir/States/GameState.cpp.i

CMakeFiles/Game-projecttest.dir/States/GameState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/States/GameState.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/States/GameState.cpp -o CMakeFiles/Game-projecttest.dir/States/GameState.cpp.s

CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.o: ../Entities/Entity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/Entities/Entity.cpp

CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/Entities/Entity.cpp > CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.i

CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/Entities/Entity.cpp -o CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.s

CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.o: ../States/MainMenuState.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/States/MainMenuState.cpp

CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/States/MainMenuState.cpp > CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.i

CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/States/MainMenuState.cpp -o CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.s

CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.o: ../Resources/Button.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/Resources/Button.cpp

CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/Resources/Button.cpp > CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.i

CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/Resources/Button.cpp -o CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.s

CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.o: ../Entities/Player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/Entities/Player.cpp

CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/Entities/Player.cpp > CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.i

CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/Entities/Player.cpp -o CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.s

CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.o: ../Components/MovementComponent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/Components/MovementComponent.cpp

CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/Components/MovementComponent.cpp > CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.i

CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/Components/MovementComponent.cpp -o CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.s

CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.o: ../Components/AnimationComponent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/Components/AnimationComponent.cpp

CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/Components/AnimationComponent.cpp > CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.i

CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/Components/AnimationComponent.cpp -o CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.s

CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.o: ../States/EditorState.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/States/EditorState.cpp

CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/States/EditorState.cpp > CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.i

CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/States/EditorState.cpp -o CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.s

CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.o: ../Components/HitBoxComponent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/Components/HitBoxComponent.cpp

CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/Components/HitBoxComponent.cpp > CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.i

CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/Components/HitBoxComponent.cpp -o CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.s

CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.o: ../Tile/Tile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/Tile/Tile.cpp

CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/Tile/Tile.cpp > CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.i

CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/Tile/Tile.cpp -o CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.s

CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.o: CMakeFiles/Game-projecttest.dir/flags.make
CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.o: ../GUI/PauseMenu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.o -c /home/kevin/CLionProjects/Game-projecttest/GameProject/GUI/PauseMenu.cpp

CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/CLionProjects/Game-projecttest/GameProject/GUI/PauseMenu.cpp > CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.i

CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/CLionProjects/Game-projecttest/GameProject/GUI/PauseMenu.cpp -o CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.s

# Object files for target Game-projecttest
Game__projecttest_OBJECTS = \
"CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.o" \
"CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.o" \
"CMakeFiles/Game-projecttest.dir/States/State.cpp.o" \
"CMakeFiles/Game-projecttest.dir/States/GameState.cpp.o" \
"CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.o" \
"CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.o" \
"CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.o" \
"CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.o" \
"CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.o" \
"CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.o" \
"CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.o" \
"CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.o" \
"CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.o" \
"CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.o"

# External object files for target Game-projecttest
Game__projecttest_EXTERNAL_OBJECTS =

Game-projecttest: CMakeFiles/Game-projecttest.dir/Source_Files/main.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/Source_Files/Game.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/States/State.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/States/GameState.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/Entities/Entity.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/States/MainMenuState.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/Resources/Button.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/Entities/Player.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/Components/MovementComponent.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/Components/AnimationComponent.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/States/EditorState.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/Components/HitBoxComponent.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/Tile/Tile.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/GUI/PauseMenu.cpp.o
Game-projecttest: CMakeFiles/Game-projecttest.dir/build.make
Game-projecttest: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
Game-projecttest: /usr/lib/x86_64-linux-gnu/libsfml-audio.so.2.5.1
Game-projecttest: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
Game-projecttest: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
Game-projecttest: CMakeFiles/Game-projecttest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable Game-projecttest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Game-projecttest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Game-projecttest.dir/build: Game-projecttest
.PHONY : CMakeFiles/Game-projecttest.dir/build

CMakeFiles/Game-projecttest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Game-projecttest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Game-projecttest.dir/clean

CMakeFiles/Game-projecttest.dir/depend:
	cd /home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kevin/CLionProjects/Game-projecttest/GameProject /home/kevin/CLionProjects/Game-projecttest/GameProject /home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug /home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug /home/kevin/CLionProjects/Game-projecttest/GameProject/cmake-build-debug/CMakeFiles/Game-projecttest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Game-projecttest.dir/depend

