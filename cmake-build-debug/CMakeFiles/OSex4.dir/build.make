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
CMAKE_COMMAND = /snap/clion/112/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/112/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shirgold/CLionProjects/OSex4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shirgold/CLionProjects/OSex4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OSex4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OSex4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OSex4.dir/flags.make

CMakeFiles/OSex4.dir/main.c.o: CMakeFiles/OSex4.dir/flags.make
CMakeFiles/OSex4.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shirgold/CLionProjects/OSex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OSex4.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OSex4.dir/main.c.o   -c /home/shirgold/CLionProjects/OSex4/main.c

CMakeFiles/OSex4.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OSex4.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/shirgold/CLionProjects/OSex4/main.c > CMakeFiles/OSex4.dir/main.c.i

CMakeFiles/OSex4.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OSex4.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/shirgold/CLionProjects/OSex4/main.c -o CMakeFiles/OSex4.dir/main.c.s

CMakeFiles/OSex4.dir/threadPool.c.o: CMakeFiles/OSex4.dir/flags.make
CMakeFiles/OSex4.dir/threadPool.c.o: ../threadPool.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shirgold/CLionProjects/OSex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OSex4.dir/threadPool.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OSex4.dir/threadPool.c.o   -c /home/shirgold/CLionProjects/OSex4/threadPool.c

CMakeFiles/OSex4.dir/threadPool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OSex4.dir/threadPool.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/shirgold/CLionProjects/OSex4/threadPool.c > CMakeFiles/OSex4.dir/threadPool.c.i

CMakeFiles/OSex4.dir/threadPool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OSex4.dir/threadPool.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/shirgold/CLionProjects/OSex4/threadPool.c -o CMakeFiles/OSex4.dir/threadPool.c.s

CMakeFiles/OSex4.dir/osqueue.c.o: CMakeFiles/OSex4.dir/flags.make
CMakeFiles/OSex4.dir/osqueue.c.o: ../osqueue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shirgold/CLionProjects/OSex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/OSex4.dir/osqueue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OSex4.dir/osqueue.c.o   -c /home/shirgold/CLionProjects/OSex4/osqueue.c

CMakeFiles/OSex4.dir/osqueue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OSex4.dir/osqueue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/shirgold/CLionProjects/OSex4/osqueue.c > CMakeFiles/OSex4.dir/osqueue.c.i

CMakeFiles/OSex4.dir/osqueue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OSex4.dir/osqueue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/shirgold/CLionProjects/OSex4/osqueue.c -o CMakeFiles/OSex4.dir/osqueue.c.s

# Object files for target OSex4
OSex4_OBJECTS = \
"CMakeFiles/OSex4.dir/main.c.o" \
"CMakeFiles/OSex4.dir/threadPool.c.o" \
"CMakeFiles/OSex4.dir/osqueue.c.o"

# External object files for target OSex4
OSex4_EXTERNAL_OBJECTS =

OSex4: CMakeFiles/OSex4.dir/main.c.o
OSex4: CMakeFiles/OSex4.dir/threadPool.c.o
OSex4: CMakeFiles/OSex4.dir/osqueue.c.o
OSex4: CMakeFiles/OSex4.dir/build.make
OSex4: CMakeFiles/OSex4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shirgold/CLionProjects/OSex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable OSex4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OSex4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OSex4.dir/build: OSex4

.PHONY : CMakeFiles/OSex4.dir/build

CMakeFiles/OSex4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OSex4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OSex4.dir/clean

CMakeFiles/OSex4.dir/depend:
	cd /home/shirgold/CLionProjects/OSex4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shirgold/CLionProjects/OSex4 /home/shirgold/CLionProjects/OSex4 /home/shirgold/CLionProjects/OSex4/cmake-build-debug /home/shirgold/CLionProjects/OSex4/cmake-build-debug /home/shirgold/CLionProjects/OSex4/cmake-build-debug/CMakeFiles/OSex4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OSex4.dir/depend

