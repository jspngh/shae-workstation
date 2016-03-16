//
// Created by vincent on 1-3-16.
//

#include "SlidingWindow.h"

// For comments regarding the params and methods, see the header file.

SlidingWindow::SlidingWindow(int frameHeight, int frameWidth, float horizon, float winHeight0, float winHeight1,
                             float winWidth0, float winWidth1, int stepX, int stepY)
	: WindowSelection(frameHeight, frameWidth, horizon, winHeight0, winHeight1, winWidth0, winWidth1, stepX, stepY)
{

	// numWindsHeight: the number of horizontal steps: will change dynamically depending on the width of the window
	int numWindsWidth;
	// numWindsHeight: the number of vertical steps
	int numWindsHeight = (int) ceil((frameHeight - winHeight1 - horizon) / stepY) + 1;
	// the ratio with which the window height will grow in each step
	float ricoHeight = (winHeight1 - winHeight0) / (numWindsHeight - 1);
	// he ratio with which the window width will grow in each step
	float ricoWidth = (winWidth1 - winWidth0) / (numWindsHeight - 1);
	// x and y position of the top left corner of the window
	int x, y;

	for (int i = 0; i < numWindsHeight; i++) {
		// calculate the height and the width of the window. These dimensions stay constant during a horizontal run.
		float height = winHeight0 + ricoHeight * i;
		float width = winWidth0 + ricoWidth * i;
		// calculate the number of window in this horizontal run
		numWindsWidth = (int) ceil((frameWidth - width) / stepX) + 1;
		// the y position of every window in a horizontal run is equal and can be calculated upfront.
		y = horizon + i * stepY;

		for (int j = 0; j < numWindsWidth; j++) {
			x = j * stepX;
			// note: the min functions are necessary for the window at the end and bottom of the frame
			this->windows.push_back(cv::Rect(x, y, fmin(width, frameWidth - x - 1), fmin(height, frameHeight - y - 1)));
		}
	}

	// set the iterator to the beginning of the vector
	this->windowIterator = this->windows.begin();
}

bool SlidingWindow::nextWindow(cv::Rect &win)
{

	if (this->windowIterator == this->windows.end())
		return false;

	win = *this->windowIterator;
	this->windowIterator++;
	return true;

}

void SlidingWindow::reset()
{
	this->windowIterator = this->windows.begin();
}
