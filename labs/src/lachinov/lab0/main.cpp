#include <opencv2\opencv.hpp>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR), bluredImg, detectedEdges, distance;
	cv::blur(img, bluredImg, cv::Size(3,3));

	cv::Canny(bluredImg, detectedEdges, atof(argv[2]), atof(argv[3]));

	cv::subtract(cv::Scalar::all(255), detectedEdges, detectedEdges);

	cv::distanceTransform(detectedEdges, distance, ::CV_DIST_L2, 3);
	cv::Mat t;
	distance.convertTo(t, CV_8UC1, 0.9);
	
	cv::imshow("img", img);
	cv::imshow("blur", bluredImg);
	cv::imshow("edges", detectedEdges);
	cv::imshow("dist", t);


	cv::waitKey();

	return 0;
}