# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/csuser/CPSC223/hw5-colleenlemak11

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/csuser/CPSC223/hw5-colleenlemak11

# Include any dependencies generated for this target.
include CMakeFiles/hw5_perf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw5_perf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw5_perf.dir/flags.make

CMakeFiles/hw5_perf.dir/hw5_perf.cpp.o: CMakeFiles/hw5_perf.dir/flags.make
CMakeFiles/hw5_perf.dir/hw5_perf.cpp.o: hw5_perf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csuser/CPSC223/hw5-colleenlemak11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw5_perf.dir/hw5_perf.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw5_perf.dir/hw5_perf.cpp.o -c /home/csuser/CPSC223/hw5-colleenlemak11/hw5_perf.cpp

CMakeFiles/hw5_perf.dir/hw5_perf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw5_perf.dir/hw5_perf.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/csuser/CPSC223/hw5-colleenlemak11/hw5_perf.cpp > CMakeFiles/hw5_perf.dir/hw5_perf.cpp.i

CMakeFiles/hw5_perf.dir/hw5_perf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw5_perf.dir/hw5_perf.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/csuser/CPSC223/hw5-colleenlemak11/hw5_perf.cpp -o CMakeFiles/hw5_perf.dir/hw5_perf.cpp.s

CMakeFiles/hw5_perf.dir/util.cpp.o: CMakeFiles/hw5_perf.dir/flags.make
CMakeFiles/hw5_perf.dir/util.cpp.o: util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csuser/CPSC223/hw5-colleenlemak11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hw5_perf.dir/util.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw5_perf.dir/util.cpp.o -c /home/csuser/CPSC223/hw5-colleenlemak11/util.cpp

CMakeFiles/hw5_perf.dir/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw5_perf.dir/util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/csuser/CPSC223/hw5-colleenlemak11/util.cpp > CMakeFiles/hw5_perf.dir/util.cpp.i

CMakeFiles/hw5_perf.dir/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw5_perf.dir/util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/csuser/CPSC223/hw5-colleenlemak11/util.cpp -o CMakeFiles/hw5_perf.dir/util.cpp.s

# Object files for target hw5_perf
hw5_perf_OBJECTS = \
"CMakeFiles/hw5_perf.dir/hw5_perf.cpp.o" \
"CMakeFiles/hw5_perf.dir/util.cpp.o"

# External object files for target hw5_perf
hw5_perf_EXTERNAL_OBJECTS =

hw5_perf: CMakeFiles/hw5_perf.dir/hw5_perf.cpp.o
hw5_perf: CMakeFiles/hw5_perf.dir/util.cpp.o
hw5_perf: CMakeFiles/hw5_perf.dir/build.make
hw5_perf: CMakeFiles/hw5_perf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/csuser/CPSC223/hw5-colleenlemak11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable hw5_perf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw5_perf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw5_perf.dir/build: hw5_perf

.PHONY : CMakeFiles/hw5_perf.dir/build

CMakeFiles/hw5_perf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw5_perf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw5_perf.dir/clean

CMakeFiles/hw5_perf.dir/depend:
	cd /home/csuser/CPSC223/hw5-colleenlemak11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/csuser/CPSC223/hw5-colleenlemak11 /home/csuser/CPSC223/hw5-colleenlemak11 /home/csuser/CPSC223/hw5-colleenlemak11 /home/csuser/CPSC223/hw5-colleenlemak11 /home/csuser/CPSC223/hw5-colleenlemak11/CMakeFiles/hw5_perf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw5_perf.dir/depend

