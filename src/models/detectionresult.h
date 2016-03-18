#ifndef DETECTIONRESULT_H
#define DETECTIONRESULT_H
#include <QGeoCoordinate>
#include <QGeoCoordinate>
#include "models/videosequence.h"


class DetectionResult
{
public:
    DetectionResult();

private:
    QGeoCoordinate location;
    double score;
    VideoSequence sequence;

};

#endif // DETECTIONRESULT_H
