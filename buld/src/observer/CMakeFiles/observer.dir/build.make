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
CMAKE_SOURCE_DIR = /home/hyq/MiniOB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hyq/MiniOB/buld

# Include any dependencies generated for this target.
include src/observer/CMakeFiles/observer.dir/depend.make

# Include the progress variables for this target.
include src/observer/CMakeFiles/observer.dir/progress.make

# Include the compile flags for this target's objects.
include src/observer/CMakeFiles/observer.dir/flags.make

src/observer/CMakeFiles/observer.dir/main.cpp.o: src/observer/CMakeFiles/observer.dir/flags.make
src/observer/CMakeFiles/observer.dir/main.cpp.o: ../src/observer/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hyq/MiniOB/buld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/observer/CMakeFiles/observer.dir/main.cpp.o"
	cd /home/hyq/MiniOB/buld/src/observer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/observer.dir/main.cpp.o -c /home/hyq/MiniOB/src/observer/main.cpp

src/observer/CMakeFiles/observer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/observer.dir/main.cpp.i"
	cd /home/hyq/MiniOB/buld/src/observer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hyq/MiniOB/src/observer/main.cpp > CMakeFiles/observer.dir/main.cpp.i

src/observer/CMakeFiles/observer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/observer.dir/main.cpp.s"
	cd /home/hyq/MiniOB/buld/src/observer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hyq/MiniOB/src/observer/main.cpp -o CMakeFiles/observer.dir/main.cpp.s

# Object files for target observer
observer_OBJECTS = \
"CMakeFiles/observer.dir/main.cpp.o"

# External object files for target observer
observer_EXTERNAL_OBJECTS =

bin/observer: src/observer/CMakeFiles/observer.dir/main.cpp.o
bin/observer: src/observer/CMakeFiles/observer.dir/build.make
bin/observer: lib/libobserver.a
bin/observer: lib/libcommon.a
bin/observer: /usr/local/lib/libevent_pthreads.a
bin/observer: /usr/local/lib/libevent_core.a
bin/observer: src/observer/CMakeFiles/observer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hyq/MiniOB/buld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/observer"
	cd /home/hyq/MiniOB/buld/src/observer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/observer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/observer/CMakeFiles/observer.dir/build: bin/observer

.PHONY : src/observer/CMakeFiles/observer.dir/build

src/observer/CMakeFiles/observer.dir/clean:
	cd /home/hyq/MiniOB/buld/src/observer && $(CMAKE_COMMAND) -P CMakeFiles/observer.dir/cmake_clean.cmake
.PHONY : src/observer/CMakeFiles/observer.dir/clean

src/observer/CMakeFiles/observer.dir/depend:
	cd /home/hyq/MiniOB/buld && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hyq/MiniOB /home/hyq/MiniOB/src/observer /home/hyq/MiniOB/buld /home/hyq/MiniOB/buld/src/observer /home/hyq/MiniOB/buld/src/observer/CMakeFiles/observer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/observer/CMakeFiles/observer.dir/depend

