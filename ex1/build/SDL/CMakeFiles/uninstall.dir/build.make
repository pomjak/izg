# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex1/build

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include SDL/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include SDL/CMakeFiles/uninstall.dir/progress.make

SDL/CMakeFiles/uninstall:
	cd /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex1/build/SDL && /usr/bin/cmake -P /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex1/build/SDL/cmake_uninstall.cmake

uninstall: SDL/CMakeFiles/uninstall
uninstall: SDL/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
SDL/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : SDL/CMakeFiles/uninstall.dir/build

SDL/CMakeFiles/uninstall.dir/clean:
	cd /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex1/build/SDL && $(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : SDL/CMakeFiles/uninstall.dir/clean

SDL/CMakeFiles/uninstall.dir/depend:
	cd /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex1 /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex1/SDL /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex1/build /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex1/build/SDL /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex1/build/SDL/CMakeFiles/uninstall.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : SDL/CMakeFiles/uninstall.dir/depend
