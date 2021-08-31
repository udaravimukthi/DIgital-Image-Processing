#include "opencv2/opencv.hpp" 
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


using namespace cv;
using namespace std;

void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

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

	//for 3x3 kernal
	int size = 3*3;
	int* arr = new int[size]; //using pointer can create an array in cpp
	int index;
	int middle;

	for (int i = 1; i < height - 1; i++) {  //thinking about image height with i(image rows)
		for (int j = 1; j < width - 1; j++) { //image with with j(image columns)
			index = 0; //reset to zero
			for (int g = i - 1; g <= i + 1; g++) {  //kernals height (i, rows )
				for (int h = j - 1; h <= j + 1; h++) { //kernals weight (j, colomns)

					arr[index] = (int)gray.at<uchar>(g, h);
					index++;
				}
			}
			//sorting the array using insertion sort
			insertionSort(arr, size);
			middle = size / 2;
			output.at<uchar>(i, j) = (uchar)arr[middle];
		}
	}

	//output with 5x5 kernal 
	int size1 = 5*5;
	int* arr1 = new int[size1]; //using pointer can create an array in cpp
	int index1;
	int middle1;

	for (int i = 2; i < height - 2; i++) {  //thinking about image height with i(image rows)
		for (int j = 2; j < width - 2; j++) { //image with with j(image columns)
			index1 = 0; //reset to zero
			for (int g = i - 2; g <= i + 2; g++) {  //kernals height (i, rows )
				for (int h = j - 2; h <= j + 2; h++) { //kernals weight (j, colomns)

					arr1[index1] = (int)gray.at<uchar>(g, h);
					index1++;
				}
			}
			//sorting the array using insertion sort
			insertionSort(arr1, size1);
			middle1 = size1 / 2;
			output1.at<uchar>(i, j) = (uchar)arr1[middle1];
		}
	}

	//output with adjustment with kernal size through cmd
	int k = atoi(argv[2]);
	int adj = k / 2; 

	int size2 = k*k ;
	int* arr2 = new int[size2]; //using pointer can create an array in cpp
	int index2;
	int middle2;

	for (int i = adj; i < height - adj; i++) {  //thinking about image height with i(image rows)
		for (int j = adj; j < width - adj; j++) { //image with with j(image columns)
			index2 = 0; //reset to zero
			for (int g = i - adj; g <= i + adj; g++) {  //kernals height (i, rows )
				for (int h = j - adj; h <= j + adj; h++) { //kernals weight (j, colomns)
					//getting of all 9 pixels
					arr2[index2]= (int)gray.at<uchar>(g, h);
					index2++;
				}
			}
			//sorting the array using insertion sort
			insertionSort(arr2, size2);
			middle2 = size2 / 2;
			output2.at<uchar>(i, j) = (uchar)arr2[middle2];
		}
	}
	namedWindow("Gray");
	imshow("Gray", gray);
	namedWindow("Output Image with 3x3 kernal with median");  // creating empty window 1 for for median
	imshow("Output Image with 3x3 kernal with median", output);  // creating empty window 1 for output of mean
	namedWindow("Output Image with 5x5 kernal with median");  // creating empty window 1 for for median
	imshow("Output Image with 5x5 kernal with median", output1);  // creating empty window 1 for output of mean

	namedWindow("Output Image with adjustable kernal with median");  // creating empty window 1 for adjustable kernal
	imshow("Output Image with adjustable kernal with median", output2);

	waitKey(0);
	return 0;

}

