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
include CMakeFiles/h0_lz77.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/h0_lz77.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/h0_lz77.dir/flags.make

CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o: CMakeFiles/h0_lz77.dir/flags.make
CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o: ../h0_lz77.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o -c /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/h0_lz77.cpp

CMakeFiles/h0_lz77.dir/h0_lz77.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/h0_lz77.dir/h0_lz77.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/h0_lz77.cpp > CMakeFiles/h0_lz77.dir/h0_lz77.cpp.i

CMakeFiles/h0_lz77.dir/h0_lz77.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/h0_lz77.dir/h0_lz77.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/h0_lz77.cpp -o CMakeFiles/h0_lz77.dir/h0_lz77.cpp.s

CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o.requires:

.PHONY : CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o.requires

CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o.provides: CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o.requires
	$(MAKE) -f CMakeFiles/h0_lz77.dir/build.make CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o.provides.build
.PHONY : CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o.provides

CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o.provides.build: CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o


# Object files for target h0_lz77
h0_lz77_OBJECTS = \
"CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o"

# External object files for target h0_lz77
h0_lz77_EXTERNAL_OBJECTS =

h0_lz77: CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o
h0_lz77: CMakeFiles/h0_lz77.dir/build.make
h0_lz77: CMakeFiles/h0_lz77.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable h0_lz77"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/h0_lz77.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/h0_lz77.dir/build: h0_lz77

.PHONY : CMakeFiles/h0_lz77.dir/build

CMakeFiles/h0_lz77.dir/requires: CMakeFiles/h0_lz77.dir/h0_lz77.cpp.o.requires

.PHONY : CMakeFiles/h0_lz77.dir/requires

CMakeFiles/h0_lz77.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/h0_lz77.dir/cmake_clean.cmake
.PHONY : CMakeFiles/h0_lz77.dir/clean

CMakeFiles/h0_lz77.dir/depend:
	cd /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin/CMakeFiles/h0_lz77.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/h0_lz77.dir/depend

