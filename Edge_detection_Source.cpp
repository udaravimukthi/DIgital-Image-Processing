#include "opencv2/opencv.hpp" 
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


using namespace cv;
using namespace std;

int main(int ardc, char* argv[]) {
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

	int r = img.at<Vec3b>(1, 1)[0];
	int g = img.at<Vec3b>(1, 1)[1];
	int b = img.at<Vec3b>(1, 1)[2];

	cout << "r=" << r << "\ng=" << g << "\nb= " << b << endl;

	//create new window fo gray
	Mat gr(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gr, COLOR_BGR2GRAY);

	Mat output = gr.clone();

	int gx = 0;
	int gy = 0;
	int G = 0;

	//to adjust threshold value from input values
	int T = atoi(argv[2]);

	//sobel operator
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			gx = -1 * gr.at<uchar>(i - 1, j - 1) -2 * gr.at<uchar>(i - 1, j) -1 * gr.at<uchar>(i - 1, j + 1) + 1 * gr.at<uchar>(i + 1, j + 1) + 2 * gr.at<uchar>(i + 1, j) + 1 * gr.at<uchar>(i + 1, j + 1);
			gy = -1 * gr.at<uchar>(i-1, j-1) -2 * gr.at<uchar>(i , j-1 ) -1 * gr.at<uchar>(i + 1, j - 1) + 1 * gr.at<uchar>(i - 1, j + 1) + 2 * gr.at<uchar>(i , j + 1) + 1 * gr.at<uchar>(i + 1, j + 1);
			G = abs(gx) + abs(gy);

			//here adding threshold value as 30
			if (G >= T)
				output.at<uchar>(i, j) = 255;
			else
				output.at<uchar>(i, j) = 0;

		}
	}

	// successive difference operator 
	//for (int i = 0; i < height - 1; i++) {
	//	for (int j = 0; j < width - 1; j++) {
	//		gx = gr.at<uchar>(i, j) - gr.at<uchar>(i, j + 1);
	//		gy = gr.at<uchar>(i, j) - gr.at<uchar>(i + 1, j);
	//		G = abs(gx) + abs(gy);

	//		//here adding threshold value as 30
	//		if (G >= T)
	//			output.at<uchar>(i, j) = 255;
	//		else
	//			output.at<uchar>(i, j) = 0;

	//	}
	//}


	namedWindow("Gray Image"); //creating window for gray image
	imshow("Gray Image", gr);
	namedWindow("Output Image"); //creating window for output image
	imshow("Output Image", output);

	waitKey(0);
	return 0;

}
