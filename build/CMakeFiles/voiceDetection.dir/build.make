# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/artik/MFCC_CMAKE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/artik/MFCC_CMAKE/build

# Include any dependencies generated for this target.
include CMakeFiles/voiceDetection.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/voiceDetection.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/voiceDetection.dir/flags.make

CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o: CMakeFiles/voiceDetection.dir/flags.make
CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o: ../src/syll_fragmentation.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artik/MFCC_CMAKE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o   -c /home/artik/MFCC_CMAKE/src/syll_fragmentation.c

CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/artik/MFCC_CMAKE/src/syll_fragmentation.c > CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.i

CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/artik/MFCC_CMAKE/src/syll_fragmentation.c -o CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.s

CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o.requires:

.PHONY : CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o.requires

CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o.provides: CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o.requires
	$(MAKE) -f CMakeFiles/voiceDetection.dir/build.make CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o.provides.build
.PHONY : CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o.provides

CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o.provides.build: CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o


CMakeFiles/voiceDetection.dir/src/utils.c.o: CMakeFiles/voiceDetection.dir/flags.make
CMakeFiles/voiceDetection.dir/src/utils.c.o: ../src/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artik/MFCC_CMAKE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/voiceDetection.dir/src/utils.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/voiceDetection.dir/src/utils.c.o   -c /home/artik/MFCC_CMAKE/src/utils.c

CMakeFiles/voiceDetection.dir/src/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/voiceDetection.dir/src/utils.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/artik/MFCC_CMAKE/src/utils.c > CMakeFiles/voiceDetection.dir/src/utils.c.i

CMakeFiles/voiceDetection.dir/src/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/voiceDetection.dir/src/utils.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/artik/MFCC_CMAKE/src/utils.c -o CMakeFiles/voiceDetection.dir/src/utils.c.s

CMakeFiles/voiceDetection.dir/src/utils.c.o.requires:

.PHONY : CMakeFiles/voiceDetection.dir/src/utils.c.o.requires

CMakeFiles/voiceDetection.dir/src/utils.c.o.provides: CMakeFiles/voiceDetection.dir/src/utils.c.o.requires
	$(MAKE) -f CMakeFiles/voiceDetection.dir/build.make CMakeFiles/voiceDetection.dir/src/utils.c.o.provides.build
.PHONY : CMakeFiles/voiceDetection.dir/src/utils.c.o.provides

CMakeFiles/voiceDetection.dir/src/utils.c.o.provides.build: CMakeFiles/voiceDetection.dir/src/utils.c.o


CMakeFiles/voiceDetection.dir/src/gemm.c.o: CMakeFiles/voiceDetection.dir/flags.make
CMakeFiles/voiceDetection.dir/src/gemm.c.o: ../src/gemm.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artik/MFCC_CMAKE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/voiceDetection.dir/src/gemm.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/voiceDetection.dir/src/gemm.c.o   -c /home/artik/MFCC_CMAKE/src/gemm.c

CMakeFiles/voiceDetection.dir/src/gemm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/voiceDetection.dir/src/gemm.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/artik/MFCC_CMAKE/src/gemm.c > CMakeFiles/voiceDetection.dir/src/gemm.c.i

CMakeFiles/voiceDetection.dir/src/gemm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/voiceDetection.dir/src/gemm.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/artik/MFCC_CMAKE/src/gemm.c -o CMakeFiles/voiceDetection.dir/src/gemm.c.s

CMakeFiles/voiceDetection.dir/src/gemm.c.o.requires:

.PHONY : CMakeFiles/voiceDetection.dir/src/gemm.c.o.requires

CMakeFiles/voiceDetection.dir/src/gemm.c.o.provides: CMakeFiles/voiceDetection.dir/src/gemm.c.o.requires
	$(MAKE) -f CMakeFiles/voiceDetection.dir/build.make CMakeFiles/voiceDetection.dir/src/gemm.c.o.provides.build
.PHONY : CMakeFiles/voiceDetection.dir/src/gemm.c.o.provides

CMakeFiles/voiceDetection.dir/src/gemm.c.o.provides.build: CMakeFiles/voiceDetection.dir/src/gemm.c.o


CMakeFiles/voiceDetection.dir/src/record.c.o: CMakeFiles/voiceDetection.dir/flags.make
CMakeFiles/voiceDetection.dir/src/record.c.o: ../src/record.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artik/MFCC_CMAKE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/voiceDetection.dir/src/record.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/voiceDetection.dir/src/record.c.o   -c /home/artik/MFCC_CMAKE/src/record.c

CMakeFiles/voiceDetection.dir/src/record.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/voiceDetection.dir/src/record.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/artik/MFCC_CMAKE/src/record.c > CMakeFiles/voiceDetection.dir/src/record.c.i

