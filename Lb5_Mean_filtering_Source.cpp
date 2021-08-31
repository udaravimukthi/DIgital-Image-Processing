#include "opencv2/opencv.hpp" 
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	Mat img = imread(argv[1], 1);

	//adding this part with when kernal size adjustable through cmd
	if (argc != 3) {
		printf("Enter exeFileName ImageName kernalSize");
		return -1;
	}

	if (!img.data) {
		cout << "Could not find the image!" << endl;
		return -1;
	}

	//height, width increase
	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;
	int ch = img.channels();

	Mat gray(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat output = gray.clone(); ///for image with 3x3 kernal
	Mat output1 = gray.clone(); //for image with 5x5 kernal
	Mat output2 = gray.clone(); // for adjustable kernal size through cmd

	int sum;
	int avg = 0;
	for (int i = 1; i < height - 1; i++) {  //thinking about image height with i(image rows)
		for (int j = 1; j < width - 1; j++) { //image with with j(image columns)
			sum = 0;
			for (int g = i - 1; g <= i + 1; g++) {  //kernals height (i, rows )
				for (int h = j - 1; h <= j + 1; h++) { //kernals weight (j, colomns)

					//getting summation of all 9 pixels
					sum = sum + (int)gray.at<uchar>(g, h);
				}
			}
			//kernal value is 3x3 , divide by 9
			avg = sum / 9;
			output.at<uchar>(i, j) = (uchar)avg;
		}
	}

	//output with 5x5 kernal (1 becomes 2, 9 becomes 25)
	int sum1;
	int avg1 = 0;
	for (int i = 2; i < height - 2; i++) {  //thinking about image height with i(image rows)
		for (int j = 2; j < width - 2; j++) { //image with with j(image columns)
			sum1 = 0;
			for (int g = i - 2; g <= i + 2; g++) {  //kernals height (i, rows )
				for (int h = j - 2; h <= j + 2; h++) { //kernals weight (j, colomns)

					//getting summation of all 9 pixels
					sum1 = sum1 + (int)gray.at<uchar>(g, h);
				}
			}
			//kernal value is 3x3 , divide by 9
			avg1 = sum1 / 25;
			output1.at<uchar>(i, j) = (uchar)avg1;
		}
	}

	//output with adjustment with kernal size through cmd
	int k = atoi(argv[2]);
	int adj = k / 2; 

	int sum2;
	int avg2 = 0;
	for (int i = adj; i < height - adj; i++) {  //thinking about image height with i(image rows)
		for (int j = adj; j < width - adj; j++) { //image with with j(image columns)
			sum2 = 0;
			for (int g = i - adj; g <= i + adj; g++) {  //kernals height (i, rows )
				for (int h = j - adj; h <= j + adj; h++) { //kernals weight (j, colomns)

					//getting summation of all 9 pixels
					sum2 = sum2 + (int)gray.at<uchar>(g, h);
				}
			}
			//kernal value is 3x3 , divide by 9
			avg2 = sum2 / (k*k) ;
			output2.at<uchar>(i, j) = (uchar)avg2;
		}
	}
	namedWindow("Gray");
	imshow("Gray", gray);
	namedWindow("Output Image with 3x3 kernal");  // creating empty window 1 for for mean
	imshow("Output Image with 3x3 kernal", output);  // creating empty window 1 for output of mean
	namedWindow("Output Image with 5x5 kernal");  // creating empty window 1 for for mean
	imshow("Output Image with 5x5 kernal", output1);  // creating empty window 1 for output of mean

	namedWindow("Output Image with adjustable kernal");  // creating empty window 1 for adjustable kernal
	imshow("Output Image with adjustable kernal", output2);

	waitKey(0);
	return 0;

}

