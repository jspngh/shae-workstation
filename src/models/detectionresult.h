#ifndef DETECTIONRESULT_H
#define DETECTIONRESULT_H
#include <QGeoCoordinate>
#include "models/videosequence.h"


class DetectionResult
{
public:
    //constructors
    DetectionResult();
    DetectionResult(const DetectionResult &d);
    ~DetectionResult();

    DetectionResult(QGeoCoordinate location, double score);
    //getters
    double getScore();
    QGeoCoordinate getLocation();

private:
    QGeoCoordinate location;
    double score;
};

Q_DECLARE_METATYPE(DetectionResult)

#endif // DETECTIONRESULT_H
