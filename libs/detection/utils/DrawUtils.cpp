//
// Created by lars on 3/1/16.
//
#include "DrawUtils.h"

/*! \brief utility functions to display images

*/

/*!
	\brief draw multiple DetectionLists on an image, in the corresponding set of colours.
	This is a draw function to display detections from different DetectionLists, whereas detection from the same list
    are displayed in the same colour.

*/
void drawDetectionLists(std::vector<DetectionList> L1, std::vector<cv::Scalar> colour, cv::Mat frame, int waitKeyEvent){
    if(L1.size()==colour.size()){
        for(int i = 0; i<L1.size(); i++){
            for(int j=0; j<L1[i].getSize();j++)
                L1[i].returnDetections()[j]->setColor(colour[i]);
            L1[i].draw(frame);

        }
        cv::imshow("Frame", frame);
        cv::waitKey(waitKeyEvent);
    }
}

void drawRectOnFrame(const cv::Mat &frame, const cv::Rect &rect, const int color, int waitKeyEvent){
    cv::Mat matCopy = frame.clone();
    cv::Scalar col;
    switch(color){
        case COLOR_WHITE:
            col = cv::Scalar(255, 255, 255);
            break;
        case COLOR_RED:
            col = cv::Scalar(255, 255, 255);
            break;
        case COLOR_GREEN:
            col = cv::Scalar(255, 255, 255);
            break;
        case COLOR_BLUE:
            col = cv::Scalar(255, 255, 255);
            break;
    }
    cv::rectangle(matCopy, rect, col, 1);
    cv::imshow("frame", matCopy);
    cv::waitKey(waitKeyEvent);
}
