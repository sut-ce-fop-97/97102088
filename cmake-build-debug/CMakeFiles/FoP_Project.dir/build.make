# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/Lenovo/.CLion2018.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Lenovo/.CLion2018.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/FoP_Project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FoP_Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FoP_Project.dir/flags.make

CMakeFiles/FoP_Project.dir/src/logic.c.o: CMakeFiles/FoP_Project.dir/flags.make
CMakeFiles/FoP_Project.dir/src/logic.c.o: ../src/logic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/FoP_Project.dir/src/logic.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FoP_Project.dir/src/logic.c.o   -c "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/logic.c"

CMakeFiles/FoP_Project.dir/src/logic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FoP_Project.dir/src/logic.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/logic.c" > CMakeFiles/FoP_Project.dir/src/logic.c.i

CMakeFiles/FoP_Project.dir/src/logic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FoP_Project.dir/src/logic.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/logic.c" -o CMakeFiles/FoP_Project.dir/src/logic.c.s

CMakeFiles/FoP_Project.dir/src/main.c.o: CMakeFiles/FoP_Project.dir/flags.make
CMakeFiles/FoP_Project.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/FoP_Project.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FoP_Project.dir/src/main.c.o   -c "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/main.c"

CMakeFiles/FoP_Project.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FoP_Project.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/main.c" > CMakeFiles/FoP_Project.dir/src/main.c.i

CMakeFiles/FoP_Project.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FoP_Project.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/main.c" -o CMakeFiles/FoP_Project.dir/src/main.c.s

CMakeFiles/FoP_Project.dir/src/physics.c.o: CMakeFiles/FoP_Project.dir/flags.make
CMakeFiles/FoP_Project.dir/src/physics.c.o: ../src/physics.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/FoP_Project.dir/src/physics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FoP_Project.dir/src/physics.c.o   -c "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/physics.c"

CMakeFiles/FoP_Project.dir/src/physics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FoP_Project.dir/src/physics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/physics.c" > CMakeFiles/FoP_Project.dir/src/physics.c.i

CMakeFiles/FoP_Project.dir/src/physics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FoP_Project.dir/src/physics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/physics.c" -o CMakeFiles/FoP_Project.dir/src/physics.c.s

CMakeFiles/FoP_Project.dir/src/simple_snake.c.o: CMakeFiles/FoP_Project.dir/flags.make
CMakeFiles/FoP_Project.dir/src/simple_snake.c.o: ../src/simple_snake.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/FoP_Project.dir/src/simple_snake.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FoP_Project.dir/src/simple_snake.c.o   -c "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/simple_snake.c"

CMakeFiles/FoP_Project.dir/src/simple_snake.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FoP_Project.dir/src/simple_snake.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/simple_snake.c" > CMakeFiles/FoP_Project.dir/src/simple_snake.c.i

CMakeFiles/FoP_Project.dir/src/simple_snake.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FoP_Project.dir/src/simple_snake.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/simple_snake.c" -o CMakeFiles/FoP_Project.dir/src/simple_snake.c.s

CMakeFiles/FoP_Project.dir/src/view.c.o: CMakeFiles/FoP_Project.dir/flags.make
CMakeFiles/FoP_Project.dir/src/view.c.o: ../src/view.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/FoP_Project.dir/src/view.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FoP_Project.dir/src/view.c.o   -c "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/view.c"

CMakeFiles/FoP_Project.dir/src/view.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FoP_Project.dir/src/view.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/view.c" > CMakeFiles/FoP_Project.dir/src/view.c.i

CMakeFiles/FoP_Project.dir/src/view.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FoP_Project.dir/src/view.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/src/view.c" -o CMakeFiles/FoP_Project.dir/src/view.c.s

# Object files for target FoP_Project
FoP_Project_OBJECTS = \
"CMakeFiles/FoP_Project.dir/src/logic.c.o" \
"CMakeFiles/FoP_Project.dir/src/main.c.o" \
"CMakeFiles/FoP_Project.dir/src/physics.c.o" \
"CMakeFiles/FoP_Project.dir/src/simple_snake.c.o" \
"CMakeFiles/FoP_Project.dir/src/view.c.o"

# External object files for target FoP_Project
FoP_Project_EXTERNAL_OBJECTS =

FoP_Project.exe: CMakeFiles/FoP_Project.dir/src/logic.c.o
FoP_Project.exe: CMakeFiles/FoP_Project.dir/src/main.c.o
FoP_Project.exe: CMakeFiles/FoP_Project.dir/src/physics.c.o
FoP_Project.exe: CMakeFiles/FoP_Project.dir/src/simple_snake.c.o
FoP_Project.exe: CMakeFiles/FoP_Project.dir/src/view.c.o
FoP_Project.exe: CMakeFiles/FoP_Project.dir/build.make
FoP_Project.exe: ../sdl2/sdl2-lib/libSDL2.a
FoP_Project.exe: ../sdl2/sdl2-lib/libSDL2main.a
FoP_Project.exe: ../sdl2/sdl2-gfx-lib/libsdl-gfx.a
FoP_Project.exe: CMakeFiles/FoP_Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable FoP_Project.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FoP_Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FoP_Project.dir/build: FoP_Project.exe

.PHONY : CMakeFiles/FoP_Project.dir/build

CMakeFiles/FoP_Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FoP_Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FoP_Project.dir/clean

CMakeFiles/FoP_Project.dir/depend:
	cd "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project" "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project" "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/cmake-build-debug" "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/cmake-build-debug" "/cygdrive/d/Amir Abbas's Documents/FoP/FoP_Project/cmake-build-debug/CMakeFiles/FoP_Project.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/FoP_Project.dir/depend

