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
CMAKE_SOURCE_DIR = /home/bobd/TechClub/2018/Vision/test_vid

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bobd/TechClub/2018/Vision/test_vid

# Include any dependencies generated for this target.
include CMakeFiles/Vision.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Vision.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Vision.dir/flags.make

CMakeFiles/Vision.dir/Vision.cpp.o: CMakeFiles/Vision.dir/flags.make
CMakeFiles/Vision.dir/Vision.cpp.o: Vision.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bobd/TechClub/2018/Vision/test_vid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Vision.dir/Vision.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Vision.dir/Vision.cpp.o -c /home/bobd/TechClub/2018/Vision/test_vid/Vision.cpp

CMakeFiles/Vision.dir/Vision.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Vision.dir/Vision.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bobd/TechClub/2018/Vision/test_vid/Vision.cpp > CMakeFiles/Vision.dir/Vision.cpp.i

CMakeFiles/Vision.dir/Vision.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Vision.dir/Vision.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bobd/TechClub/2018/Vision/test_vid/Vision.cpp -o CMakeFiles/Vision.dir/Vision.cpp.s

CMakeFiles/Vision.dir/Vision.cpp.o.requires:

.PHONY : CMakeFiles/Vision.dir/Vision.cpp.o.requires

CMakeFiles/Vision.dir/Vision.cpp.o.provides: CMakeFiles/Vision.dir/Vision.cpp.o.requires
	$(MAKE) -f CMakeFiles/Vision.dir/build.make CMakeFiles/Vision.dir/Vision.cpp.o.provides.build
.PHONY : CMakeFiles/Vision.dir/Vision.cpp.o.provides

CMakeFiles/Vision.dir/Vision.cpp.o.provides.build: CMakeFiles/Vision.dir/Vision.cpp.o


CMakeFiles/Vision.dir/Vision_test.cpp.o: CMakeFiles/Vision.dir/flags.make
CMakeFiles/Vision.dir/Vision_test.cpp.o: Vision_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bobd/TechClub/2018/Vision/test_vid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Vision.dir/Vision_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Vision.dir/Vision_test.cpp.o -c /home/bobd/TechClub/2018/Vision/test_vid/Vision_test.cpp

CMakeFiles/Vision.dir/Vision_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Vision.dir/Vision_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bobd/TechClub/2018/Vision/test_vid/Vision_test.cpp > CMakeFiles/Vision.dir/Vision_test.cpp.i

CMakeFiles/Vision.dir/Vision_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Vision.dir/Vision_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bobd/TechClub/2018/Vision/test_vid/Vision_test.cpp -o CMakeFiles/Vision.dir/Vision_test.cpp.s

CMakeFiles/Vision.dir/Vision_test.cpp.o.requires:

.PHONY : CMakeFiles/Vision.dir/Vision_test.cpp.o.requires

CMakeFiles/Vision.dir/Vision_test.cpp.o.provides: CMakeFiles/Vision.dir/Vision_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/Vision.dir/build.make CMakeFiles/Vision.dir/Vision_test.cpp.o.provides.build
.PHONY : CMakeFiles/Vision.dir/Vision_test.cpp.o.provides

CMakeFiles/Vision.dir/Vision_test.cpp.o.provides.build: CMakeFiles/Vision.dir/Vision_test.cpp.o


CMakeFiles/Vision.dir/HSV_Parallel.cpp.o: CMakeFiles/Vision.dir/flags.make
CMakeFiles/Vision.dir/HSV_Parallel.cpp.o: HSV_Parallel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bobd/TechClub/2018/Vision/test_vid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Vision.dir/HSV_Parallel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Vision.dir/HSV_Parallel.cpp.o -c /home/bobd/TechClub/2018/Vision/test_vid/HSV_Parallel.cpp

