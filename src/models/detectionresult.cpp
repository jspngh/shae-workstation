#include "detectionresult.h"

DetectionResult::DetectionResult(QGeoCoordinate location, double score)
{
    this->location=location;
    this->score=score;
}
