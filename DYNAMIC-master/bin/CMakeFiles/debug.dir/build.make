# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin

# Include any dependencies generated for this target.
include CMakeFiles/debug.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/debug.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/debug.dir/flags.make

CMakeFiles/debug.dir/debug.cpp.o: CMakeFiles/debug.dir/flags.make
CMakeFiles/debug.dir/debug.cpp.o: ../debug.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/debug.dir/debug.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/debug.dir/debug.cpp.o -c /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/debug.cpp

CMakeFiles/debug.dir/debug.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/debug.dir/debug.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/debug.cpp > CMakeFiles/debug.dir/debug.cpp.i

CMakeFiles/debug.dir/debug.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/debug.dir/debug.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/debug.cpp -o CMakeFiles/debug.dir/debug.cpp.s

CMakeFiles/debug.dir/debug.cpp.o.requires:

.PHONY : CMakeFiles/debug.dir/debug.cpp.o.requires

CMakeFiles/debug.dir/debug.cpp.o.provides: CMakeFiles/debug.dir/debug.cpp.o.requires
	$(MAKE) -f CMakeFiles/debug.dir/build.make CMakeFiles/debug.dir/debug.cpp.o.provides.build
.PHONY : CMakeFiles/debug.dir/debug.cpp.o.provides

CMakeFiles/debug.dir/debug.cpp.o.provides.build: CMakeFiles/debug.dir/debug.cpp.o


# Object files for target debug
debug_OBJECTS = \
"CMakeFiles/debug.dir/debug.cpp.o"

# External object files for target debug
debug_EXTERNAL_OBJECTS =

debug: CMakeFiles/debug.dir/debug.cpp.o
debug: CMakeFiles/debug.dir/build.make
debug: CMakeFiles/debug.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable debug"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/debug.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/debug.dir/build: debug

.PHONY : CMakeFiles/debug.dir/build

CMakeFiles/debug.dir/requires: CMakeFiles/debug.dir/debug.cpp.o.requires

.PHONY : CMakeFiles/debug.dir/requires

CMakeFiles/debug.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/debug.dir/cmake_clean.cmake
.PHONY : CMakeFiles/debug.dir/clean

CMakeFiles/debug.dir/depend:
	cd /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin/CMakeFiles/debug.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/debug.dir/depend