CMakeFiles/Vision.dir/HSV_Parallel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Vision.dir/HSV_Parallel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bobd/TechClub/2018/Vision/test_vid/HSV_Parallel.cpp > CMakeFiles/Vision.dir/HSV_Parallel.cpp.i

CMakeFiles/Vision.dir/HSV_Parallel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Vision.dir/HSV_Parallel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bobd/TechClub/2018/Vision/test_vid/HSV_Parallel.cpp -o CMakeFiles/Vision.dir/HSV_Parallel.cpp.s

CMakeFiles/Vision.dir/HSV_Parallel.cpp.o.requires:

.PHONY : CMakeFiles/Vision.dir/HSV_Parallel.cpp.o.requires

CMakeFiles/Vision.dir/HSV_Parallel.cpp.o.provides: CMakeFiles/Vision.dir/HSV_Parallel.cpp.o.requires
	$(MAKE) -f CMakeFiles/Vision.dir/build.make CMakeFiles/Vision.dir/HSV_Parallel.cpp.o.provides.build
.PHONY : CMakeFiles/Vision.dir/HSV_Parallel.cpp.o.provides

CMakeFiles/Vision.dir/HSV_Parallel.cpp.o.provides.build: CMakeFiles/Vision.dir/HSV_Parallel.cpp.o


CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o: CMakeFiles/Vision.dir/flags.make
CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o: Thresh_Parallel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bobd/TechClub/2018/Vision/test_vid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o -c /home/bobd/TechClub/2018/Vision/test_vid/Thresh_Parallel.cpp

CMakeFiles/Vision.dir/Thresh_Parallel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Vision.dir/Thresh_Parallel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bobd/TechClub/2018/Vision/test_vid/Thresh_Parallel.cpp > CMakeFiles/Vision.dir/Thresh_Parallel.cpp.i

CMakeFiles/Vision.dir/Thresh_Parallel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Vision.dir/Thresh_Parallel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bobd/TechClub/2018/Vision/test_vid/Thresh_Parallel.cpp -o CMakeFiles/Vision.dir/Thresh_Parallel.cpp.s

CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o.requires:

.PHONY : CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o.requires

CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o.provides: CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o.requires
	$(MAKE) -f CMakeFiles/Vision.dir/build.make CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o.provides.build
.PHONY : CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o.provides

CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o.provides.build: CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o


# Object files for target Vision
Vision_OBJECTS = \
"CMakeFiles/Vision.dir/Vision.cpp.o" \
"CMakeFiles/Vision.dir/Vision_test.cpp.o" \
"CMakeFiles/Vision.dir/HSV_Parallel.cpp.o" \
"CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o"

# External object files for target Vision
Vision_EXTERNAL_OBJECTS =

