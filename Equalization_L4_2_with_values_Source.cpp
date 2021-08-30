#include "opencv2/opencv.hpp" 
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


using namespace cv;
using namespace std;

int main(int ardc, char* argv[]) {
	Mat img = imread(argv[1], IMREAD_GRAYSCALE);

	if (!img.data) {
		cout << "Could not find the image!" << endl;
		return -1;
	}

	//allocate memory location
	int histrogram[256];
	int equalhistrogram[256];
	int cNew[256];

	//probability of each intensity
	double prob[256];
	double cprob[256];

	//intialized gray level values to 0
	for (int x = 0; x < 256; x++) {
		cNew[x] = 0;
		histrogram[x] = 0;
		equalhistrogram[x] = 0;

		prob[x] = 0.0;
		cprob[x] = 0.0;
	}

	//calcualte no of pixels for each gray levels of original image
	for (int i = 0;i < img.rows;i++) {
		for (int j = 0;j < img.cols;j++) {
			histrogram[(int)img.at<uchar>(i, j)] = histrogram[(int)img.at<uchar>(i, j)] + 1;
		}
	}

	//total nuomber pixels of the image
	int N = img.rows * img.cols;

	//calculate the probabilty of each gray level
	for (int i = 0; i < 256; i++) {
		prob[i] = (double)histrogram[i] / N;
	}

	//Generate cumulative probabilty
	cprob[0] = prob[0];
	for (int i = 1; i < 256; i++) {
		cprob[i] = cprob[i - 1] + prob[i];
	}

	//print cumulative probabilties
	for (int i = 1; i < 256; i++) {
		printf("%f\n", cprob[i]);
	}

	//scale the cumulative probability
	for (int i = 0;i < 256; i++) {
		cNew[i] = cvRound(cprob[i] * 255);
	}

	//create new image to get equilized by cloning gray image
	Mat copy = img.clone();

	//then again read the pixel by pixel & and scaled culilative values to the image
	int z = 0;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			z = cNew[(int)img.at<uchar>(i, j)];
			copy.at<uchar>(i, j) = (uchar)z;
		}
	}

	//calcualte no of pixels for each gray levels of equalized image
	for (int i = 0;i < img.rows;i++) {
		for (int j = 0;j < img.cols;j++) {
			equalhistrogram[(int)img.at<uchar>(i, j)] = equalhistrogram[(int)img.at<uchar>(i, j)] + 1;
		}
	}

	namedWindow("Image");
	imshow("Image", img);

	namedWindow("Equalized Image");
	imshow("Equalized Image", copy);

	waitKey(0);
	return 0;

}