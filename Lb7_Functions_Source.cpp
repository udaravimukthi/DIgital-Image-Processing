#include "opencv2/opencv.hpp" 
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	Mat img = imread(argv[1], 1);

	if (!img.data) {
		cout << "Could not find the image!" << endl;
		return -1;
	}

	//height, width increase
	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;
	int ch = img.channels();

	//1. Average filter using salt and pepper image using blur function
	Mat avgFilter = img.clone();
	//input image , output image ,kernal size,pointing(not necceary), border
	blur(img, avgFilter, Size(3, 3), Point(-1, -1), 4);

	//2. median filter
	Mat medianFilter = img.clone(); 
	//input imge, output image, kernal size
	medianBlur(img, medianFilter, 3);

	//3. Gaussian filter
	Mat gaussianFilter = img.clone();
	//input image, output image, kernal size, sigmax, sigmay, border
	GaussianBlur(img, gaussianFilter, Size(3, 3), (0,0), 4);

	//4. Binary Thresholding
	Mat bThreshold = img.clone();
	//input, output, double tresh, double maxval, int type
	//here using median filtered image as input image
	threshold(medianFilter, bThreshold, 128, 255, CV_THRESH_BINARY);

	//5. OTSU Threshold
	//Mat oThreshold = img.clone();
	//threshold(medianFilter, oThreshold, 0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU); // Best one

	//6. Addaptive threshold
	//Mat aThreshold = img.clone();
	//adaptiveThreshold(medianFilter, aThreshold, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 11, 2);


	//7. Canny's Edge Detection
	Mat cannyedge = img.clone();
	Canny(medianFilter, cannyedge, 50, 100, 3, false);

	//8. svm-support vector machine
	//Mat con = img.clone();

	//vector<vector<Point>> contours;
	//vector<Vec4i>hierarchy;
	//findContours(bThreshold, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	//drawContours(con, contours, -1, Scalar(0), 2);

	namedWindow("Image");
	imshow("Image", img);
	namedWindow("Average Filter");
	imshow("Average Filter", avgFilter);
	namedWindow("Median Filter");
	imshow("Median Filter", medianFilter);
	namedWindow("Gaussian Filter");
	imshow("Gaussian Filter", gaussianFilter);
	namedWindow("Binary Threshold");
	imshow("Binary Threshold", bThreshold);
	//namedWindow("Otsu Threshold");
	//imshow("Otsu Threshold", oThreshold);
	//namedWindow("Adaptive Threshold");
	//imshow("Adaptive Threshold", aThreshold);
	//namedWindow("find contours");
	//imshow("find contours", bThreshold);
	namedWindow("Canny Edge");
	imshow("Canny Edge", cannyedge);
	//namedWindow("Contours");
	//imshow("Contours", con);

	waitKey(0);
	return 0;

}

