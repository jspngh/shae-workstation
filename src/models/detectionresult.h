#ifndef DETECTIONRESULT_H
#define DETECTIONRESULT_H
#include <QGeoCoordinate>
#include <QGeoCoordinate>
#include "models/videosequence.h"


class DetectionResult
{
public:
    DetectionResult();
    DetectionResult(QGeoCoordinate coordinate, double score, VideoSequence video);
    VideoSequence getVideoSequence();
    double getScore();
    QGeoCoordinate getLocation();

private:
    QGeoCoordinate location;
    double score;
    VideoSequence sequence;

};

#endif // DETECTIONRESULT_H
