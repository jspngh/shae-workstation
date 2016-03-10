//
// Created by lars on 3/5/16.
//

#ifndef DETECTION_TESTFRAMEWORK_H
#define DETECTION_TESTFRAMEWORK_H
#include "SequenceTest.h"
#include "FrameTest.h"


void executeAccuracyTest(Detector* D, std::string type);
void executePerformanceTest(Detector* D, std::string type);


#endif //DETECTION_TESTFRAMEWORK_H
