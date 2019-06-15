/* HSV_Parallel - parallel-ize HSV across all 4 cores

	 created 3/1/17 BD

*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Thresh_Parallel : public cv::ParallelLoopBody
{
 public:
 Thresh_Parallel(cv::Mat img, cv::Mat& img_out, cv::Scalar sMin,	cv::Scalar sMax, int diffVal) :
	img_in(img),
		img_out(img_out),
		scalarMin(sMin),
		scalarMax(sMax),
		diff(diffVal)
	{ }

	~Thresh_Parallel() {}

 public:
	void operator()(const cv::Range& range) const ;

 private:
	cv::Mat img_in;
	cv::Mat& img_out;

	cv::Scalar scalarMin;
	cv::Scalar scalarMax;

	int diff;

} ;
