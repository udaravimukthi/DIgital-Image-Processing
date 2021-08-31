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

	printf("height: %d, Width: %d, Width Step: %d, Channels: %d\n", height, width, widthstep, ch);

	Mat gray(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//Contrast streching for gray image
	Mat new_image = gray.clone();
	int v;
	int output;

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

	//(Histrogram Process) allocate memory for all the intencity values
	int hist[256];

	//initialize "0" to all the array elements
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	//count one by one pixel for each intensity value
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			hist[(int)new_image.at<uchar>(y, x)] = hist[(int)new_image.at<uchar>(y, x)] + 1;
		}
	}

	for (int i = 0; i < 256;i++) {
		cout << i << ":" << hist[i] << endl;
	}

	//create an image to display the histrogram
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	//create histrogram window
	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0));

	//find the maximum number of pixels from histrogram array
	int max = hist[0];
	for (int i = 0; i < 256; i++) {
		if (max < hist[i]) {
			max = hist[i];
		}
	}

	//normalize the histrogram between 0 and histrogram height
	for (int i = 0; i < 256; i++) {
		hist[i] = ((double)hist[i] / max) * histImage.rows; //histImsge
	}

	//draw the lines of histrogram
	for (int i = 0; i < 256; i++) {
		line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - hist[i]), Scalar(255), 1, 8, 0);
	}

	//save the contrasted image
	imwrite("saved_contrasted_image.jpg", new_image);

	//save the histrogram image after contrasting
	imwrite("saved_histrogram_image_after_contrasting.jpg", histImage);

	namedWindow("Image"); //creating window for main image
	imshow("Image", img);
	namedWindow("Gray");  // creating empty window for gray
	imshow("Gray", gray); 
	namedWindow("Histrogram");  // creating histogram window
	imshow("Histrogram", histImage);  
	namedWindow("New Image");  // creating contrasting window for gray image 
	imshow("New Image", new_image);

	waitKey(0);
	return 0;

}
