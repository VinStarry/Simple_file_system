# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.13.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.13.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yongxinxu/Desktop/Projects/vfs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yongxinxu/Desktop/Projects/vfs

# Include any dependencies generated for this target.
include CMakeFiles/vfs.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vfs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vfs.dir/flags.make

CMakeFiles/vfs.dir/vfs.c.o: CMakeFiles/vfs.dir/flags.make
CMakeFiles/vfs.dir/vfs.c.o: vfs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yongxinxu/Desktop/Projects/vfs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/vfs.dir/vfs.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/vfs.dir/vfs.c.o   -c /Users/yongxinxu/Desktop/Projects/vfs/vfs.c

CMakeFiles/vfs.dir/vfs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vfs.dir/vfs.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yongxinxu/Desktop/Projects/vfs/vfs.c > CMakeFiles/vfs.dir/vfs.c.i

CMakeFiles/vfs.dir/vfs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vfs.dir/vfs.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yongxinxu/Desktop/Projects/vfs/vfs.c -o CMakeFiles/vfs.dir/vfs.c.s

CMakeFiles/vfs.dir/src/dentry.c.o: CMakeFiles/vfs.dir/flags.make
CMakeFiles/vfs.dir/src/dentry.c.o: src/dentry.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yongxinxu/Desktop/Projects/vfs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/vfs.dir/src/dentry.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/vfs.dir/src/dentry.c.o   -c /Users/yongxinxu/Desktop/Projects/vfs/src/dentry.c

CMakeFiles/vfs.dir/src/dentry.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vfs.dir/src/dentry.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yongxinxu/Desktop/Projects/vfs/src/dentry.c > CMakeFiles/vfs.dir/src/dentry.c.i

CMakeFiles/vfs.dir/src/dentry.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vfs.dir/src/dentry.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yongxinxu/Desktop/Projects/vfs/src/dentry.c -o CMakeFiles/vfs.dir/src/dentry.c.s

CMakeFiles/vfs.dir/src/inode.c.o: CMakeFiles/vfs.dir/flags.make
CMakeFiles/vfs.dir/src/inode.c.o: src/inode.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yongxinxu/Desktop/Projects/vfs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/vfs.dir/src/inode.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/vfs.dir/src/inode.c.o   -c /Users/yongxinxu/Desktop/Projects/vfs/src/inode.c

CMakeFiles/vfs.dir/src/inode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vfs.dir/src/inode.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yongxinxu/Desktop/Projects/vfs/src/inode.c > CMakeFiles/vfs.dir/src/inode.c.i

CMakeFiles/vfs.dir/src/inode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vfs.dir/src/inode.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yongxinxu/Desktop/Projects/vfs/src/inode.c -o CMakeFiles/vfs.dir/src/inode.c.s

CMakeFiles/vfs.dir/src/super_block.c.o: CMakeFiles/vfs.dir/flags.make
CMakeFiles/vfs.dir/src/super_block.c.o: src/super_block.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yongxinxu/Desktop/Projects/vfs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/vfs.dir/src/super_block.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/vfs.dir/src/super_block.c.o   -c /Users/yongxinxu/Desktop/Projects/vfs/src/super_block.c

CMakeFiles/vfs.dir/src/super_block.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vfs.dir/src/super_block.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yongxinxu/Desktop/Projects/vfs/src/super_block.c > CMakeFiles/vfs.dir/src/super_block.c.i

CMakeFiles/vfs.dir/src/super_block.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vfs.dir/src/super_block.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yongxinxu/Desktop/Projects/vfs/src/super_block.c -o CMakeFiles/vfs.dir/src/super_block.c.s

CMakeFiles/vfs.dir/src/user.c.o: CMakeFiles/vfs.dir/flags.make
CMakeFiles/vfs.dir/src/user.c.o: src/user.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yongxinxu/Desktop/Projects/vfs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/vfs.dir/src/user.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/vfs.dir/src/user.c.o   -c /Users/yongxinxu/Desktop/Projects/vfs/src/user.c

CMakeFiles/vfs.dir/src/user.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vfs.dir/src/user.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yongxinxu/Desktop/Projects/vfs/src/user.c > CMakeFiles/vfs.dir/src/user.c.i

CMakeFiles/vfs.dir/src/user.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vfs.dir/src/user.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yongxinxu/Desktop/Projects/vfs/src/user.c -o CMakeFiles/vfs.dir/src/user.c.s

# Object files for target vfs
vfs_OBJECTS = \
"CMakeFiles/vfs.dir/vfs.c.o" \
"CMakeFiles/vfs.dir/src/dentry.c.o" \
"CMakeFiles/vfs.dir/src/inode.c.o" \
"CMakeFiles/vfs.dir/src/super_block.c.o" \
"CMakeFiles/vfs.dir/src/user.c.o"

# External object files for target vfs
vfs_EXTERNAL_OBJECTS =

vfs: CMakeFiles/vfs.dir/vfs.c.o
vfs: CMakeFiles/vfs.dir/src/dentry.c.o
vfs: CMakeFiles/vfs.dir/src/inode.c.o
vfs: CMakeFiles/vfs.dir/src/super_block.c.o
vfs: CMakeFiles/vfs.dir/src/user.c.o
vfs: CMakeFiles/vfs.dir/build.make
vfs: CMakeFiles/vfs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/yongxinxu/Desktop/Projects/vfs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable vfs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vfs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vfs.dir/build: vfs

.PHONY : CMakeFiles/vfs.dir/build

CMakeFiles/vfs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vfs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vfs.dir/clean

CMakeFiles/vfs.dir/depend:
	cd /Users/yongxinxu/Desktop/Projects/vfs && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/yongxinxu/Desktop/Projects/vfs /Users/yongxinxu/Desktop/Projects/vfs /Users/yongxinxu/Desktop/Projects/vfs /Users/yongxinxu/Desktop/Projects/vfs /Users/yongxinxu/Desktop/Projects/vfs/CMakeFiles/vfs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vfs.dir/depend

