/* Thresh_Parallel - parallel-ize Threshold operation across all 4 cores

	 created 3/2/17 BD

*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Thresh_Parallel.h"

void Thresh_Parallel::operator()(const cv::Range& range) const
{
	for (int i = range.start; i < range.end; i++)
		{
			// get the stripe that we're working on
			cv::Mat in(img_in,
								 cv::Rect(0, (img_in.rows/diff)*i, 
													img_in.cols, img_in.rows/diff));
			cv::Mat out(img_out, cv::Rect(0, (img_out.rows/diff)*i, 
																		img_out.cols, img_out.rows/diff));

			// and now, perform the function
			cv::inRange(in, scalarMin, scalarMax, out);
		}
}

