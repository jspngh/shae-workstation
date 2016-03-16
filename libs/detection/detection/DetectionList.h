#ifndef DETECTIONLIST_H
#define DETECTIONLIST_H

#include <vector>
#include "Detection.h"
#include <string>

/*!
 * \brief DetectionList is a wrapper class around a vector of detection objects.
 * Additionally the class provides extra utilities.
*/

class DetectionList
{
	// Some classes that should have direct access to the detections
	friend class NonMaximumSuppression;
	friend class Combinator;

public:
	DetectionList();
	DetectionList(const DetectionList &DL);
	virtual ~DetectionList();

	// methods for creating an adding a detection to the list
	void addDetection(float x, float y, float width, float height, float score);
	void addDetection(float x, float y, float width, float height);
	void addDetection(float x, float y, float width, float height, float score, std::string name);
	void addDetection(float x, float y, float width, float height, float score, cv::Scalar color);
	int getSize() const { return (int) this->detections.size(); }

	// draw the detections on Frame
	void draw(cv::Mat &Frame);
	// Resize the detections (required when working on an upscaled image)
	void resizeDetections(float scale);
	DetectionList &operator=(const DetectionList &DL);
	void PrintList() const;
	std::vector<Detection *> returnDetections();

private:
	std::vector<Detection *> detections;
};

#endif /* DETECTIONLIST_H */
