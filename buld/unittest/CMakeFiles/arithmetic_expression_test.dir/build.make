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
include unittest/CMakeFiles/arithmetic_expression_test.dir/depend.make

# Include the progress variables for this target.
include unittest/CMakeFiles/arithmetic_expression_test.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/CMakeFiles/arithmetic_expression_test.dir/flags.make

unittest/CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.o: unittest/CMakeFiles/arithmetic_expression_test.dir/flags.make
unittest/CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.o: ../unittest/arithmetic_expression_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hyq/MiniOB/buld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.o"
	cd /home/hyq/MiniOB/buld/unittest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.o -c /home/hyq/MiniOB/unittest/arithmetic_expression_test.cpp

unittest/CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.i"
	cd /home/hyq/MiniOB/buld/unittest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hyq/MiniOB/unittest/arithmetic_expression_test.cpp > CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.i

unittest/CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.s"
	cd /home/hyq/MiniOB/buld/unittest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hyq/MiniOB/unittest/arithmetic_expression_test.cpp -o CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.s

# Object files for target arithmetic_expression_test
arithmetic_expression_test_OBJECTS = \
"CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.o"

# External object files for target arithmetic_expression_test
arithmetic_expression_test_EXTERNAL_OBJECTS =

bin/arithmetic_expression_test: unittest/CMakeFiles/arithmetic_expression_test.dir/arithmetic_expression_test.cpp.o
bin/arithmetic_expression_test: unittest/CMakeFiles/arithmetic_expression_test.dir/build.make
bin/arithmetic_expression_test: lib/libcommon.a
bin/arithmetic_expression_test: lib/libobserver.a
bin/arithmetic_expression_test: lib/libcommon.a
bin/arithmetic_expression_test: /usr/local/lib/libevent_pthreads.a
bin/arithmetic_expression_test: /usr/local/lib/libevent_core.a
bin/arithmetic_expression_test: unittest/CMakeFiles/arithmetic_expression_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hyq/MiniOB/buld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/arithmetic_expression_test"
	cd /home/hyq/MiniOB/buld/unittest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arithmetic_expression_test.dir/link.txt --verbose=$(VERBOSE)
	cd /home/hyq/MiniOB/buld/unittest && /usr/bin/cmake -D TEST_TARGET=arithmetic_expression_test -D TEST_EXECUTABLE=/home/hyq/MiniOB/buld/bin/arithmetic_expression_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/hyq/MiniOB/buld/unittest -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=arithmetic_expression_test_TESTS -D CTEST_FILE=/home/hyq/MiniOB/buld/unittest/arithmetic_expression_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -P /usr/share/cmake-3.16/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
unittest/CMakeFiles/arithmetic_expression_test.dir/build: bin/arithmetic_expression_test

.PHONY : unittest/CMakeFiles/arithmetic_expression_test.dir/build

unittest/CMakeFiles/arithmetic_expression_test.dir/clean:
	cd /home/hyq/MiniOB/buld/unittest && $(CMAKE_COMMAND) -P CMakeFiles/arithmetic_expression_test.dir/cmake_clean.cmake
.PHONY : unittest/CMakeFiles/arithmetic_expression_test.dir/clean

unittest/CMakeFiles/arithmetic_expression_test.dir/depend:
	cd /home/hyq/MiniOB/buld && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hyq/MiniOB /home/hyq/MiniOB/unittest /home/hyq/MiniOB/buld /home/hyq/MiniOB/buld/unittest /home/hyq/MiniOB/buld/unittest/CMakeFiles/arithmetic_expression_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/CMakeFiles/arithmetic_expression_test.dir/depend

