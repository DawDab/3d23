# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dawdab/3d23

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dawdab/3d23/build

# Include any dependencies generated for this target.
include src/Assignments/Triangle/CMakeFiles/Triangle.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/Assignments/Triangle/CMakeFiles/Triangle.dir/compiler_depend.make

# Include the progress variables for this target.
include src/Assignments/Triangle/CMakeFiles/Triangle.dir/progress.make

# Include the compile flags for this target's objects.
include src/Assignments/Triangle/CMakeFiles/Triangle.dir/flags.make

src/Assignments/Triangle/CMakeFiles/Triangle.dir/main.cpp.o: src/Assignments/Triangle/CMakeFiles/Triangle.dir/flags.make
src/Assignments/Triangle/CMakeFiles/Triangle.dir/main.cpp.o: ../src/Assignments/Triangle/main.cpp
src/Assignments/Triangle/CMakeFiles/Triangle.dir/main.cpp.o: src/Assignments/Triangle/CMakeFiles/Triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dawdab/3d23/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Assignments/Triangle/CMakeFiles/Triangle.dir/main.cpp.o"
	cd /home/dawdab/3d23/build/src/Assignments/Triangle && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Assignments/Triangle/CMakeFiles/Triangle.dir/main.cpp.o -MF CMakeFiles/Triangle.dir/main.cpp.o.d -o CMakeFiles/Triangle.dir/main.cpp.o -c /home/dawdab/3d23/src/Assignments/Triangle/main.cpp

src/Assignments/Triangle/CMakeFiles/Triangle.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Triangle.dir/main.cpp.i"
	cd /home/dawdab/3d23/build/src/Assignments/Triangle && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dawdab/3d23/src/Assignments/Triangle/main.cpp > CMakeFiles/Triangle.dir/main.cpp.i

src/Assignments/Triangle/CMakeFiles/Triangle.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Triangle.dir/main.cpp.s"
	cd /home/dawdab/3d23/build/src/Assignments/Triangle && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dawdab/3d23/src/Assignments/Triangle/main.cpp -o CMakeFiles/Triangle.dir/main.cpp.s

src/Assignments/Triangle/CMakeFiles/Triangle.dir/app.cpp.o: src/Assignments/Triangle/CMakeFiles/Triangle.dir/flags.make
src/Assignments/Triangle/CMakeFiles/Triangle.dir/app.cpp.o: ../src/Assignments/Triangle/app.cpp
src/Assignments/Triangle/CMakeFiles/Triangle.dir/app.cpp.o: src/Assignments/Triangle/CMakeFiles/Triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dawdab/3d23/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/Assignments/Triangle/CMakeFiles/Triangle.dir/app.cpp.o"
	cd /home/dawdab/3d23/build/src/Assignments/Triangle && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Assignments/Triangle/CMakeFiles/Triangle.dir/app.cpp.o -MF CMakeFiles/Triangle.dir/app.cpp.o.d -o CMakeFiles/Triangle.dir/app.cpp.o -c /home/dawdab/3d23/src/Assignments/Triangle/app.cpp

src/Assignments/Triangle/CMakeFiles/Triangle.dir/app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Triangle.dir/app.cpp.i"
	cd /home/dawdab/3d23/build/src/Assignments/Triangle && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dawdab/3d23/src/Assignments/Triangle/app.cpp > CMakeFiles/Triangle.dir/app.cpp.i

src/Assignments/Triangle/CMakeFiles/Triangle.dir/app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Triangle.dir/app.cpp.s"
	cd /home/dawdab/3d23/build/src/Assignments/Triangle && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dawdab/3d23/src/Assignments/Triangle/app.cpp -o CMakeFiles/Triangle.dir/app.cpp.s

# Object files for target Triangle
Triangle_OBJECTS = \
"CMakeFiles/Triangle.dir/main.cpp.o" \
"CMakeFiles/Triangle.dir/app.cpp.o"

# External object files for target Triangle
Triangle_EXTERNAL_OBJECTS = \
"/home/dawdab/3d23/build/CMakeFiles/glad.dir/src/3rdParty/glad/glad_4_1/glad/src/gl.c.o"

src/Assignments/Triangle/Triangle: src/Assignments/Triangle/CMakeFiles/Triangle.dir/main.cpp.o
src/Assignments/Triangle/Triangle: src/Assignments/Triangle/CMakeFiles/Triangle.dir/app.cpp.o
src/Assignments/Triangle/Triangle: CMakeFiles/glad.dir/src/3rdParty/glad/glad_4_1/glad/src/gl.c.o
src/Assignments/Triangle/Triangle: src/Assignments/Triangle/CMakeFiles/Triangle.dir/build.make
src/Assignments/Triangle/Triangle: /usr/lib/x86_64-linux-gnu/libGL.so
src/Assignments/Triangle/Triangle: _deps/glfw-build/src/libglfw3.a
src/Assignments/Triangle/Triangle: src/Application/libapplication.a
src/Assignments/Triangle/Triangle: /usr/lib/x86_64-linux-gnu/libGL.so
src/Assignments/Triangle/Triangle: _deps/glfw-build/src/libglfw3.a
src/Assignments/Triangle/Triangle: /usr/lib/x86_64-linux-gnu/librt.a
src/Assignments/Triangle/Triangle: /usr/lib/x86_64-linux-gnu/libm.so
src/Assignments/Triangle/Triangle: src/Assignments/Triangle/CMakeFiles/Triangle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dawdab/3d23/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Triangle"
	cd /home/dawdab/3d23/build/src/Assignments/Triangle && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Triangle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Assignments/Triangle/CMakeFiles/Triangle.dir/build: src/Assignments/Triangle/Triangle
.PHONY : src/Assignments/Triangle/CMakeFiles/Triangle.dir/build

src/Assignments/Triangle/CMakeFiles/Triangle.dir/clean:
	cd /home/dawdab/3d23/build/src/Assignments/Triangle && $(CMAKE_COMMAND) -P CMakeFiles/Triangle.dir/cmake_clean.cmake
.PHONY : src/Assignments/Triangle/CMakeFiles/Triangle.dir/clean

src/Assignments/Triangle/CMakeFiles/Triangle.dir/depend:
	cd /home/dawdab/3d23/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dawdab/3d23 /home/dawdab/3d23/src/Assignments/Triangle /home/dawdab/3d23/build /home/dawdab/3d23/build/src/Assignments/Triangle /home/dawdab/3d23/build/src/Assignments/Triangle/CMakeFiles/Triangle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Assignments/Triangle/CMakeFiles/Triangle.dir/depend

