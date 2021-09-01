#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	Mat img = imread(argv[1], 1);

	if (!img.data) {
		cout << "Image is not found!" << endl;
		return -1;
	}

	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;
	int ch = img.channels();

	printf("Height: %d\n", height);
	printf("Width: %d\n", width);
	printf("WidthStep: %d\n", widthstep);
	printf("Channels: %d\n", ch);

	img.at<uchar>(10, 10) = 255;

	Mat gray(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat copy(height, width, CV_8UC3, Scalar(0, 0, 0));

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			copy.at<Vec3b>(y, x) = img.at<Vec3b>(y, x);
		}
	}

	int hist[256];

	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	//count one by one pixel for each intensity value
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			hist[(int)gray.at<uchar>(y, x)] = hist[(int)gray.at<uchar>(y, x)] + 1;
		}
	}

	//cout to cmd
	for (int i = 0; i < 256;i++) {
		cout << i << ":" << hist[i] << endl;
	}

	//Create an image to display the histogram
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255));

	//Find the maximum number of pixels from histogram array
	int max = hist[0];

	for (int i = 0; i < 256; i++) {
		if (hist[i] > max) {
			max = hist[i];
		}
	}

	//Normalize the histogram between 0 and histogram height
	for (int i = 0; i < 256; i++) {
		hist[i] = ((double)hist[i] / max) * histImage.rows;
	}

	//Draw the lines of histogram.
	for (int i = 0; i < 256; i++) {
		line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - hist[i]), Scalar(0), 1, 8, 0);
	}

	//Contrast streching for gray image
	Mat new_image = gray.clone();
	int v;
	int output;

	//image
	for (int y = 0;y < height;y++) {
		for (int x = 0; x < width;x++) {
			//input pixel value
			v = (int)gray.at<uchar>(y, x);
			if (v >= 0 && v <= 72) {
				output = int((5 / 72.0) * v);
			}
			else if (v > 72 && v <= 192) {
				output = int((245 / 120.0) * (v - 72) + 5);
			}
			else if (v > 192 && v <= 255) {
				output = int((5 / 63.0) * (v - 192) + 250);
			}
			new_image.at<uchar>(y, x) = (uchar)output;
		}
	}

	namedWindow("Image");
	imshow("Image", img);
	namedWindow("Gray");
	imshow("Gray", gray);
	namedWindow("Copy");
	imshow("Copy", copy);
	namedWindow("HistImg");
	imshow("HistImg", histImage);
	namedWindow("New Image");  // creating contrasting window for gray image 
	imshow("New Image", new_image);
	waitKey(0);
	return 0;
}