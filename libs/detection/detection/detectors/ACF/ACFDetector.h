/*
 * ACFDetector.h
 *
 *  Created on: Jan 16, 2015
 *      Author: fds
 */

#ifndef ACFDETECTOR_H_
#define ACFDETECTOR_H_

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>


#include "../../../utils/rapidxml-1.13/rapidxml.hpp"
#include "../../../utils/rapidxml-1.13/rapidxml_print.hpp"

#include "ChannelFeatures.h"

#include "../../DetectionList.h"
#include "../../Detection.h"
#include "../../detectors/Detector.h"

using namespace rapidxml;
/*!
 * \brief The ACFDetector class implements the Detector 'interface'
 * The detector relies on the ACF detector implementation of the 'openframework' to make detections.
 */

class ACFDetector: public Detector
{
public:
	//constructors and destructors
	ACFDetector();
	ACFDetector(std::string modelfile);
	virtual ~ACFDetector();


	//getters
	int getShrinking() const;
	int getHeight() const;
	std::string getName() const;
	std::string getType() const;
	void setType(std::string type);

	//detection specific methods
	/*!
	* \brief The Detect method compares a set of calculated features to the model.
	*/
	std::vector<Detection *> Detect(const ChannelFeatures *features) const;
	/*!
	* \brief The applyDetectorOnWindow method applies the Detector on single window.
	*/
	bool applyDetectorOnWindow(const cv::Mat &Frame) const;
	/*!
	* \brief The applyDetectorOnBand method applies the Detector on single band.
	*/
	DetectionList applyDetectorOnBand(const cv::Mat &Frame) const;

	/*!
	* \brief The applyDetectorOnFrame method applies the Detector on a full frame.
	*/
	DetectionList applyDetectorOnFrame(const cv::Mat &Frame) const;

private:

	void getChild(const ChannelFeatures *features, int &k0, int &k, int c, int r, int s, int channelwidth, int channelheight, int modelwidth, int modelheight) const;
	void setWidth(float w);
	void setHeight(float h);
	void setWidthPad(float w);
	void setHeightPad(float h);
	void ReadModel(std::string modelfile);

	//! holds indeces to follow through a stage evaluation, normally these are the same in every stage since these represent the decision stump tree
	std::vector<std::vector<int> > Child;

	//! holds indeces to follow through a stage evaluation, normally these are the same in every stage since these represent the decision stump tree
	std::vector<std::vector<int> > depth;

	//! holds the indeces of the features to use, no longer used when features are inside the model
	std::vector<std::vector<int> > Fid;

	//! The thresholds that should be reached for each feature
	std::vector<std::vector<float> > Thresholds;

	//! stores the values to be added/subtracted at the end of a stage (dependent on the leaf reached)
	std::vector<std::vector<float> > Values;

	float modelwidth, modelheight;
	float modelwidthpad, modelheightpad;
	int shrinking;
	int ModelDepth;
};

#endif /* ACFDETECTOR_H_ */
