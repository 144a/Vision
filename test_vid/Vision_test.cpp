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
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include "Vision.h"
#include <mosquitto.h>

#define mqtt_host "localhost"
#define mqtt_port 1183


void usage(){
	printf("usage: Vision [-h] [-d] [-m] [-p] [fid]\n");
	printf("where:\n");
	printf("       -h - print this help screen\n");
	printf("       -d - display processing frames\n");
	printf("       -m - publish distance and angle to MQTT broker\n");
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
	int mosqf = 0;
	
	if (argc > 5){
		usage();
		return -1;
	}
	
	if(argc > 1){
		for(i = 1; i < argc; i++) { 
			if(*argv[i] == '-'){
				switch(argv[i][1]){
				case 'd': // display
					vis.displayf = 1;
					break;
				
				case 'm': // MQTT
					mosqf = 1;
					break;
					
				case 'p': // parallel execution using TBB
					vis.setParallel(1);
					break;
				
				case 'h': // help
					usage();
					return 0;
					break;

				}
			} else {
				fid = argv[i];	
			}		
		}
	}

	printf("*%s*\n", fid);
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
	int rc;
	char stemp[80];
	struct mosquitto *mosq;
	char clientid[24];

	if(mosqf) {
		mosquitto_lib_init();
	
		memset(clientid, 0, 24);
		snprintf(clientid, 23, "vision_%d", getpid());
		mosq = mosquitto_new(clientid, true, 0);
	
		if(!mosq)
			{
				printf("Couldn't create MQTT client!\n");
				exit(-1);
			}
	
		rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 60);
	}
	
	tstart = Vision::gettime_usec();
	for(;;){
		cap >> frame;
		if(frame.empty()) break;

		printf("Columns: %d Rows: %d\n", frame.cols, frame.rows);
		
		tprocess_start = vis.gettime_usec();
		vis.process(frame, imgDraw);
		tprocess_end = Vision::gettime_usec();
		frames++;
		tdelta = tprocess_end - tprocess_start;
		printf("Process time: %lld\n", tdelta);

		sprintf(stemp, "%6.2lf %6.2lf", vis.distance, vis.angle);
		
		if(mosqf) {
			mosquitto_publish(mosq, 0, "PI/CV/SHOOT/DATA", strlen(stemp), stemp, 0, 0);
			rc = mosquitto_loop(mosq, 0, 1);
			if(rc){
				printf("connection error!\n");
				// sleep(10);
				mosquitto_reconnect(mosq);
			}
		}

		if(vis.displayf) {
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

	if(mosqf) {
		if(mosq) {
			mosquitto_destroy(mosq);
		}
		mosquitto_lib_cleanup();
	}
	
	return 0;
	
}

