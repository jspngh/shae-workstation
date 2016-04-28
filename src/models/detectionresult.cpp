#include "detectionresult.h"





DetectionResult::DetectionResult(QGeoCoordinate location, double score)
{
    this->location = location;
    this->score = score;
}

DetectionResult::DetectionResult(const DetectionResult &d)
{
    location = d.location;
    score = d.score;
}

DetectionResult::~DetectionResult()
{

}

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