CMakeFiles/voiceDetection.dir/src/record.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/voiceDetection.dir/src/record.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/artik/MFCC_CMAKE/src/record.c -o CMakeFiles/voiceDetection.dir/src/record.c.s

CMakeFiles/voiceDetection.dir/src/record.c.o.requires:

.PHONY : CMakeFiles/voiceDetection.dir/src/record.c.o.requires

CMakeFiles/voiceDetection.dir/src/record.c.o.provides: CMakeFiles/voiceDetection.dir/src/record.c.o.requires
	$(MAKE) -f CMakeFiles/voiceDetection.dir/build.make CMakeFiles/voiceDetection.dir/src/record.c.o.provides.build
.PHONY : CMakeFiles/voiceDetection.dir/src/record.c.o.provides

CMakeFiles/voiceDetection.dir/src/record.c.o.provides.build: CMakeFiles/voiceDetection.dir/src/record.c.o


CMakeFiles/voiceDetection.dir/src/mfcc.c.o: CMakeFiles/voiceDetection.dir/flags.make
CMakeFiles/voiceDetection.dir/src/mfcc.c.o: ../src/mfcc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artik/MFCC_CMAKE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/voiceDetection.dir/src/mfcc.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/voiceDetection.dir/src/mfcc.c.o   -c /home/artik/MFCC_CMAKE/src/mfcc.c

CMakeFiles/voiceDetection.dir/src/mfcc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/voiceDetection.dir/src/mfcc.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/artik/MFCC_CMAKE/src/mfcc.c > CMakeFiles/voiceDetection.dir/src/mfcc.c.i

CMakeFiles/voiceDetection.dir/src/mfcc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/voiceDetection.dir/src/mfcc.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/artik/MFCC_CMAKE/src/mfcc.c -o CMakeFiles/voiceDetection.dir/src/mfcc.c.s

CMakeFiles/voiceDetection.dir/src/mfcc.c.o.requires:

.PHONY : CMakeFiles/voiceDetection.dir/src/mfcc.c.o.requires

CMakeFiles/voiceDetection.dir/src/mfcc.c.o.provides: CMakeFiles/voiceDetection.dir/src/mfcc.c.o.requires
	$(MAKE) -f CMakeFiles/voiceDetection.dir/build.make CMakeFiles/voiceDetection.dir/src/mfcc.c.o.provides.build
.PHONY : CMakeFiles/voiceDetection.dir/src/mfcc.c.o.provides

CMakeFiles/voiceDetection.dir/src/mfcc.c.o.provides.build: CMakeFiles/voiceDetection.dir/src/mfcc.c.o


CMakeFiles/voiceDetection.dir/src/svm.c.o: CMakeFiles/voiceDetection.dir/flags.make
CMakeFiles/voiceDetection.dir/src/svm.c.o: ../src/svm.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artik/MFCC_CMAKE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/voiceDetection.dir/src/svm.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/voiceDetection.dir/src/svm.c.o   -c /home/artik/MFCC_CMAKE/src/svm.c

CMakeFiles/voiceDetection.dir/src/svm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/voiceDetection.dir/src/svm.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/artik/MFCC_CMAKE/src/svm.c > CMakeFiles/voiceDetection.dir/src/svm.c.i

CMakeFiles/voiceDetection.dir/src/svm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/voiceDetection.dir/src/svm.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/artik/MFCC_CMAKE/src/svm.c -o CMakeFiles/voiceDetection.dir/src/svm.c.s

CMakeFiles/voiceDetection.dir/src/svm.c.o.requires:

.PHONY : CMakeFiles/voiceDetection.dir/src/svm.c.o.requires

CMakeFiles/voiceDetection.dir/src/svm.c.o.provides: CMakeFiles/voiceDetection.dir/src/svm.c.o.requires
	$(MAKE) -f CMakeFiles/voiceDetection.dir/build.make CMakeFiles/voiceDetection.dir/src/svm.c.o.provides.build
.PHONY : CMakeFiles/voiceDetection.dir/src/svm.c.o.provides

CMakeFiles/voiceDetection.dir/src/svm.c.o.provides.build: CMakeFiles/voiceDetection.dir/src/svm.c.o


CMakeFiles/voiceDetection.dir/src/augmentation.c.o: CMakeFiles/voiceDetection.dir/flags.make
CMakeFiles/voiceDetection.dir/src/augmentation.c.o: ../src/augmentation.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artik/MFCC_CMAKE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/voiceDetection.dir/src/augmentation.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/voiceDetection.dir/src/augmentation.c.o   -c /home/artik/MFCC_CMAKE/src/augmentation.c

