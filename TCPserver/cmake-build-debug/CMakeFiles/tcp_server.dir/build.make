# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/169/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/169/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/york/CLionProjects/socketTest/TCPserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/york/CLionProjects/socketTest/TCPserver/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tcp_server.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/tcp_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tcp_server.dir/flags.make

CMakeFiles/tcp_server.dir/tcp_server.c.o: CMakeFiles/tcp_server.dir/flags.make
CMakeFiles/tcp_server.dir/tcp_server.c.o: ../tcp_server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/york/CLionProjects/socketTest/TCPserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tcp_server.dir/tcp_server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tcp_server.dir/tcp_server.c.o -c /home/york/CLionProjects/socketTest/TCPserver/tcp_server.c

CMakeFiles/tcp_server.dir/tcp_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tcp_server.dir/tcp_server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/york/CLionProjects/socketTest/TCPserver/tcp_server.c > CMakeFiles/tcp_server.dir/tcp_server.c.i

CMakeFiles/tcp_server.dir/tcp_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tcp_server.dir/tcp_server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/york/CLionProjects/socketTest/TCPserver/tcp_server.c -o CMakeFiles/tcp_server.dir/tcp_server.c.s

CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.o: CMakeFiles/tcp_server.dir/flags.make
CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.o: ../threadutils/tinycthread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/york/CLionProjects/socketTest/TCPserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.o -c /home/york/CLionProjects/socketTest/TCPserver/threadutils/tinycthread.c

CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/york/CLionProjects/socketTest/TCPserver/threadutils/tinycthread.c > CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.i

CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/york/CLionProjects/socketTest/TCPserver/threadutils/tinycthread.c -o CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.s

# Object files for target tcp_server
tcp_server_OBJECTS = \
"CMakeFiles/tcp_server.dir/tcp_server.c.o" \
"CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.o"

# External object files for target tcp_server
tcp_server_EXTERNAL_OBJECTS =

tcp_server: CMakeFiles/tcp_server.dir/tcp_server.c.o
tcp_server: CMakeFiles/tcp_server.dir/threadutils/tinycthread.c.o
tcp_server: CMakeFiles/tcp_server.dir/build.make
tcp_server: CMakeFiles/tcp_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/york/CLionProjects/socketTest/TCPserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable tcp_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcp_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tcp_server.dir/build: tcp_server
.PHONY : CMakeFiles/tcp_server.dir/build

CMakeFiles/tcp_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tcp_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tcp_server.dir/clean

CMakeFiles/tcp_server.dir/depend:
	cd /home/york/CLionProjects/socketTest/TCPserver/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/york/CLionProjects/socketTest/TCPserver /home/york/CLionProjects/socketTest/TCPserver /home/york/CLionProjects/socketTest/TCPserver/cmake-build-debug /home/york/CLionProjects/socketTest/TCPserver/cmake-build-debug /home/york/CLionProjects/socketTest/TCPserver/cmake-build-debug/CMakeFiles/tcp_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tcp_server.dir/depend

