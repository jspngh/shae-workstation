#include "Detection.h"

Detection::Detection()
{}

Detection::Detection(float x, float y, float width, float height, float score)
{
	this->setX(x);
	this->setY(y);
	this->setWidth(width);
	this->setHeight(height);
	this->setScore(score);
}

Detection::Detection(float x, float y, float width, float height, float score, std::string name)
{
	this->setX(x);
	this->setY(y);
	this->setWidth(width);
	this->setHeight(height);
	this->setScore(score);
	this->setModelName(name);
	this->setDetectorName(name);
}

Detection::Detection(const Detection &D)
{
	this->x = D.getX();
	this->y = D.getY();
	this->width = D.getWidth();
	this->height = D.getHeight();
	this->filename = D.getFilename();
	this->color = D.getColor();
	this->modelName = D.getModelName();
	this->level = D.getLevel();
	this->score = D.getScore();
	this->detectorname = D.getDetectorName();
}


Detection::Detection(Detection *D)
{
	this->setX(D->getX());
	this->setY(D->getY());
	this->setWidth(D->getWidth());
	this->setHeight(D->getHeight());
	this->setScore(D->getScore());
	this->setColor(D->getColor());
	this->setDetectorName(D->getDetectorName());
}

float Detection::getX() const
{
	return this->x;
}
float Detection::getY() const
{
	return this->y;
}
float Detection::getWidth() const
{
	return this->width;
}
float Detection::getHeight() const
{
	return this->height;
}
float Detection::getScore() const
{
	return this->score;
}
std::string Detection::getFilename() const
{
	return this->filename;
}
cv::Scalar Detection::getColor() const
{
	return this->color;
}
std::string Detection::getModelName() const
{
	return this->modelName;
}
int Detection::getLevel() const
{
	return this->level;
}
void Detection::setX(float x)
{
	this->x = x;
}
void Detection::setY(float y)
{
	this->y = y;
}
void Detection::setWidth(float width)
{
	this->width = width;
}
void Detection::setHeight(float height)
{
	this->height = height;
}
void Detection::setScore(float score)
{
	this->score = score;
}
void Detection::setFilename(std::string filename)
{
	this->filename = filename;
}

void Detection::setColor(cv::Scalar color)
{
	this->color = color;
}
void Detection::setModelName(std::string modelname)
{
	this->modelName = modelname;
}

void Detection::setDetectorName(std::string d)
{
	this->detectorname = d;
}

std::string Detection::getDetectorName() const
{
	return this->detectorname;
}

cv::Point Detection::getCenter()
{
	return cv::Point(this->getX() + this->getWidth() / 2, this->getY() + this->getHeight() / 2);
}

void Detection::resize(float factor)
{
	this->setX(this->x / factor);
	this->setY(this->y / factor);
	this->setWidth(this->width / factor);
	this->setHeight(this->height / factor);
}

