// smoothing_ch1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <string>
#include <windows.h>

using namespace cv;

std::string windowname = "example";

int g_slider_pos = 0;
int g_run = 1, g_dontset = 0;
VideoCapture g_cap;

void onTrackbarSlide(int pos, void *) {

	g_cap.set(CAP_PROP_POS_FRAMES, pos);

	if (!g_dontset) {
		g_run = 1;
	}
	g_dontset = 0;
}

int main(int argc, char** argv)
{
	namedWindow(windowname, WINDOW_KEEPRATIO);
	g_cap.open(std::string(argv[1]));
	int frames = (int)g_cap.get(CAP_PROP_FRAME_COUNT);
	int tmpw = (int)g_cap.get(CAP_PROP_FRAME_WIDTH);
	int tmph = (int)g_cap.get(CAP_PROP_FRAME_HEIGHT);
	std::cout << "Video has " << frames << " frames if dimenstion (" << tmpw << "," << tmph << ")." << std::endl;

	createTrackbar("Position", windowname, &g_slider_pos, frames, onTrackbarSlide);

	Mat frame;
	for (;;) {

		if (g_run != 0)
		{
			g_cap >> frame;
			if (frame.empty()) break;

			int curpos = (int)g_cap.get(CAP_PROP_POS_FRAMES);

			imshow(windowname, frame);

			g_run -= 1;
		}

		char c = (char)waitKey(10);

		if (c == 's')
		{
			g_run = 1; std::cout << "Single step, run = " << g_run << std::endl;
		}
		if (c == 'r') {
			g_run = -1; std::cout << "Run module, run = " << g_run << std::endl; 
		}
		if (c == 27) break;
	}

    return 0;
}

