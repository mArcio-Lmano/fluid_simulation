# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/talocha/C++/fluid_simulation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/talocha/C++/fluid_simulation/build

# Include any dependencies generated for this target.
include CMakeFiles/fluid_app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/fluid_app.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/fluid_app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fluid_app.dir/flags.make

CMakeFiles/fluid_app.dir/src/main.cpp.o: CMakeFiles/fluid_app.dir/flags.make
CMakeFiles/fluid_app.dir/src/main.cpp.o: /home/talocha/C++/fluid_simulation/src/main.cpp
CMakeFiles/fluid_app.dir/src/main.cpp.o: CMakeFiles/fluid_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/talocha/C++/fluid_simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fluid_app.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fluid_app.dir/src/main.cpp.o -MF CMakeFiles/fluid_app.dir/src/main.cpp.o.d -o CMakeFiles/fluid_app.dir/src/main.cpp.o -c /home/talocha/C++/fluid_simulation/src/main.cpp

CMakeFiles/fluid_app.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fluid_app.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/talocha/C++/fluid_simulation/src/main.cpp > CMakeFiles/fluid_app.dir/src/main.cpp.i

CMakeFiles/fluid_app.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fluid_app.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/talocha/C++/fluid_simulation/src/main.cpp -o CMakeFiles/fluid_app.dir/src/main.cpp.s

# Object files for target fluid_app
fluid_app_OBJECTS = \
"CMakeFiles/fluid_app.dir/src/main.cpp.o"

# External object files for target fluid_app
fluid_app_EXTERNAL_OBJECTS =

fluid_app: CMakeFiles/fluid_app.dir/src/main.cpp.o
fluid_app: CMakeFiles/fluid_app.dir/build.make
fluid_app: /usr/lib/libsfml-graphics.so.2.6.1
fluid_app: /usr/lib/libsfml-window.so.2.6.1
fluid_app: /usr/lib/libsfml-system.so.2.6.1
fluid_app: /usr/lib/libOpenCL.so
fluid_app: CMakeFiles/fluid_app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/talocha/C++/fluid_simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fluid_app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fluid_app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fluid_app.dir/build: fluid_app
.PHONY : CMakeFiles/fluid_app.dir/build

CMakeFiles/fluid_app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fluid_app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fluid_app.dir/clean

CMakeFiles/fluid_app.dir/depend:
	cd /home/talocha/C++/fluid_simulation/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/talocha/C++/fluid_simulation /home/talocha/C++/fluid_simulation /home/talocha/C++/fluid_simulation/build /home/talocha/C++/fluid_simulation/build /home/talocha/C++/fluid_simulation/build/CMakeFiles/fluid_app.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/fluid_app.dir/depend
