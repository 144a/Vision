/* test_vid.cpp for FRC - Example 2-1 from OpenCV book

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

#define TEMPLATE_FILE "template17top.jpg"

// Globals
	
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
int HMin = 70;
int HMax = 100;
int SMin = 125;
int SMax = 255;
int VMin = 125;
int VMax = 255;

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

std::vector< std::vector< cv::Point> > contoursTemplate;

int process_template()
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
int distance(int pixelheight)
{
	return 24.71815424 * pow(.9901601227, pixelheight);
}

int process(cv::Mat img, cv::Mat &imgDraw)
{
	// cv::Mat img = cv::imread(argv[1], -1);
	// if(img.empty()) return -1;
	// cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
	// cv::imshow("Input", img);

	// first convert to HSV
	cv::Mat imgHSV;
	cv::cvtColor(img, imgHSV, CV_BGR2HSV);

	// threshold image
	cv::Mat imgThresh;
	
	// cv::threshold(imgHSV, imgThresh, );
	cv::inRange(imgHSV, cv::Scalar(HMin, SMin, VMin), cv::Scalar(HMax, SMax, VMax), imgThresh);
	// cv::namedWindow("Threshold", cv::WINDOW_AUTOSIZE);
	// cv::imshow("Threshold", imgThresh);

	// erode and dilate
	cv::Mat imgOpen;
	cv::morphologyEx(imgThresh, imgOpen, CV_MOP_OPEN, cv::Mat());
	// cv::namedWindow("Open", cv::WINDOW_AUTOSIZE);
	// cv::imshow("Open", imgOpen);

	// find countours
	// cv::Mat imgDraw(img);
	imgDraw = img;
	cv::Mat imgCont(imgOpen);
	std::vector< std::vector< cv::Point> > contours;
	cv::findContours(imgCont, contours, cv::noArray(), cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
	std::vector< cv::Moments > moms;
	imgCont = cv::Scalar::all(0);
	cv::drawContours(imgDraw, contours, -1, cv::Scalar::all(255));

	printf("\nFound %d contours\n", contours.size());

	
	// find bounding rectangle
	cv::namedWindow("Contours", cv::WINDOW_AUTOSIZE);

	for(int i = 0; i < contours.size(); i++) {
		// bounding rectange
		// cv::Rect rect1 = cv::boundingRect(contours[i]);
		// cv::rectangle(imgDraw, rect1, cv::Scalar(0, 255, 0));
		// minimum area (rotated) rectangle
		cv::Rect rect1 = cv::boundingRect(contours[i]);

		imgDraw = img.clone();

		/*
			cv::Point2f vertices[4];
			rect1.points(vertices);
			for (int j = 0; j < 4; j++) {
			cv::line(imgDraw,  vertices[j], vertices[(j+1)%4], cv::Scalar(0,255,0));
			}
		*/
		cv::rectangle(imgDraw,rect1,cv::Scalar(0,255,0));
		
		// compute Moments so we can find center of each contour (for printing for now)
		cv::Moments mom1 = cv::moments(contours[i], true);
		moms.push_back(mom1);
		cv::Point center(mom1.m10/mom1.m00, mom1.m01/mom1.m00);
		cv::Point ptText(center);

		
		
		// printf("m00: %lf m10: %lf m01: %lf x: %lf, y: %lf\n", mom1.m00, mom1.m10, mom1.m01,
		// mom1.m10/mom1.m00, mom1.m01/mom1.m00);
		
		printf("m00: %6.2lf   h: %3d   w: %3d\n", mom1.m00, rect1.height, rect1.width);
		
		// check match against template
		double match = cv::matchShapes(contoursTemplate[0], contours[i], CV_CONTOURS_MATCH_I3, 0);

		int fontFace = cv::FONT_HERSHEY_SIMPLEX;
		double fontScale = 0.5;
		char s1[255];
		// sprintf(s1, "#%d %0.2lf", i, match);
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
		//cv::imshow("Contours", imgDraw);
		//cv::waitKey(0);

	}
	for (std::vector<cv::Moments>::iterator it = moms.begin() ; it != moms.end(); it++)	{
		//		printf("m00: %6.2lf   h: %3d   w: %3d\n", mom1.m00, rect1.height, rect1.width);
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

int main(int argc, char** argv){
	
	cv::namedWindow("Contours", cv::WINDOW_AUTOSIZE);
	
	cv::VideoCapture cap;
	if(argc==1){
		cap.open(0);              //open first camera
	}else{
		cap.open(argv[1]);
	}
	if(!cap.isOpened()){        //check if we succeeded
		std::cerr << "Couldn't open capture. Life sucks." <<std::endl;
		return -1;
	}
	
	cv::Mat frame;
	cv::Mat imgDraw;
	process_template();

	for(;;){
		cap >> frame;
		if(frame.empty()) break;
		process(frame, imgDraw);
		cv::imshow("Contours", imgDraw);
		if(cv::waitKey(33) >= 0) break;
		//cv::waitKey(0);
	}
	return 0;
	
}

