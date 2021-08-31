#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	Mat img = imread(argv[1], IMREAD_GRAYSCALE);

	if (!img.data) {
		cout << "Image is not found!" << endl;
		return -1;
	}

	int histogram[256];
	int N = img.rows * img.cols;
	double probability[256];
	double cum_prob[256];
	int cNew[256];
	int equalhistogram[256];

	for (int x = 0; x < 256; x++) {
		histogram[x] = 0;
		probability[x] = 0.0;
		cum_prob[x] = 0.0;
		cNew[x] = 0;
		equalhistogram[x] = 0;
	}

	// Calculate number of pixels in each gray levels

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			histogram[(int)img.at<uchar>(i, j)] = histogram[(int)img.at<uchar>(i, j)] + 1;
		}
	}

	// Calculate the probability of each intensity

	for (int i = 0; i < 256; i++) {
		probability[i] = (double)histogram[i] / N;
	}

	// Generate cumulative probability

	double cum = 0.0;

	for (int i = 0; i < 256; i++) {
		cum = cum + probability[i];
		cum_prob[i] = cum;
	}

	//Scale cumulative probability

	for (int i = 0; i < 256; i++) {
		cNew[i] = cvRound(cum_prob[i] * 255);
	}

	// Create a copy of the gray image

	Mat copy = img.clone();


	// Generate the equalized image

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			copy.at<uchar>(i, j) = cNew[img.at<uchar>(i, j)];
		}
	}

	// Draw histograms
	// Calculate number of pixels in each gray levels for equalize image
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			equalhistogram[(int)copy.at<uchar>(i, j)] = equalhistogram[(int)copy.at<uchar>(i, j)] + 1;
		}
	}

	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255));
	Mat equalhistImage(hist_h, hist_w, CV_8UC1, Scalar(255));

	//Draw image histogram
	//Find the maximum number of pixels from histogram array
	int max = histogram[0];

	for (int i = 0; i < 256; i++) {
		if (histogram[i] > max) {
			max = histogram[i];
		}
	}

	//Normalize the histogram between 0 and histogram height
	for (int i = 0; i < 256; i++) {
		histogram[i] = ((double)histogram[i] / max) * histImage.rows;
	}

	//Draw the lines of histogram.
	for (int i = 0; i < 256; i++) {
		line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - histogram[i]), Scalar(0), 1, 8, 0);
	}


	//Draw equalize image histogram
	//Find the maximum number of pixels from histogram array
	int equalmax = equalhistogram[0];

	for (int i = 0; i < 256; i++) {
		if (equalhistogram[i] > equalmax) {
			equalmax = equalhistogram[i];
		}
	}

	//Normalize the histogram between 0 and histogram height
	for (int i = 0; i < 256; i++) {
		equalhistogram[i] = ((double)equalhistogram[i] / equalmax) * equalhistImage.rows;
	}

	//Draw the lines of histogram.
	for (int i = 0; i < 256; i++) {
		line(equalhistImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - equalhistogram[i]), Scalar(0), 1, 8, 0);
	}

	namedWindow("Image");
	imshow("Image", img);
	namedWindow("Copy");
	imshow("Copy", copy);
	namedWindow("Histogram");
	imshow("Histogram", histImage);
	namedWindow("Equal Histogram");
	imshow("Equal Histogram", equalhistImage);
	waitKey(0);
	return 0;
}