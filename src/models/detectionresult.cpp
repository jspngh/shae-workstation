#include "detectionresult.h"

DetectionResult::DetectionResult(){

}

DetectionResult::DetectionResult(QGeoCoordinate coordinate, double score, VideoSequence video){
    this->location = coordinate;
    this->score = score;
    this->sequence = video;
}

VideoSequence DetectionResult::getVideoSequence()
{
    return sequence;
}

double DetectionResult::getScore()
{
    return score;
}

QGeoCoordinate DetectionResult::getLocation()
{
    return location;
}
