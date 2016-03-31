#ifndef DETECTIONRESULT_H
#define DETECTIONRESULT_H
#include <QGeoCoordinate>
#include "models/videosequence.h"


class DetectionResult
{
public:
    DetectionResult();
    DetectionResult(QGeoCoordinate location, double score);
private:
    QGeoCoordinate location;
    double score;
};

#endif // DETECTIONRESULT_H
