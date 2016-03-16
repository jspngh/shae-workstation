//============================================================================
// Author      : F. De Smedt @ EAVISE
// Copyright   : This code is written for the publication of  "Open Framework for Combined Pedestrian detection". This code is for research and educational purposes only. For a different license, please contact the contributors directly. More information about the license can be fount in license.txt
//============================================================================


#ifndef DETECTION_FRAMEFROMVIDEO_H
#define DETECTION_FRAMEFROMVIDEO_H

#include "FrameProducer.h"

class FrameFromVideo: public FrameProducer
{
public:
	FrameFromVideo(std::string directory);
	virtual ~FrameFromVideo();

	cv::Mat giveFrame();
	bool isend();

	std::string getFilename()
	{
		return "video";
	}
private:
	cv::VideoCapture cap;
};

#endif /* DETECTION_FRAMEFROMVIDEO_H */
