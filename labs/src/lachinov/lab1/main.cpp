#include <opencv2\opencv.hpp>
#include <stdlib.h>

int min(int a, int b)
{
	return a > b ? b : a;
}
int max(int a, int b)
{
	return a > b ? a : b;
}

int error(char *name)
{
	printf("invalid arguments\nTempalte: %s image canny_low_treshold canny_high_treshold blur_coef\n", name);
	return -1;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
		return error(argv[0]);	

	float canny_low_treshold = atof(argv[2]), canny_high_treshold = atof(argv[3]);
	cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR), detectedEdges, distance, integral, blurred;
	float blur_coef = atof(argv[4]);

	if (canny_low_treshold <= 0.0f || canny_high_treshold <= 0.0f || !img.data || blur_coef <= 0.0f || canny_high_treshold < canny_low_treshold)
		return error(argv[0]);

	
	//detect edges
	cv::Canny(img, detectedEdges, canny_low_treshold, canny_high_treshold);
	//revert image color
	cv::subtract(cv::Scalar::all(255), detectedEdges, detectedEdges);
	//transform distances
	cv::distanceTransform(detectedEdges, distance, ::CV_DIST_L2, 3);

	cv::integral(img, integral, CV_32FC3);
	
	blurred = cv::Mat(img.rows, img.cols, CV_8UC3);
	//cv::Mat t;
	//distance.convertTo(t, CV_8UC1, 0.9);
	//kernel is all ones
	//variable size
	for (int i = 0; i < img.cols; ++i)
	{
		for (int j = 0; j < img.rows; ++j)
		{
			int kernelsize = (int)(blur_coef*distance.at<float>(cv::Point(i, j)));
			kernelsize = kernelsize < 1 ? 1 : kernelsize;

			int minx, maxx, miny, maxy;

			cv::Vec3f colr(0.0f, 0.0f, 0.0f);

			minx = max(0, i - kernelsize / 2);
			maxx = min(img.cols-1, i + kernelsize / 2);
			miny = max(0, j - kernelsize / 2);
			maxy = min(img.rows - 1, j + kernelsize / 2);

			//calculate sum
			colr = integral.at<cv::Vec3f>(cv::Point(maxx+1, maxy+1));
			colr += integral.at<cv::Vec3f>(cv::Point(minx, miny));
			colr -= integral.at<cv::Vec3f>(cv::Point(maxx+1, miny));
			colr -= integral.at<cv::Vec3f>(cv::Point(minx, maxy+1));

			//for (int k = minx; k <= maxx; ++k)
			//{
			//	for (int l = miny; l <= maxy; ++l)
			//		colr += img.at<cv::Vec3b>(cv::Point(k, l));
			//}
			colr /= (maxx - minx +1) * (maxy-miny+1);

			blurred.at<cv::Vec3b>(cv::Point(i, j)) = colr;
		}
	}

	cv::imshow("img", img);
	//cv::imshow("blur", bluredImg);
	cv::imshow("edges", detectedEdges);
	//cv::imshow("dist", t);
	cv::imshow("blurred", blurred);
	cv::waitKey(0);

	cv::imwrite("out.bmp", blurred);

	return 0;
}