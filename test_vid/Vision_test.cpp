/* Vision_test.cpp - program to test class Vision

	 created 2/28/17 BD

	 info:

	 2018:
	 - to build project, in test_vid directory issue "make"
	 - to run project, be in Vision directory
	 - cmake - not sure where

	 2016-17:
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

#define MQTT_HOST "roborio-2358-frc.local" // roborio-2358-frc.local
// #define MQTT_HOST "192.168.1.112" // laptop
// #define MQTT_HOST "localhost" // laptop
#define mqtt_port 1183


void usage(){
	printf("usage: Vision [OPTIONS] [fid]\n");
	printf("where:\n");
	printf("       -h - print this help screen\n");
	printf("       -d - display processing frames\n");
	printf("       -m[=addr] - publish distance and angle to MQTT broker [optional address]\n");
	printf("       -p - use TBB for parallel processing on all 4 cores\n");
	printf("       -g - for gear. Default is boiler\n");
	printf("       fid - file name to process\n");
	printf("             if no file name is given, use camera 0\n");
}

int main(int argc, char** argv){
	
	Vision vis;
	int i;
	int ret = 0;
	
	char* fid = 0;
	vis.displayf = 0;
	vis.parallelf = 0;
	int mosqf = 0;
	int filterf = 0; // default to boiler
	char mqtt_host[256];
	
	if (argc > 6){
		usage();
		return -1;
	}

	// copy default server address
	strncpy(mqtt_host, MQTT_HOST, 255);
	mqtt_host[255] = 0;
	
	if(argc > 1){
		for(i = 1; i < argc; i++) { 
			if(*argv[i] == '-'){
				switch(argv[i][1]){
				case 'd': // display
					vis.displayf = 1;
					break;
				
				case 'g': // gear or boiler
					filterf = 1;
					break;
				
				case 'm': // MQTT
					mosqf = 1;
					if(argv[i][2] == '=') {
						// get MQTT server address
						strncpy(mqtt_host, &argv[i][3], 255);
						mqtt_host[255] = 0;
					}
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
	printf("MQTT server: *%s*\n", mqtt_host);

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
	// Changed to use new template image of vision target for hatches
	ret = vis.process_template(TEMPLATE_FILE);
	if(ret != 0) {
	  printf("Could not find template file %s\n", TEMPLATE_FILE);
	  exit(-1);
	}
	
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
		printf("mosquitto_connect ret: %d\n", rc);
	}
	
	tstart = Vision::gettime_usec();
	for(;;){
		cap >> frame;
		if(frame.empty()) break;

		printf("Columns: %d Rows: %d\n", frame.cols, frame.rows);
		
		tprocess_start = vis.gettime_usec();
		ret = vis.process(frame, imgDraw, filterf);
		printf("vis.process ret: %d\n", ret);
		tprocess_end = Vision::gettime_usec();
		frames++;
		tdelta = tprocess_end - tprocess_start;
		printf("Process time: %lld\n", tdelta);

		if(ret) {
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
		}

		if(vis.displayf) {
			cv::imshow("Contours", imgDraw);
		}

		// one or the other of the following lines (or neither)
		// not both
		// if(cv::waitKey(1) >= 0) break;
		cv::waitKey(0);
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

