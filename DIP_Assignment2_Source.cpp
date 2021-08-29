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

	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;
	int ch = img.channels();

	//gray image 
	Mat grayImage(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, grayImage, COLOR_BGR2GRAY);

	//get a copy of the gray image
	//GaussianBlur(grayImage, grayImage, Size(3, 3), 0, 0, BORDER_DEFAULT);
	Mat Laplacian_Output = grayImage.clone();

    //here I used second method
	int Grad = 0; 

	// finding zero crossing
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {

			//here I used second method which gives clear image

			Grad = (-1 * grayImage.at<uchar>(i - 1, j - 1) -1 * grayImage.at<uchar>(i - 1, j) -1 * grayImage.at<uchar>(i - 1, j + 1) -1 
			* grayImage.at<uchar>(i, j - 1) + 8 * grayImage.at<uchar>(i, j) -1 * grayImage.at<uchar>(i, j + 1) -1 *
			grayImage.at<uchar>(i + 1, j - 1) -1 * grayImage.at<uchar>(i + 1, j) -1 * grayImage.at<uchar>(i + 1, j + 1));

			//I tried this also, not clear
			
			//G = -1 * grayImage.at<uchar>(i, j - 1) - 1 * grayImage.at<uchar>(i - 1, j) -1 * grayImage.at<uchar>(i, j + 1) - 1 * grayImage.at<uchar>(i + 1, j) + 4 * grayImage.at<uchar>(i, j);

			if (Grad < 0) {
				Grad = 0;
			}
			else if (Grad> 255) {
				Grad = 255;
			}
			Laplacian_Output.at<uchar>(i, j) = Grad ;
		}
	}

	namedWindow("OriginalImage"); //window for original image
	imshow("OriginalImage", img);

	namedWindow("GrayImage");   // window for gray image
	imshow("GrayImage", grayImage);
	imwrite("Gray_Output.jpg", grayImage);

	namedWindow("Laplacian_Output");  // window for laplacian output
	imshow("Laplacian_Output", Laplacian_Output);
	imwrite("Laplacian_Output.jpg", Laplacian_Output); //get output image as jpg

	waitKey(0);
	return 0;

}