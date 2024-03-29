# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /Users/nelson/Downloads/usr/local/Cellar/cmake/3.14.5/bin/cmake

# The command to remove a file.
RM = /Users/nelson/Downloads/usr/local/Cellar/cmake/3.14.5/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nelson/Documents/cannonball_example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nelson/Documents/cannonball_example

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Users/nelson/Downloads/usr/local/Cellar/cmake/3.14.5/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/Users/nelson/Downloads/usr/local/Cellar/cmake/3.14.5/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/nelson/Documents/cannonball_example/CMakeFiles /Users/nelson/Documents/cannonball_example/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/nelson/Documents/cannonball_example/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named std

# Build rule for target.
std: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 std
.PHONY : std

# fast build rule for target.
std/fast:
	$(MAKE) -f CMakeFiles/std.dir/build.make CMakeFiles/std.dir/build
.PHONY : std/fast

#=============================================================================
# Target rules for targets named cnl

# Build rule for target.
cnl: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cnl
.PHONY : cnl

# fast build rule for target.
cnl/fast:
	$(MAKE) -f CMakeFiles/cnl.dir/build.make CMakeFiles/cnl.dir/build
.PHONY : cnl/fast

src/cnl_types.o: src/cnl_types.cpp.o

.PHONY : src/cnl_types.o

# target to build an object file
src/cnl_types.cpp.o:
	$(MAKE) -f CMakeFiles/cnl.dir/build.make CMakeFiles/cnl.dir/src/cnl_types.cpp.o
.PHONY : src/cnl_types.cpp.o

src/cnl_types.i: src/cnl_types.cpp.i

.PHONY : src/cnl_types.i

# target to preprocess a source file
src/cnl_types.cpp.i:
	$(MAKE) -f CMakeFiles/cnl.dir/build.make CMakeFiles/cnl.dir/src/cnl_types.cpp.i
.PHONY : src/cnl_types.cpp.i

src/cnl_types.s: src/cnl_types.cpp.s

.PHONY : src/cnl_types.s

# target to generate assembly for a file
src/cnl_types.cpp.s:
	$(MAKE) -f CMakeFiles/cnl.dir/build.make CMakeFiles/cnl.dir/src/cnl_types.cpp.s
.PHONY : src/cnl_types.cpp.s

src/std_types.o: src/std_types.cpp.o

.PHONY : src/std_types.o

# target to build an object file
src/std_types.cpp.o:
	$(MAKE) -f CMakeFiles/std.dir/build.make CMakeFiles/std.dir/src/std_types.cpp.o
.PHONY : src/std_types.cpp.o

src/std_types.i: src/std_types.cpp.i

.PHONY : src/std_types.i

# target to preprocess a source file
src/std_types.cpp.i:
	$(MAKE) -f CMakeFiles/std.dir/build.make CMakeFiles/std.dir/src/std_types.cpp.i
.PHONY : src/std_types.cpp.i

src/std_types.s: src/std_types.cpp.s

.PHONY : src/std_types.s

# target to generate assembly for a file
src/std_types.cpp.s:
	$(MAKE) -f CMakeFiles/std.dir/build.make CMakeFiles/std.dir/src/std_types.cpp.s
.PHONY : src/std_types.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... std"
	@echo "... cnl"
	@echo "... src/cnl_types.o"
	@echo "... src/cnl_types.i"
	@echo "... src/cnl_types.s"
	@echo "... src/std_types.o"
	@echo "... src/std_types.i"
	@echo "... src/std_types.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

