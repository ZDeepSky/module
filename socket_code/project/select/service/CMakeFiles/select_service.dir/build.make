# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = /home/zgd/code/socket

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zgd/code/socket/project

# Include any dependencies generated for this target.
include select/service/CMakeFiles/select_service.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include select/service/CMakeFiles/select_service.dir/compiler_depend.make

# Include the progress variables for this target.
include select/service/CMakeFiles/select_service.dir/progress.make

# Include the compile flags for this target's objects.
include select/service/CMakeFiles/select_service.dir/flags.make

select/service/CMakeFiles/select_service.dir/codegen:
.PHONY : select/service/CMakeFiles/select_service.dir/codegen

select/service/CMakeFiles/select_service.dir/source/service.cpp.o: select/service/CMakeFiles/select_service.dir/flags.make
select/service/CMakeFiles/select_service.dir/source/service.cpp.o: /home/zgd/code/socket/select/service/source/service.cpp
select/service/CMakeFiles/select_service.dir/source/service.cpp.o: select/service/CMakeFiles/select_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/zgd/code/socket/project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object select/service/CMakeFiles/select_service.dir/source/service.cpp.o"
	cd /home/zgd/code/socket/project/select/service && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT select/service/CMakeFiles/select_service.dir/source/service.cpp.o -MF CMakeFiles/select_service.dir/source/service.cpp.o.d -o CMakeFiles/select_service.dir/source/service.cpp.o -c /home/zgd/code/socket/select/service/source/service.cpp

select/service/CMakeFiles/select_service.dir/source/service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/select_service.dir/source/service.cpp.i"
	cd /home/zgd/code/socket/project/select/service && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zgd/code/socket/select/service/source/service.cpp > CMakeFiles/select_service.dir/source/service.cpp.i

select/service/CMakeFiles/select_service.dir/source/service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/select_service.dir/source/service.cpp.s"
	cd /home/zgd/code/socket/project/select/service && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zgd/code/socket/select/service/source/service.cpp -o CMakeFiles/select_service.dir/source/service.cpp.s

# Object files for target select_service
select_service_OBJECTS = \
"CMakeFiles/select_service.dir/source/service.cpp.o"

# External object files for target select_service
select_service_EXTERNAL_OBJECTS =

/home/zgd/code/socket/bin/select_service: select/service/CMakeFiles/select_service.dir/source/service.cpp.o
/home/zgd/code/socket/bin/select_service: select/service/CMakeFiles/select_service.dir/build.make
/home/zgd/code/socket/bin/select_service: select/service/CMakeFiles/select_service.dir/compiler_depend.ts
/home/zgd/code/socket/bin/select_service: select/service/CMakeFiles/select_service.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/zgd/code/socket/project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/zgd/code/socket/bin/select_service"
	cd /home/zgd/code/socket/project/select/service && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/select_service.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
select/service/CMakeFiles/select_service.dir/build: /home/zgd/code/socket/bin/select_service
.PHONY : select/service/CMakeFiles/select_service.dir/build

select/service/CMakeFiles/select_service.dir/clean:
	cd /home/zgd/code/socket/project/select/service && $(CMAKE_COMMAND) -P CMakeFiles/select_service.dir/cmake_clean.cmake
.PHONY : select/service/CMakeFiles/select_service.dir/clean

select/service/CMakeFiles/select_service.dir/depend:
	cd /home/zgd/code/socket/project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zgd/code/socket /home/zgd/code/socket/select/service /home/zgd/code/socket/project /home/zgd/code/socket/project/select/service /home/zgd/code/socket/project/select/service/CMakeFiles/select_service.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : select/service/CMakeFiles/select_service.dir/depend

