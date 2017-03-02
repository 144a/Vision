/* Vision.cpp from test_vid.cpp for FRC - Example 2-1 from OpenCV book

	 created 3/25/16 BD from test.cpp 
	 - from 3/23 version
	 - change to reading from video file and processing each frame
	 updated 3/27/16
	 - LATER, add command line for following:
	 - don't print if > threshold
	 - add angle
	 updated 1/21/17x
	 - pull template processing out of process()
	
	
	 info:
	 - to make OpenCV project, copy and edit CMakeLists.tst
	 $ cmake .
	 $ make
	
	 to run it:
	
	 bobd@HP-Mini:~/opencv/install_opencv/OpenCV/opencv-2.4.8/build$ ~/TechClub/2016/vision/opencv/test_vid/test_vid ~/TechClub/2016/p5_auto.mjpg 
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#define TEMPLATE_FILE "template17top.jpg"


class Vision
{
 public:
	Vision();
	~Vision() {};

	// Globals
	int displayf;

	//extract green
	int HMin;
	int HMax;
	int SMin;
	int SMax;
	int VMin;
	int VMax;

	std::vector< std::vector< cv::Point> > contoursTemplate;

	int process_template();
	static double distance(int width);
	static long long gettime_usec();
	int process(cv::Mat img, cv::Mat &imgDraw);

} ;
