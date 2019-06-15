/* HSV_Parallel - parallel-ize HSV across all 4 cores

	 created 3/1/17 BD

*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class HSV_Parallel : public cv::ParallelLoopBody
{
 public:
 HSV_Parallel(cv::Mat img, cv::Mat& img_out, int code, int diffVal) :
	img_in(img),
		img_out(img_out),
		code(code),
		diff(diffVal)
		{ }

	~HSV_Parallel() {}

 public:
	void operator()(const cv::Range& range) const ;

 private:
	cv::Mat img_in;
	cv::Mat& img_out;

	int code;
	int diff;

} ;
