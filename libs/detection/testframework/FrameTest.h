//
// Created by lars on 2/25/16.
//

#ifndef DETECTION_FRAMETEST_H
#define DETECTION_FRAMETEST_H


#include "PerformanceTest.h"

class FrameTest: public PerformanceTest {
public:
    FrameTest(std::string data, std:: string groundTruth, std::string dataExtension, std::string GTExtension, DetectorManager* detectorManager);
    ~FrameTest();
    void test(bool debug);
private:
    std::vector<std::string> filesData;
    std::vector<std::string> filesGroundTruth;

};



#endif //DETECTION_FRAMETEST_H
