#ifndef DETECTIONRESULT_H
#define DETECTIONRESULT_H
#include <QGeoCoordinate>
#include <QGeoCoordinate>
#include "models/videosequence.h"


class DetectionResult
{
public:
    //constructors
    DetectionResult();
    DetectionResult(QGeoCoordinate coordinate, double score, VideoSequence video);
    //getters
    VideoSequence getVideoSequence();
    double getScore();
    QGeoCoordinate getLocation();

private:
    QGeoCoordinate location;
    double score;
    VideoSequence sequence;

};

#endif // DETECTIONRESULT_H
