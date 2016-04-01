#include "detectionresult.h"

double DetectionResult::getScore()
{
    return score;
}

QGeoCoordinate DetectionResult::getLocation()
{
    return location;
}

DetectionResult::DetectionResult()
{
    this->location = QGeoCoordinate(0, 0);
    this->score = 0;
}


DetectionResult::DetectionResult(QGeoCoordinate location, double score)
{
    this->location = location;
    this->score = score;
}
