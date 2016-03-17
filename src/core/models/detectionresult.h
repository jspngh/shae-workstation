#ifndef DETECTIONRESULT_H
#define DETECTIONRESULT_H
#include <QGeoCoordinate>
#include <QGeoCoordinate>
#include "core/models/videosequence.h"


class DetectionResult
{
public:
    DetectionResult();
    QGeoCoordinate location;
    double score;
    VideoSequence sequence;

};

#endif // DETECTIONRESULT_H
