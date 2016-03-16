//
// Created by vincent on 25-2-16.
//

#ifndef DETECTION_SLIDINGWINDOW_H
#define DETECTION_SLIDINGWINDOW_H

#include "WindowSelection.h"

/*!
 * Implements the WindowSelection 'interface'
 * This simple approach will slide over the frame from left to right, from top to bottom.
 * The window will increase in size (width, height) by coming to the front.
 * Adjusting the window size is based on the fact that people in the foreground are bigger than
 * people in the back of the frame.
 */

class SlidingWindow : public WindowSelection {

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

    SlidingWindow(int frameHeight, int frameWidth, float horizon, float winHeight0, float winHeight1,
                  float winWidth0, float winWidth1, int stepX, int stepY);
    ~SlidingWindow() {}

    /*!
     * Will set the window that needs to be evaluated next.
     * The function will adjust the parameter nextWin.
     * \param nextWin [out] nextWin contains the top-left (x,y) coordinate of the rect that needs to be evaluated.
     * \return False is there is no next window, True if nextWin has a meaningful value
     */
    bool nextWindow(cv::Rect &nextWin);

    void reset();

private:
    std::vector<cv::Rect> windows; /*!< contains all the windows that need to be evaluated */
    std::vector<cv::Rect>::iterator windowIterator; /*!< points to the window that needs to be evaluated next */
};

#endif //DETECTION_SLIDINGWINDOW_H
