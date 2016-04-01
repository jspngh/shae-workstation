#ifndef DETECTIONRESULT_H
#define DETECTIONRESULT_H
#include <QGeoCoordinate>
#include "models/videosequence.h"


class DetectionResult
{
public:
    //constructors
    DetectionResult();
    DetectionResult(QGeoCoordinate location, double score);
    //getters
    double getScore();
    QGeoCoordinate getLocation();

private:
    QGeoCoordinate location;
    double score;
};

#endif // DETECTIONRESULT_H