Vision: CMakeFiles/Vision.dir/Vision.cpp.o
Vision: CMakeFiles/Vision.dir/Vision_test.cpp.o
Vision: CMakeFiles/Vision.dir/HSV_Parallel.cpp.o
Vision: CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o
Vision: CMakeFiles/Vision.dir/build.make
Vision: /usr/local/lib/libopencv_stitching.so.3.4.0
Vision: /usr/local/lib/libopencv_superres.so.3.4.0
Vision: /usr/local/lib/libopencv_videostab.so.3.4.0
Vision: /usr/local/lib/libopencv_aruco.so.3.4.0
Vision: /usr/local/lib/libopencv_bgsegm.so.3.4.0
Vision: /usr/local/lib/libopencv_bioinspired.so.3.4.0
Vision: /usr/local/lib/libopencv_ccalib.so.3.4.0
Vision: /usr/local/lib/libopencv_cvv.so.3.4.0
Vision: /usr/local/lib/libopencv_dnn_objdetect.so.3.4.0
Vision: /usr/local/lib/libopencv_dpm.so.3.4.0
Vision: /usr/local/lib/libopencv_face.so.3.4.0
Vision: /usr/local/lib/libopencv_freetype.so.3.4.0
Vision: /usr/local/lib/libopencv_fuzzy.so.3.4.0
Vision: /usr/local/lib/libopencv_hfs.so.3.4.0
Vision: /usr/local/lib/libopencv_img_hash.so.3.4.0
Vision: /usr/local/lib/libopencv_line_descriptor.so.3.4.0
Vision: /usr/local/lib/libopencv_optflow.so.3.4.0
Vision: /usr/local/lib/libopencv_reg.so.3.4.0
Vision: /usr/local/lib/libopencv_rgbd.so.3.4.0
Vision: /usr/local/lib/libopencv_saliency.so.3.4.0
Vision: /usr/local/lib/libopencv_stereo.so.3.4.0
Vision: /usr/local/lib/libopencv_structured_light.so.3.4.0
Vision: /usr/local/lib/libopencv_surface_matching.so.3.4.0
Vision: /usr/local/lib/libopencv_tracking.so.3.4.0
Vision: /usr/local/lib/libopencv_xfeatures2d.so.3.4.0
Vision: /usr/local/lib/libopencv_ximgproc.so.3.4.0
Vision: /usr/local/lib/libopencv_xobjdetect.so.3.4.0
Vision: /usr/local/lib/libopencv_xphoto.so.3.4.0
Vision: /usr/local/lib/libopencv_shape.so.3.4.0
Vision: /usr/local/lib/libopencv_photo.so.3.4.0
Vision: /usr/local/lib/libopencv_datasets.so.3.4.0
Vision: /usr/local/lib/libopencv_plot.so.3.4.0
Vision: /usr/local/lib/libopencv_text.so.3.4.0
Vision: /usr/local/lib/libopencv_dnn.so.3.4.0
Vision: /usr/local/lib/libopencv_ml.so.3.4.0
Vision: /usr/local/lib/libopencv_video.so.3.4.0
Vision: /usr/local/lib/libopencv_calib3d.so.3.4.0
Vision: /usr/local/lib/libopencv_features2d.so.3.4.0
Vision: /usr/local/lib/libopencv_highgui.so.3.4.0
Vision: /usr/local/lib/libopencv_videoio.so.3.4.0
Vision: /usr/local/lib/libopencv_phase_unwrapping.so.3.4.0
Vision: /usr/local/lib/libopencv_flann.so.3.4.0
Vision: /usr/local/lib/libopencv_imgcodecs.so.3.4.0
Vision: /usr/local/lib/libopencv_objdetect.so.3.4.0
Vision: /usr/local/lib/libopencv_imgproc.so.3.4.0
Vision: /usr/local/lib/libopencv_core.so.3.4.0
Vision: CMakeFiles/Vision.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bobd/TechClub/2018/Vision/test_vid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Vision"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Vision.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Vision.dir/build: Vision

.PHONY : CMakeFiles/Vision.dir/build

CMakeFiles/Vision.dir/requires: CMakeFiles/Vision.dir/Vision.cpp.o.requires
CMakeFiles/Vision.dir/requires: CMakeFiles/Vision.dir/Vision_test.cpp.o.requires
CMakeFiles/Vision.dir/requires: CMakeFiles/Vision.dir/HSV_Parallel.cpp.o.requires
CMakeFiles/Vision.dir/requires: CMakeFiles/Vision.dir/Thresh_Parallel.cpp.o.requires

.PHONY : CMakeFiles/Vision.dir/requires

CMakeFiles/Vision.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Vision.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Vision.dir/clean

CMakeFiles/Vision.dir/depend:
	cd /home/bobd/TechClub/2018/Vision/test_vid && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bobd/TechClub/2018/Vision/test_vid /home/bobd/TechClub/2018/Vision/test_vid /home/bobd/TechClub/2018/Vision/test_vid /home/bobd/TechClub/2018/Vision/test_vid /home/bobd/TechClub/2018/Vision/test_vid/CMakeFiles/Vision.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Vision.dir/depend

