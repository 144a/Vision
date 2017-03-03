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
#include "Vision.h"
#include "HSV_Parallel.h"
#include "Thresh_Parallel.h"

Vision::Vision() 
{
	/*
	//extract blue
	int HMin = 75; // 120 from robot code
	int HMax = 1300; // 170 from robot code
	int SMin = 180;
	int SMax = 255;
	int VMin = 150;
	int VMax = 255;
	*/
	//extract green
	HMin = 70;
	HMax = 100;
	SMin = 125;
	SMax = 255;
	VMin = 125;
	VMax = 255;

	/*
		Colors from new template *tentative*
		bright:
		H:180
		S:38
		L:100
		middle:
		H:177
		S:94
		L:98
		dark:
		H:165
		S:94
		L:82
	*/

	displayf = 0;
	parallelf = 0;
}



int Vision::process_template()
{
	// ok, now lets get ready to match template.jpg
	cv::Mat imgTemplate = cv::imread(TEMPLATE_FILE, -1);
	if(imgTemplate.empty()) return -1;
	cv::cvtColor(imgTemplate, imgTemplate, CV_BGR2HSV);
	cv::inRange(imgTemplate, cv::Scalar(HMin, SMin, VMin), cv::Scalar(HMax, SMax, VMax), imgTemplate);
	cv::morphologyEx(imgTemplate, imgTemplate, CV_MOP_OPEN, cv::Mat());
	cv::findContours(imgTemplate, contoursTemplate, cv::noArray(), cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
	
	// cv::namedWindow("Template", cv::WINDOW_AUTOSIZE);
	// cv::imshow("Template", imgTemplate);
	// cv::waitKey(0);

}

// find distance to target
double Vision::distance(int width)
{
	return (-0.2555350554 * width + 24.3431734317);
}

// return Linux time a long long microseconds
long long Vision::gettime_usec()
{
	struct timeval tv1;
	long long ret;
	
	gettimeofday(&tv1, NULL);
	ret = tv1.tv_sec * 1000000 + tv1.tv_usec;
	return ret;
}

void Vision::setParallel(int flag)
{
	parallelf = flag;
}

int Vision::process(cv::Mat img, cv::Mat &imgDraw)
{
	printf("\n");
	// cv::Mat img = cv::imread(argv[1], -1);
	// if(img.empty()) return -1;
	// cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
	// cv::imshow("Input", img);

	// first convert to HSV
	long long tHSVstart = gettime_usec();
	cv::Mat imgHSV =img.clone(); // faster to create and fill with zeros ?

	if(parallelf) {
		// actually, seemed to slow it down a little
		parallel_for_(cv::Range(0, 8), HSV_Parallel(img, imgHSV, CV_BGR2HSV, 8));
	} else {
		cv::cvtColor(img, imgHSV, CV_BGR2HSV);
	}

	long long tHSVend = gettime_usec();
	printf("HSV converison time: %lld usec\n", tHSVend - tHSVstart);

	// threshold image
	cv::Mat imgThresh = cv::Mat::zeros(imgHSV.rows, imgHSV.cols, CV_8U);
	
	long long tthreshstart = gettime_usec();
	// older version
	// cv::threshold(imgHSV, imgThresh, );

	if(parallelf) {
		// improvement - from ~2.7ms to 1.4ms - Yay!
		parallel_for_(cv::Range(0, 4), Thresh_Parallel(imgHSV, imgThresh, cv::Scalar(HMin, SMin, VMin),	cv::Scalar(HMax, SMax, VMax), 4));
	} else {
		// non-parallel version
		cv::inRange(imgHSV, cv::Scalar(HMin, SMin, VMin), cv::Scalar(HMax, SMax, VMax), imgThresh);
	}
	
	long long tthreshend = gettime_usec();
	printf("Threshold time: %lld usec\n", tthreshend - tthreshstart);
	// cv::namedWindow("Threshold", cv::WINDOW_AUTOSIZE);
	// cv::imshow("Threshold", imgThresh);

	// erode and dilate
	long long tmorphstart = gettime_usec();
	// cloning imgThresh takes ~0.5 msec
	cv::Mat imgOpen;
	if(parallelf) {
		// cloning imgThresh in here, and performing Open operation inplace increased from ~9.7msec to ~17.3msec
		// Wow! Just replacing morphologyEx Open operation with erode() followed by dilate reduces Morphology step from ~9.6 msec to 2.4 msec!
		// Process time now around 21-23 msec
		cv::Mat imgTemp;
		cv::erode(imgThresh, imgTemp, cv::Mat());
		cv::dilate(imgTemp, imgOpen, cv::Mat());
	} else {
		cv::morphologyEx(imgThresh, imgOpen, CV_MOP_OPEN, cv::Mat());
	}
	long long tmorphend = gettime_usec();
	printf("Morphology time: %lld usec\n", tmorphend - tmorphstart);

	// cv::namedWindow("Open", cv::WINDOW_AUTOSIZE);
	// cv::imshow("Open", imgOpen);





	// find countours
	// cv::Mat imgDraw(img);
	imgDraw = img;
	cv::Mat imgCont(imgOpen);
	std::vector< std::vector< cv::Point> > contours;
	long long tcontoursstart = gettime_usec();
	cv::findContours(imgCont, contours, cv::noArray(), cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
	long long tcontoursend = gettime_usec();
	printf("Contour time: %lld usec\n", tcontoursend - tcontoursstart);
	std::vector< cv::Moments > moms;
	imgCont = cv::Scalar::all(0);
	if(displayf){
		cv::drawContours(imgDraw, contours, -1, cv::Scalar::all(255));
	}
	std::vector< cv::Rect > rects;

	printf("Found %d contours\n", contours.size());

	// find bounding rectangle
	if(displayf){
		cv::namedWindow("Contours", cv::WINDOW_AUTOSIZE);
	}

	long long tcontloopstart = gettime_usec();
	for(int i = 0; i < contours.size(); i++) {
		// bounding rectangle
		
		cv::Rect rect1 = cv::boundingRect(contours[i]);
		if(displayf){
			cv::rectangle(imgDraw, rect1, cv::Scalar(0, 255, 0));
		}
		
		// minimum area (rotated) rectangle
		// cv::RotatedRect rect1 = cv::minAreaRect(contours[i]);

		rects.push_back(rect1);
		// removed this line when not dsiplaying
		// reduced Contour loop time from ~3.4 msec to 0.15 msec for 2 countours
		if(displayf) {
			imgDraw = img.clone();
		}
			
		/*
			cv::Point2f vertices[4];
			rect1.points(vertices);
			for (int j = 0; j < 4; j++) {
			cv::line(imgDraw,  vertices[j], vertices[(j+1)%4], cv::Scalar(0,255,0));
			}
		*/
		
		// compute Moments so we can find center of each contour (for printing for now)
		long long tmomentsstart = gettime_usec();
		cv::Moments mom1 = cv::moments(contours[i], true);
		long long tmomentsend = gettime_usec();
		printf("Moments time: %lld\n", tmomentsend - tmomentsstart);
		moms.push_back(mom1);
		cv::Point center(mom1.m10/mom1.m00, mom1.m01/mom1.m00);
		cv::Point ptText(center);
		
		
		// printf("m00: %lf m10: %lf m01: %lf x: %lf, y: %lf\n", mom1.m00, mom1.m10, mom1.m01,
		// mom1.m10/mom1.m00, mom1.m01/mom1.m00);
		
		printf("m00: %6.2lf   h: %3d   w: %3d y: %3d\n", mom1.m00, rect1.height, rect1.width, rect1.y);
		
		// check match against template
		long long tmatchstart = gettime_usec();
		double match = cv::matchShapes(contoursTemplate[0], contours[i], CV_CONTOURS_MATCH_I3, 0);
		long long tmatchend = gettime_usec();
		printf("Match Shapes time: %lld\n", tmatchend - tmatchstart);
		int fontFace = cv::FONT_HERSHEY_SIMPLEX;
		double fontScale = 0.5;
		char s1[255];
 		// sprintf(s1, "#%d %0.2lf", i, match);
		if(displayf){
			if((match <= 3.0)) {
			
				sprintf(s1, "#%d %0.2lf", i, match);
				cv::putText(imgDraw, s1, ptText, fontFace, fontScale, cv::Scalar(0, 0, 255), 1); 

				sprintf(s1, "x: %d", center.x);
				ptText.y += 15;
				cv::putText(imgDraw, s1, ptText, fontFace, fontScale, cv::Scalar(0, 0, 255), 1); 

				sprintf(s1, "y: %d", center.y);
				ptText.y += 15;
				cv::putText(imgDraw, s1, ptText, fontFace, fontScale, cv::Scalar(0, 0, 255), 1);
			
				// print distance from target to cli
				//printf("%d feet away\n", distance(240.0 - center.y));
			
			} else {
				cv::putText(imgDraw, s1, center, fontFace, fontScale, cv::Scalar(255, 255, 255), 2);
			}
		}
		//cv::imshow("Contours", imgDraw);
		//cv::waitKey(0);
	}
	long long tcontloopend = gettime_usec();
	printf("Contour loop time: %lld usec\n", tcontloopend - tcontloopstart);

	/*
		std::vector<cv::Moments>::iterator itM = moms.begin();
		std::vector<cv::Rect>::iterator itR = rects.begin();
	
		while(itM != moms.end())	{
		printf("m00: %6.2lf   h: %3d   w: %3d\n", itM->m00 , itR->height, itR->width);
		itM++;
		itR++;
		}
	*/
	
	/*
	// Filter Contours
	std::vector< cv::Rect > nrects;
	std::vector< cv::Moments > nmoms;

	for(int iter = 0; iter < moms.size();) {
	if(moms[iter].m00 < 100 * 1.0) {
	nmoms.push_back(moms[iter]);
	nrects.push_back(rects[iter]);
	} else {
	iter++;
	}
	}
	*/
	
	/*
	// using indexes
	std::vector<cv::Rect>::iterator itR = rects.begin();
	std::vector<cv::Rect>::iterator itR2 = rects.begin();

	std::vector< cv::Rect > nrects;

	while(itR != rects.end()) {
	itR2 = rects.begin();
	while(itR2 != rects.end()) {
	if((((1.0 * itR2->height)/(1.0 * itR->y - 1.0 * itR2->y)) < 80) && (((1.0 * itR2->height)/(1.0 * itR->y - 1.0 * itR2->y)) > 55)) {
	nrects.push_back(itR);
	nrects.push_back(itR2);
	rects.clear();
	rects.push_back(nrects[0]);
	rects.push_back(nrects[1]);
	}
	itR2++;
	}
	itR++;
	}
	

	// using iterators
	std::vector< cv::Rect > nrects;
	
	for(int iter = 0; iter < rects.size(); iter++) {
	for(int iter2 = 0; iter2 < rects.size(); iter2++) {
	if(true or((((1.0 * rects[iter2].height)/(1.0 * rects[iter].y - 1.0 * rects[iter2].y)) < 80) && (((1.0 * rects[iter2].height)/(1.0 * rects[iter].y - 1.0 * rects[iter2].y)) > 55))) {
	nrects.push_back(rects[iter]);
	nrects.push_back(rects[iter2]);
	rects.clear();
	rects.push_back(nrects[0]);
	rects.push_back(nrects[1]);
					
	}
	}
	}

	*/
	
	if(contours.size() >= 1){
		double y[2];
		y[0] = 1.0 * rects[0].y;
		y[1] = 1.0 * rects[1].y;
		printf("distance!?!: %6.2lf\n", distance(rects[0].width));
		printf("ratio: %6.2lf   %6.2lf %6.2lf\n", (1.0 * rects[1].height)/(y[0] - y[1]), y[0], y[1]);
		printf("Analysed %3d Contours\n", rects.size());
	
		//printf("m00: %6.2lf   h: %3d   w: %3d\n", moms[0].m00 , rects[0].height, rects[0].width);
	}
	//cv::destroyAllWindows(); 

	return 0;
}

/*
	int main(int argc, char *argv[])
	{
	cv::namedWindow("Contours", cv::WINDOW_AUTOSIZE);
	cv::VideoCapture cap;
	cap.open(std::string(argv[1]));
	cv::Mat frame;
	cv::Mat imgDraw;;
	process_template();
	while(1) {
	cap >> frame;
	if(!frame.data) break; // ran out of film
	process(frame, imgDraw);
	cv::imshow("Contours", imgDraw);
	if(cv::waitKey(1) >= 0) break;
	}
	return 0;
	}
*/

/*
void usage(){
	printf("usage: Vision [-h] [-d] [fid]\n");
	printf("where:\n");
	printf("       -h - print this help screen\n");
	printf("       -d - display processing frames\n");
	printf("       fid - file name to process\n");
	printf("             if no file name is given, use camera 0\n");
}

int main(int argc, char** argv){
	
	Vision vis;

	char* fid = 0;
	vis.displayf = 0;
	
	if (argc > 3){
		usage();
		return -1;
	}
	
	if(argc > 1){
		if(*argv[1] == '-'){
			switch(argv[1][1]){
			case 'd':
				vis.displayf = 1;
				if (argc > 2){
					fid = argv[2];
				}
				break;
				
			case 'h':
				usage();
				return 0;
				break;

			}
		} else {
			fid = argv[1];	
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

*/
