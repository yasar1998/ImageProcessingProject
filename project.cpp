#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace ml;


int main()
{
	VideoCapture capture, background;
	capture.open("C:\\Users\\yasar\\OneDrive\\Desktop\\foreground.mp4");
	background.open("C:\\Users\\yasar\\OneDrive\\Desktop\\Background.mp4");

	if (!capture.isOpened() || !background.isOpened())
	{
		puts("could not find the video file");
		system("pause");
		return -1;
	}

	Mat frame, bg, dest, sm, mask, dest2, dl, er, res;

	int i, j;
	int b, g, r;
	while (capture.read(frame) && background.read(bg))
	{
		resize(bg, dest, frame.size());

		for (i = 0; i < frame.rows; i++)
			for (j = 0; j < frame.cols; j++)
			{
				b = frame.at<Vec3b>(i, j)[0];
				g = frame.at<Vec3b>(i, j)[1];
				r = frame.at<Vec3b>(i, j)[2];
				if (b >= 0 && g <= 180 && r >= 0) {
					dest.at<Vec3b>(i, j)[0] = b;
					dest.at<Vec3b>(i, j)[1] = g;
					dest.at<Vec3b>(i, j)[2] = r;
				}
			}
		imshow("dest", dest);

		GaussianBlur(dest, sm, Size(7, 7), 5.0, 5.0);
		imshow("smoothed", sm);

		inRange(dest, Scalar(0, 0, 0), Scalar(80, 255, 255), dest2);
		imshow("threshed", dest2);
		

		Mat k = getStructuringElement(MORPH_RECT, Size(7, 7));
		erode(dest2, er, k);
		imshow("mask_smaller", er);

		dilate(dest2, dl, k);
		imshow("mask_bigger", dl);
		
		Mat edges = dl - er;
		imshow("edges_mask", edges);

		copyTo(sm, res, edges);
		imshow("last", res);

		char c = waitKey(1);
		if (c == 27)
			break;
	}

	waitKey(0);
	return 0;
}