CMakeFiles/voiceDetection.dir/src/augmentation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/voiceDetection.dir/src/augmentation.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/artik/MFCC_CMAKE/src/augmentation.c > CMakeFiles/voiceDetection.dir/src/augmentation.c.i

CMakeFiles/voiceDetection.dir/src/augmentation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/voiceDetection.dir/src/augmentation.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/artik/MFCC_CMAKE/src/augmentation.c -o CMakeFiles/voiceDetection.dir/src/augmentation.c.s

CMakeFiles/voiceDetection.dir/src/augmentation.c.o.requires:

.PHONY : CMakeFiles/voiceDetection.dir/src/augmentation.c.o.requires

CMakeFiles/voiceDetection.dir/src/augmentation.c.o.provides: CMakeFiles/voiceDetection.dir/src/augmentation.c.o.requires
	$(MAKE) -f CMakeFiles/voiceDetection.dir/build.make CMakeFiles/voiceDetection.dir/src/augmentation.c.o.provides.build
.PHONY : CMakeFiles/voiceDetection.dir/src/augmentation.c.o.provides

CMakeFiles/voiceDetection.dir/src/augmentation.c.o.provides.build: CMakeFiles/voiceDetection.dir/src/augmentation.c.o


CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o: CMakeFiles/voiceDetection.dir/flags.make
CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o: ../src/kiss_fft.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artik/MFCC_CMAKE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o   -c /home/artik/MFCC_CMAKE/src/kiss_fft.c

CMakeFiles/voiceDetection.dir/src/kiss_fft.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/voiceDetection.dir/src/kiss_fft.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/artik/MFCC_CMAKE/src/kiss_fft.c > CMakeFiles/voiceDetection.dir/src/kiss_fft.c.i

CMakeFiles/voiceDetection.dir/src/kiss_fft.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/voiceDetection.dir/src/kiss_fft.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/artik/MFCC_CMAKE/src/kiss_fft.c -o CMakeFiles/voiceDetection.dir/src/kiss_fft.c.s

CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o.requires:

.PHONY : CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o.requires

CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o.provides: CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o.requires
	$(MAKE) -f CMakeFiles/voiceDetection.dir/build.make CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o.provides.build
.PHONY : CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o.provides

CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o.provides.build: CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o


CMakeFiles/voiceDetection.dir/src/filter.c.o: CMakeFiles/voiceDetection.dir/flags.make
CMakeFiles/voiceDetection.dir/src/filter.c.o: ../src/filter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artik/MFCC_CMAKE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/voiceDetection.dir/src/filter.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/voiceDetection.dir/src/filter.c.o   -c /home/artik/MFCC_CMAKE/src/filter.c

CMakeFiles/voiceDetection.dir/src/filter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/voiceDetection.dir/src/filter.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/artik/MFCC_CMAKE/src/filter.c > CMakeFiles/voiceDetection.dir/src/filter.c.i

CMakeFiles/voiceDetection.dir/src/filter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/voiceDetection.dir/src/filter.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/artik/MFCC_CMAKE/src/filter.c -o CMakeFiles/voiceDetection.dir/src/filter.c.s

CMakeFiles/voiceDetection.dir/src/filter.c.o.requires:

.PHONY : CMakeFiles/voiceDetection.dir/src/filter.c.o.requires

CMakeFiles/voiceDetection.dir/src/filter.c.o.provides: CMakeFiles/voiceDetection.dir/src/filter.c.o.requires
	$(MAKE) -f CMakeFiles/voiceDetection.dir/build.make CMakeFiles/voiceDetection.dir/src/filter.c.o.provides.build
.PHONY : CMakeFiles/voiceDetection.dir/src/filter.c.o.provides

CMakeFiles/voiceDetection.dir/src/filter.c.o.provides.build: CMakeFiles/voiceDetection.dir/src/filter.c.o


CMakeFiles/voiceDetection.dir/src/svm2.cpp.o: CMakeFiles/voiceDetection.dir/flags.make
CMakeFiles/voiceDetection.dir/src/svm2.cpp.o: ../src/svm2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artik/MFCC_CMAKE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/voiceDetection.dir/src/svm2.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/voiceDetection.dir/src/svm2.cpp.o -c /home/artik/MFCC_CMAKE/src/svm2.cpp

CMakeFiles/voiceDetection.dir/src/svm2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voiceDetection.dir/src/svm2.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artik/MFCC_CMAKE/src/svm2.cpp > CMakeFiles/voiceDetection.dir/src/svm2.cpp.i

CMakeFiles/voiceDetection.dir/src/svm2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voiceDetection.dir/src/svm2.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artik/MFCC_CMAKE/src/svm2.cpp -o CMakeFiles/voiceDetection.dir/src/svm2.cpp.s

CMakeFiles/voiceDetection.dir/src/svm2.cpp.o.requires:

