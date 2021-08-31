#include "opencv2/opencv.hpp" 
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
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

	printf("height: %d, Width: %d, Width Step: %d, Channels: %d\n" , height, width, widthstep, ch );

	//if use MAT structure BGR image u need to access like this, 3 pixels for each
	Mat B = img.clone();
	B.at<Vec3b>(10, 10)[0] = (255, 0, 255);//blue
	B.at<Vec3b>(10, 10)[1] = (255, 0, 255);//green
	B.at<Vec3b>(10, 10)[2] = (255, 0, 255);//red

	// part of image to be white
	//img.at<uchar>(100, 100) = 255;

	//creating empty window 1
	Mat gray(height, width, CV_8UC1, Scalar(0));

	//try to asssign orignal into gray window, we can get gray image
	cvtColor(img, gray, COLOR_BGR2GRAY);  

	//y=row, x=colomn with new windo with 3 channels
	Mat copy(height, width, CV_8UC3, Scalar(0, 0, 0));

	for (int y = 0; y < height; y++) {
		for (int x = 0;x < width;x++) {
			copy.at<Vec3b>(y, x) = img.at<Vec3b>(y, x);
		}
	}

	//histrogram scene

	//allocatw memory for all the intencity values
	int hist[256];

	//initialize "0" to all the array elements
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}
	
	//count one by one pixel for each intensity value
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			hist[(int)gray.at<uchar>(y, x)] = hist[(int)gray.at<uchar>(y, x)]+ 1;	
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
		hist[i]= ((double)hist[i] / max)* histImage.rows;
	}

	//draw the lines of histrogram
	for (int i = 0; i < 256; i++) {
		line(histImage, Point(bin_w *(i), hist_h), Point(bin_w *(i), hist_h - hist[i]), Scalar(255), 1, 8, 0);
	}
	

	namedWindow("Image");
	imshow("Image", img);
	namedWindow("Gray");  // creating empty window 1 for gray
	imshow("Gray", gray);  // creating empty window 1 for gray

	namedWindow("Copy");  // creating empty window  with 3 channels
	imshow("Copy", copy);  // creating empty window with 3 channels

	namedWindow("B");
	imshow("B", B);

	namedWindow("Histrogram");  // creating histogram window
	imshow("Histrogram", histImage);  // creating histrogram window 

	waitKey(0);
	return 0;

}

