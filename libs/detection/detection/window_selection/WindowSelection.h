//
// Created by vincent on 25-2-16.
//

#ifndef DETECTION_WINDOWSELECTION_H
#define DETECTION_WINDOWSELECTION_H

#include <opencv2/core/core.hpp>
#include <math.h>
#include <algorithm>

/*!
 * WindowSelection is a base class for every class that return windows which need to be evaluated by the detector.
 */

class WindowSelection
{
public:
	/*!
	 * Constructor of the WindowSelection class
	 * \param frameHeight height of the complete frame
	 * \param frameWidth width of the complete frame
	 * \param horizon The position of the horizon (amount of pixels from the top to the horizon)
	 * \param winHeight0 Height of the first window i.e. the window at the back / horizon
	 * \param winWidth0 Width of the first window i.e. the window at the back / horizon
	 * \param winHeight0 height of the last window i.e. the window at the front of the frame
	 * \param winHeight1 width of the last window i.e. the window at the front of the frame
	 * \param stepX step size to the right of the window
	 * \param stepY step size to the bottom of the window
	 */

	WindowSelection(int frameHeight, int frameWidth, float horizon, float winHeight0, float winHeight1,
	                float winWidth0, float winWidth1, int stepX, int stepY);

	~WindowSelection() {}

	/*!
	 * Will set the window that needs to be evaluated next.
	 * The function will adjust the parameter nextWin.
	 * \param nextWin [out] nextWin contains the top-left (x,y) coordinate of the rect that needs to be evaluated.
	 * \return False is there is no next window, True if nextWin has a meaningful value
	 */
	virtual bool nextWindow(cv::Rect &nextWin) = 0;

	/*!
	 * Reset the window selection. Next window will return the first window on position (x0, y0) with width equal to
	 * winWidth0 and height equal to winHeight0.
	 * Note: this routine needs to be called before looping over a frame.
	 */
	virtual void reset() = 0;

protected:
	int frameHeight, frameWidth; /*!< Height and Width of the frame. */
	int stepX, stepY; /*!< Step size of the window in the x and y direction. */
	float winWidth0, winHeight0; /*!< Width and height of the first window i.e. the window at the back / horizon */
	float winWidth1, winHeight1; /*!< Width and height of the last window i.e. the window at the front of the frame */
	float horizon; /*!< The position of the horizon (amount of pixels from the top to the horizon) */
};

#endif //DETECTION_WINDOWSELECTION_H
