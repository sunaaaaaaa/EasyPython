# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/lighthouse/cppSpace/EasyPython

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lighthouse/cppSpace/EasyPython/build

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/src/main.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/main.cc.o: ../src/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lighthouse/cppSpace/EasyPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.dir/src/main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/src/main.cc.o -c /home/lighthouse/cppSpace/EasyPython/src/main.cc

CMakeFiles/test.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lighthouse/cppSpace/EasyPython/src/main.cc > CMakeFiles/test.dir/src/main.cc.i

CMakeFiles/test.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lighthouse/cppSpace/EasyPython/src/main.cc -o CMakeFiles/test.dir/src/main.cc.s

CMakeFiles/test.dir/src/main.cc.o.requires:

.PHONY : CMakeFiles/test.dir/src/main.cc.o.requires

CMakeFiles/test.dir/src/main.cc.o.provides: CMakeFiles/test.dir/src/main.cc.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/main.cc.o.provides.build
.PHONY : CMakeFiles/test.dir/src/main.cc.o.provides

CMakeFiles/test.dir/src/main.cc.o.provides.build: CMakeFiles/test.dir/src/main.cc.o


CMakeFiles/test.dir/src/object/String.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/object/String.cc.o: ../src/object/String.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lighthouse/cppSpace/EasyPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test.dir/src/object/String.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/src/object/String.cc.o -c /home/lighthouse/cppSpace/EasyPython/src/object/String.cc

CMakeFiles/test.dir/src/object/String.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/object/String.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lighthouse/cppSpace/EasyPython/src/object/String.cc > CMakeFiles/test.dir/src/object/String.cc.i

CMakeFiles/test.dir/src/object/String.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/object/String.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lighthouse/cppSpace/EasyPython/src/object/String.cc -o CMakeFiles/test.dir/src/object/String.cc.s

CMakeFiles/test.dir/src/object/String.cc.o.requires:

.PHONY : CMakeFiles/test.dir/src/object/String.cc.o.requires

CMakeFiles/test.dir/src/object/String.cc.o.provides: CMakeFiles/test.dir/src/object/String.cc.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/object/String.cc.o.provides.build
.PHONY : CMakeFiles/test.dir/src/object/String.cc.o.provides

CMakeFiles/test.dir/src/object/String.cc.o.provides.build: CMakeFiles/test.dir/src/object/String.cc.o


CMakeFiles/test.dir/src/object/integer.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/object/integer.cc.o: ../src/object/integer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lighthouse/cppSpace/EasyPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test.dir/src/object/integer.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/src/object/integer.cc.o -c /home/lighthouse/cppSpace/EasyPython/src/object/integer.cc

CMakeFiles/test.dir/src/object/integer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/object/integer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lighthouse/cppSpace/EasyPython/src/object/integer.cc > CMakeFiles/test.dir/src/object/integer.cc.i

CMakeFiles/test.dir/src/object/integer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/object/integer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lighthouse/cppSpace/EasyPython/src/object/integer.cc -o CMakeFiles/test.dir/src/object/integer.cc.s

CMakeFiles/test.dir/src/object/integer.cc.o.requires:

.PHONY : CMakeFiles/test.dir/src/object/integer.cc.o.requires

CMakeFiles/test.dir/src/object/integer.cc.o.provides: CMakeFiles/test.dir/src/object/integer.cc.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/object/integer.cc.o.provides.build
.PHONY : CMakeFiles/test.dir/src/object/integer.cc.o.provides

CMakeFiles/test.dir/src/object/integer.cc.o.provides.build: CMakeFiles/test.dir/src/object/integer.cc.o


CMakeFiles/test.dir/src/code/code_object.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/code/code_object.cc.o: ../src/code/code_object.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lighthouse/cppSpace/EasyPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/test.dir/src/code/code_object.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/src/code/code_object.cc.o -c /home/lighthouse/cppSpace/EasyPython/src/code/code_object.cc

CMakeFiles/test.dir/src/code/code_object.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/code/code_object.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lighthouse/cppSpace/EasyPython/src/code/code_object.cc > CMakeFiles/test.dir/src/code/code_object.cc.i

CMakeFiles/test.dir/src/code/code_object.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/code/code_object.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lighthouse/cppSpace/EasyPython/src/code/code_object.cc -o CMakeFiles/test.dir/src/code/code_object.cc.s

CMakeFiles/test.dir/src/code/code_object.cc.o.requires:

.PHONY : CMakeFiles/test.dir/src/code/code_object.cc.o.requires

CMakeFiles/test.dir/src/code/code_object.cc.o.provides: CMakeFiles/test.dir/src/code/code_object.cc.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/code/code_object.cc.o.provides.build
.PHONY : CMakeFiles/test.dir/src/code/code_object.cc.o.provides

CMakeFiles/test.dir/src/code/code_object.cc.o.provides.build: CMakeFiles/test.dir/src/code/code_object.cc.o


CMakeFiles/test.dir/src/code/binary_parser.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/code/binary_parser.cc.o: ../src/code/binary_parser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lighthouse/cppSpace/EasyPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/test.dir/src/code/binary_parser.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/src/code/binary_parser.cc.o -c /home/lighthouse/cppSpace/EasyPython/src/code/binary_parser.cc

CMakeFiles/test.dir/src/code/binary_parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/code/binary_parser.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lighthouse/cppSpace/EasyPython/src/code/binary_parser.cc > CMakeFiles/test.dir/src/code/binary_parser.cc.i

CMakeFiles/test.dir/src/code/binary_parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/code/binary_parser.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lighthouse/cppSpace/EasyPython/src/code/binary_parser.cc -o CMakeFiles/test.dir/src/code/binary_parser.cc.s

CMakeFiles/test.dir/src/code/binary_parser.cc.o.requires:

.PHONY : CMakeFiles/test.dir/src/code/binary_parser.cc.o.requires

CMakeFiles/test.dir/src/code/binary_parser.cc.o.provides: CMakeFiles/test.dir/src/code/binary_parser.cc.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/code/binary_parser.cc.o.provides.build
.PHONY : CMakeFiles/test.dir/src/code/binary_parser.cc.o.provides

CMakeFiles/test.dir/src/code/binary_parser.cc.o.provides.build: CMakeFiles/test.dir/src/code/binary_parser.cc.o


# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/src/main.cc.o" \
"CMakeFiles/test.dir/src/object/String.cc.o" \
"CMakeFiles/test.dir/src/object/integer.cc.o" \
"CMakeFiles/test.dir/src/code/code_object.cc.o" \
"CMakeFiles/test.dir/src/code/binary_parser.cc.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

test: CMakeFiles/test.dir/src/main.cc.o
test: CMakeFiles/test.dir/src/object/String.cc.o
test: CMakeFiles/test.dir/src/object/integer.cc.o
test: CMakeFiles/test.dir/src/code/code_object.cc.o
test: CMakeFiles/test.dir/src/code/binary_parser.cc.o
test: CMakeFiles/test.dir/build.make
test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lighthouse/cppSpace/EasyPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test

.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/requires: CMakeFiles/test.dir/src/main.cc.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/src/object/String.cc.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/src/object/integer.cc.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/src/code/code_object.cc.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/src/code/binary_parser.cc.o.requires

.PHONY : CMakeFiles/test.dir/requires

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /home/lighthouse/cppSpace/EasyPython/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lighthouse/cppSpace/EasyPython /home/lighthouse/cppSpace/EasyPython /home/lighthouse/cppSpace/EasyPython/build /home/lighthouse/cppSpace/EasyPython/build /home/lighthouse/cppSpace/EasyPython/build/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

