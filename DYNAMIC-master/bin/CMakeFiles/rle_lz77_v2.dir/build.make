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
include CMakeFiles/rle_lz77_v2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rle_lz77_v2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rle_lz77_v2.dir/flags.make

CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o: CMakeFiles/rle_lz77_v2.dir/flags.make
CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o: ../rle_lz77_v2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o -c /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/rle_lz77_v2.cpp

CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/rle_lz77_v2.cpp > CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.i

CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/rle_lz77_v2.cpp -o CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.s

CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o.requires:

.PHONY : CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o.requires

CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o.provides: CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o.requires
	$(MAKE) -f CMakeFiles/rle_lz77_v2.dir/build.make CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o.provides.build
.PHONY : CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o.provides

CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o.provides.build: CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o


# Object files for target rle_lz77_v2
rle_lz77_v2_OBJECTS = \
"CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o"

# External object files for target rle_lz77_v2
rle_lz77_v2_EXTERNAL_OBJECTS =

rle_lz77_v2: CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o
rle_lz77_v2: CMakeFiles/rle_lz77_v2.dir/build.make
rle_lz77_v2: CMakeFiles/rle_lz77_v2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rle_lz77_v2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rle_lz77_v2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rle_lz77_v2.dir/build: rle_lz77_v2

.PHONY : CMakeFiles/rle_lz77_v2.dir/build

CMakeFiles/rle_lz77_v2.dir/requires: CMakeFiles/rle_lz77_v2.dir/rle_lz77_v2.cpp.o.requires

.PHONY : CMakeFiles/rle_lz77_v2.dir/requires

CMakeFiles/rle_lz77_v2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rle_lz77_v2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rle_lz77_v2.dir/clean

CMakeFiles/rle_lz77_v2.dir/depend:
	cd /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin /home/borja/Escritorio/k2treeDinamic/DYNAMIC-master/bin/CMakeFiles/rle_lz77_v2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rle_lz77_v2.dir/depend
