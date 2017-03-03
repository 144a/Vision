/* Vision_test.cpp - program to test class Vision

	 created 2/28/17 BD

	 info:
	 - to make OpenCV project, copy and edit CMakeLists.tst
	 - cd to "build" directory under source
	 $ cmake ..
	 $ make
	
	 to run it:

pi@raspberrypi:~/TechClub/2017/Vision_pll $ test_vid/build/Vision Test_Vids/20170402_17\:03\:07.mp4

*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include "Vision.h"



void usage(){
	printf("usage: Vision [-h] [-d] [-p] [fid]\n");
	printf("where:\n");
	printf("       -h - print this help screen\n");
	printf("       -d - display processing frames\n");
	printf("       -p - use TBB for parallel processing on all 4 cores\n");
	printf("       fid - file name to process\n");
	printf("             if no file name is given, use camera 0\n");
}

int main(int argc, char** argv){
	
	Vision vis;
	int i;
	
	char* fid = 0;
	vis.displayf = 0;
	vis.parallelf = 0;
	
	if (argc > 4){
		usage();
		return -1;
	}
	
	if(argc > 1){
		for(i = 1; i < argc; i++) { 
			if(*argv[i] == '-'){
				switch(argv[i][1]){
				case 'd':
					vis.displayf = 1;
					break;
				
				case 'p':
					vis.setParallel(1);
					break;
				
				case 'h':
					usage();
					return 0;
					break;

				}
			} else {
				fid = argv[i];	
			}		
		}
	}

	printf("*%s*", fid);
	if(vis.displayf){
		cv::namedWindow("Contours", cv::WINDOW_AUTOSIZE);
	}
	cv::VideoCapture cap;
	if(fid == 0){
		cap.open(0);              //open first camera
	}else{
		cap.open(fid);
	}
	if(!cap.isOpened()){        //check if we succeeded
		std::cerr << "Couldn't open capture. Life sucks." <<std::endl;
		return -1;
	}
	
	cv::Mat frame;
	cv::Mat imgDraw;
	vis.process_template();
	long long tprocess_start;
	long long tprocess_end;
	long long tdelta;
	long frames = 0;
	long long tstart;
	long long tend;
	double trun;
	
	tstart = Vision::gettime_usec();
	for(;;){
		cap >> frame;
		if(frame.empty()) break;
		tprocess_start = vis.gettime_usec();
		vis.process(frame, imgDraw);
		tprocess_end = Vision::gettime_usec();
		frames++;
		tdelta = tprocess_end - tprocess_start;
		printf("Process time: %lld\n", tdelta);
		if(vis.displayf){
			cv::imshow("Contours", imgDraw);
		}
		if(cv::waitKey(1) >= 0) break;
		// cv::waitKey(0);
	}
	tend = Vision::gettime_usec();

	trun = (1.0 * tend - tstart)/1e6;
	printf("time: %7.3lf frames: %ld  fps: %6.2lf\n", trun,
				 frames, (1.0 * frames/trun));
	printf("time_t: %d suseconds_t: %d long: %d long long %d\n",
				 sizeof(time_t), sizeof(suseconds_t), sizeof(long), sizeof(long long));
	return 0;
	
}

