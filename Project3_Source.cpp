#include "opencv2/opencv.hpp" 
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


using namespace cv;
using namespace std;

int main(int ardc, char* argv[]){
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


	//creating empty window 1
	Mat gray(height, width, CV_8UC1, Scalar(0));

	//try to asssign orignal into gray window, we can get gray image
	cvtColor(img, gray, COLOR_BGR2GRAY);  

	Mat new_image = gray.clone();

	int v;
	int output;

	for (int y = 0;y < height;y++) {
		for (int x = 0; x < width;x++) {
			//input pixel value
			v = (int)gray.at<uchar>(y, x);
			if (v >= 0 && v <= 71) {
				output = int((5 / 71) * v);
			}
			else if (v > 71 && v <= 227) {
				output = int((245 / 156) * (v - 71) + 5);
			}
			else if (v > 227 && v <= 255) {
				output = int((5 / 28) * (v - 227) + 250);
			}
			new_image.at<uchar>(y, x) = (uchar)output ;
		}
	}
	namedWindow("Image");
	imshow("Image", img);
	namedWindow("Gray");  // creating empty window 1 for gray
	imshow("Gray", gray);  // creating empty window 1 for gray

	namedWindow("New Image");  // creating empty window  with 3 channels
	imshow("New Image", new_image);

	waitKey(0);
	return 0;

}

