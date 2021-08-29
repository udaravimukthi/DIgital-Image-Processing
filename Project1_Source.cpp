#include "cv.h"
#include "highgui.h"

int main(int ardc, char* argv[]){
	
	IplImage* img;
	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);

	if (!img) {
		printf("Could not load image file %s\n", argv[1]);
		return -1;
	}
	
	int width = img->width;
	int height = img->height;
	int widthstep = img->widthStep;
	int channels = img->nChannels;

	printf("Width: %d\n", width);
	printf("Height: %d\n", height);
	printf("Width step: %d\n", widthstep);
	printf("No of channels: %d\n", channels);

//image datatype
	uchar* data = (uchar*)img->imageData;

	int i = 100; //y axis
	int j = 100;  //x axis

	int b = data[i * widthstep + j * channels];  //take the data from each channel(blue color pixel)
	int g = data[i * widthstep + j * channels + 1];
	int r = data[i * widthstep + j * channels + 2];

	printf("Blue: %d\n", b);
	printf("Green: %d\n", g);
	printf("Red: %d\n", r);

	//to convert in to black all the pixel should be zero
	//(100 * 100 area black)

	for (int a = 0; a <= 100; a++) {
		for (int b = 0; b <= 100; b++) {
			data[a * widthstep + b * channels] = 0;
			data[a * widthstep + b * channels + 1] = 0;
			data[a * widthstep + b * channels + 2] = 0;
		}
	}
	
	//to get a gray image by convertinh
	IplImage* gray = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	uchar* graydata = (uchar*)gray->imageData;
	int grayWS = gray->widthStep;
	int grayCh = gray->nChannels;

	for (int a = 0; a < height; a++) {
		for (int b = 0; b < width; b++) {
			graydata[a * grayWS + b* grayCh] = data[a * widthstep + b * channels] * 0.1140 + data[a * widthstep + b * channels + 1] * 0.5870 + data[a * widthstep + b * channels + 2] * 0.2989;

		}
	}

	//by changing thresold value we can convert image to binary image
	for (int a = 0; a < height; a++) {
		for (int b = 0; b < width; b++) {
			if (graydata[a * grayWS + b * grayCh] > 150)
				graydata[a * grayWS + b * grayCh] = 255; //150 thresdhold value

			else
				graydata[a * grayWS + b * grayCh] = 0;
		}
	}
	 //convert BGR image into negative image (Invert BGR).
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data[i * widthstep + j * channels] = 255 - data[i * widthstep + j * channels];
			data[i * widthstep + j * channels + 1] = 255 - data[i * widthstep + j * channels + 1];
			data[i * widthstep + j * channels +2] = 255 - data[i * widthstep + j * channels +2 ];
		}
	}

	// Split BGR image into 3 channels. (Blue, Green, Red)
	IplImage* blue = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	IplImage* green = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	IplImage* red = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);

	uchar* dataB = (uchar*)blue->imageData;
	uchar* dataG = (uchar*)green->imageData;
	uchar* dataR = (uchar*)red->imageData;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dataB[i * widthstep + j * channels] = data[i * widthstep + j * channels];
			dataB[i * widthstep + j * channels + 1] = 0;
			dataB[i * widthstep + j * channels + 2] = 0;

			dataG[i * widthstep + j * channels] = 0;
			dataG[i * widthstep + j * channels + 1] = data[i * widthstep + j * channels + 1];
			dataG[i * widthstep + j * channels + 2] = 0;

			//only assign red cor and others assign to zeros
			dataR[i * widthstep + j * channels] = 0;  
			dataR[i * widthstep + j * channels + 1] = 0;
			dataR[i * widthstep + j * channels + 2] = data[i * widthstep + j * channels + 2];
		}
	}

	cvNamedWindow("Image");
	cvShowImage("Image", img);
	cvNamedWindow("Gray");   // add new to convert gray image
	cvShowImage("Gray", gray);  // add new to convert gray image

	cvNamedWindow("Blue");   // Load data for channel B
	cvShowImage("Blue", blue);  // Load data for channel B

	cvNamedWindow("Green");   // Load data for channel G
	cvShowImage("Green", green);  // Load data for channel G

	cvNamedWindow("Red");   // Load data for channel R
	cvShowImage("Red", red );  // Load data for channel R
	cvWaitKey(0);
	//cvDestroyWindow("Image");
	//cvReleaseImage(&img);
	//cvDestroyWindow("Gray"); // add new to convert gray image
	//cvReleaseImage(&gray);  // add new to convert gray image7

	cvDestroyAllWindows(); // for run split thing have to destroy all windows
	return 0;


	
	}

