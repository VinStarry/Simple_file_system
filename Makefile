# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = "/Users/yongxinxu/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/183.5153.40/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/yongxinxu/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/183.5153.40/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yongxinxu/Desktop/Projects/vfs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yongxinxu/Desktop/Projects/vfs

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"/Users/yongxinxu/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/183.5153.40/CLion.app/Contents/bin/cmake/mac/bin/cmake" -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	"/Users/yongxinxu/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/183.5153.40/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/yongxinxu/Desktop/Projects/vfs/CMakeFiles /Users/yongxinxu/Desktop/Projects/vfs/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/yongxinxu/Desktop/Projects/vfs/CMakeFiles 0
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
# Target rules for targets named vfs

# Build rule for target.
vfs: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 vfs
.PHONY : vfs

# fast build rule for target.
vfs/fast:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/build
.PHONY : vfs/fast

src/dentry.o: src/dentry.c.o

.PHONY : src/dentry.o

# target to build an object file
src/dentry.c.o:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/dentry.c.o
.PHONY : src/dentry.c.o

src/dentry.i: src/dentry.c.i

.PHONY : src/dentry.i

# target to preprocess a source file
src/dentry.c.i:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/dentry.c.i
.PHONY : src/dentry.c.i

src/dentry.s: src/dentry.c.s

.PHONY : src/dentry.s

# target to generate assembly for a file
src/dentry.c.s:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/dentry.c.s
.PHONY : src/dentry.c.s

src/inode.o: src/inode.c.o

.PHONY : src/inode.o

# target to build an object file
src/inode.c.o:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/inode.c.o
.PHONY : src/inode.c.o

src/inode.i: src/inode.c.i

.PHONY : src/inode.i

# target to preprocess a source file
src/inode.c.i:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/inode.c.i
.PHONY : src/inode.c.i

src/inode.s: src/inode.c.s

.PHONY : src/inode.s

# target to generate assembly for a file
src/inode.c.s:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/inode.c.s
.PHONY : src/inode.c.s

src/instruction_handle.o: src/instruction_handle.c.o

.PHONY : src/instruction_handle.o

# target to build an object file
src/instruction_handle.c.o:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/instruction_handle.c.o
.PHONY : src/instruction_handle.c.o

src/instruction_handle.i: src/instruction_handle.c.i

.PHONY : src/instruction_handle.i

# target to preprocess a source file
src/instruction_handle.c.i:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/instruction_handle.c.i
.PHONY : src/instruction_handle.c.i

src/instruction_handle.s: src/instruction_handle.c.s

.PHONY : src/instruction_handle.s

# target to generate assembly for a file
src/instruction_handle.c.s:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/instruction_handle.c.s
.PHONY : src/instruction_handle.c.s

src/super_block.o: src/super_block.c.o

.PHONY : src/super_block.o

# target to build an object file
src/super_block.c.o:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/super_block.c.o
.PHONY : src/super_block.c.o

src/super_block.i: src/super_block.c.i

.PHONY : src/super_block.i

# target to preprocess a source file
src/super_block.c.i:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/super_block.c.i
.PHONY : src/super_block.c.i

src/super_block.s: src/super_block.c.s

.PHONY : src/super_block.s

# target to generate assembly for a file
src/super_block.c.s:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/super_block.c.s
.PHONY : src/super_block.c.s

src/trival_helper.o: src/trival_helper.c.o

.PHONY : src/trival_helper.o

# target to build an object file
src/trival_helper.c.o:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/trival_helper.c.o
.PHONY : src/trival_helper.c.o

src/trival_helper.i: src/trival_helper.c.i

.PHONY : src/trival_helper.i

# target to preprocess a source file
src/trival_helper.c.i:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/trival_helper.c.i
.PHONY : src/trival_helper.c.i

src/trival_helper.s: src/trival_helper.c.s

.PHONY : src/trival_helper.s

# target to generate assembly for a file
src/trival_helper.c.s:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/trival_helper.c.s
.PHONY : src/trival_helper.c.s

src/user.o: src/user.c.o

.PHONY : src/user.o

# target to build an object file
src/user.c.o:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/user.c.o
.PHONY : src/user.c.o

src/user.i: src/user.c.i

.PHONY : src/user.i

# target to preprocess a source file
src/user.c.i:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/user.c.i
.PHONY : src/user.c.i

src/user.s: src/user.c.s

.PHONY : src/user.s

# target to generate assembly for a file
src/user.c.s:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/src/user.c.s
.PHONY : src/user.c.s

vfs.o: vfs.c.o

.PHONY : vfs.o

# target to build an object file
vfs.c.o:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/vfs.c.o
.PHONY : vfs.c.o

vfs.i: vfs.c.i

.PHONY : vfs.i

# target to preprocess a source file
vfs.c.i:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/vfs.c.i
.PHONY : vfs.c.i

vfs.s: vfs.c.s

.PHONY : vfs.s

# target to generate assembly for a file
vfs.c.s:
	$(MAKE) -f CMakeFiles/vfs.dir/build.make CMakeFiles/vfs.dir/vfs.c.s
.PHONY : vfs.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... vfs"
	@echo "... src/dentry.o"
	@echo "... src/dentry.i"
	@echo "... src/dentry.s"
	@echo "... src/inode.o"
	@echo "... src/inode.i"
	@echo "... src/inode.s"
	@echo "... src/instruction_handle.o"
	@echo "... src/instruction_handle.i"
	@echo "... src/instruction_handle.s"
	@echo "... src/super_block.o"
	@echo "... src/super_block.i"
	@echo "... src/super_block.s"
	@echo "... src/trival_helper.o"
	@echo "... src/trival_helper.i"
	@echo "... src/trival_helper.s"
	@echo "... src/user.o"
	@echo "... src/user.i"
	@echo "... src/user.s"
	@echo "... vfs.o"
	@echo "... vfs.i"
	@echo "... vfs.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

