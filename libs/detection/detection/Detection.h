#ifndef DETECTION_H
#define DETECTION_H
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>


/*!
 * Detection is a data class containing information about detections made by the detector in a frame
 * TODO: mechanism to match a detection to a coordinate
 */

class Detection
{
public:
	// constructors
	Detection();
	Detection(float x, float y, float width, float height, float score);
	Detection(float x, float y, float width, float height, float score, std::string name);
	Detection(const Detection &d);
	Detection(Detection *d);

	// getters an setters
	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;
	float getScore() const;
	std::string getFilename() const;
	cv::Scalar getColor() const;
	std::string getModelName() const;
	int getLevel() const;
	void setX(float x) ;
	void setY(float y) ;
	void setWidth(float width) ;
	void setHeight(float height) ;
	void setScore(float score) ;
	void setFilename(std::string filename) ;
	void setColor(cv::Scalar color) ;
	void setModelName(std::string modelname) ;
	void setDetectorName(std::string d);
	std::string getDetectorName() const;

	// utils functions
	cv::Point getCenter();
	void resize(float factor);

private:
	float x;
	float y;
	float width;
	float height;
	float score;
	int level;
	std::string filename;
	cv::Scalar color;
	std::string modelName;
	std::string detectorname;
};

#endif // DETECTION_H
