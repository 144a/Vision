/* HSV_Parallel - parallel-ize HSV across all 4 cores

	 created 3/1/17 BD

*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "HSV_Parallel.h"

void HSV_Parallel::operator()(const cv::Range& range) const
{
	for (int i = range.start; i < range.end; i++)
		{
			// cv::cvtColor(img, img_out, CV_BGR2HSV);

			// get the stripe that we're wokring on
			cv::Mat in(img_in,
								 cv::Rect(0, (img_in.rows/diff)*i, 
													img_in.cols, img_in.rows/diff));
			cv::Mat out(img_out, cv::Rect(0, (img_out.rows/diff)*i, 
																		img_out.cols, img_out.rows/diff));

			// and now, perform the function
			cv::cvtColor(in, out, code);
		}
}