.PHONY : CMakeFiles/voiceDetection.dir/src/svm2.cpp.o.requires

CMakeFiles/voiceDetection.dir/src/svm2.cpp.o.provides: CMakeFiles/voiceDetection.dir/src/svm2.cpp.o.requires
	$(MAKE) -f CMakeFiles/voiceDetection.dir/build.make CMakeFiles/voiceDetection.dir/src/svm2.cpp.o.provides.build
.PHONY : CMakeFiles/voiceDetection.dir/src/svm2.cpp.o.provides

CMakeFiles/voiceDetection.dir/src/svm2.cpp.o.provides.build: CMakeFiles/voiceDetection.dir/src/svm2.cpp.o


# Object files for target voiceDetection
voiceDetection_OBJECTS = \
"CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o" \
"CMakeFiles/voiceDetection.dir/src/utils.c.o" \
"CMakeFiles/voiceDetection.dir/src/gemm.c.o" \
"CMakeFiles/voiceDetection.dir/src/record.c.o" \
"CMakeFiles/voiceDetection.dir/src/mfcc.c.o" \
"CMakeFiles/voiceDetection.dir/src/svm.c.o" \
"CMakeFiles/voiceDetection.dir/src/augmentation.c.o" \
"CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o" \
"CMakeFiles/voiceDetection.dir/src/filter.c.o" \
"CMakeFiles/voiceDetection.dir/src/svm2.cpp.o"

# External object files for target voiceDetection
voiceDetection_EXTERNAL_OBJECTS =

libvoiceDetection.so: CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o
libvoiceDetection.so: CMakeFiles/voiceDetection.dir/src/utils.c.o
libvoiceDetection.so: CMakeFiles/voiceDetection.dir/src/gemm.c.o
libvoiceDetection.so: CMakeFiles/voiceDetection.dir/src/record.c.o
libvoiceDetection.so: CMakeFiles/voiceDetection.dir/src/mfcc.c.o
libvoiceDetection.so: CMakeFiles/voiceDetection.dir/src/svm.c.o
libvoiceDetection.so: CMakeFiles/voiceDetection.dir/src/augmentation.c.o
libvoiceDetection.so: CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o
libvoiceDetection.so: CMakeFiles/voiceDetection.dir/src/filter.c.o
libvoiceDetection.so: CMakeFiles/voiceDetection.dir/src/svm2.cpp.o
libvoiceDetection.so: CMakeFiles/voiceDetection.dir/build.make
libvoiceDetection.so: CMakeFiles/voiceDetection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/artik/MFCC_CMAKE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX shared library libvoiceDetection.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/voiceDetection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/voiceDetection.dir/build: libvoiceDetection.so

.PHONY : CMakeFiles/voiceDetection.dir/build

CMakeFiles/voiceDetection.dir/requires: CMakeFiles/voiceDetection.dir/src/syll_fragmentation.c.o.requires
CMakeFiles/voiceDetection.dir/requires: CMakeFiles/voiceDetection.dir/src/utils.c.o.requires
CMakeFiles/voiceDetection.dir/requires: CMakeFiles/voiceDetection.dir/src/gemm.c.o.requires
CMakeFiles/voiceDetection.dir/requires: CMakeFiles/voiceDetection.dir/src/record.c.o.requires
CMakeFiles/voiceDetection.dir/requires: CMakeFiles/voiceDetection.dir/src/mfcc.c.o.requires
CMakeFiles/voiceDetection.dir/requires: CMakeFiles/voiceDetection.dir/src/svm.c.o.requires
CMakeFiles/voiceDetection.dir/requires: CMakeFiles/voiceDetection.dir/src/augmentation.c.o.requires
CMakeFiles/voiceDetection.dir/requires: CMakeFiles/voiceDetection.dir/src/kiss_fft.c.o.requires
CMakeFiles/voiceDetection.dir/requires: CMakeFiles/voiceDetection.dir/src/filter.c.o.requires
CMakeFiles/voiceDetection.dir/requires: CMakeFiles/voiceDetection.dir/src/svm2.cpp.o.requires

.PHONY : CMakeFiles/voiceDetection.dir/requires

CMakeFiles/voiceDetection.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/voiceDetection.dir/cmake_clean.cmake
.PHONY : CMakeFiles/voiceDetection.dir/clean

CMakeFiles/voiceDetection.dir/depend:
	cd /home/artik/MFCC_CMAKE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/artik/MFCC_CMAKE /home/artik/MFCC_CMAKE /home/artik/MFCC_CMAKE/build /home/artik/MFCC_CMAKE/build /home/artik/MFCC_CMAKE/build/CMakeFiles/voiceDetection.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/voiceDetection.dir/depend

