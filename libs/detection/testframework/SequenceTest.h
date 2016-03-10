//
// Created by lars on 2/25/16.
//

#ifndef DETECTION_SEQUENCETEST_H
#define DETECTION_SEQUENCETEST_H


#include "PerformanceTest.h"


class SequenceTest: public PerformanceTest {
public:
    SequenceTest(): PerformanceTest(){};
    SequenceTest(std::string data, std:: string groundTruth, std::string dataExtension, std::string GTExtension, DetectorManager* detectorManager);
    ~SequenceTest();
    void test(bool debug);
    static void testSequence(bool debug, double* elapsedTime,double* elapsedSurface, int* truePositives, int* falsePositives,
                      cv::VideoCapture* sequence, vector<pair<int, DetectionList>> GT, DetectorManager* DM);
private:
    std::vector<std::string> filesData;
    std::vector<std::string> filesGroundTruth;


};


#endif //DETECTION_SEQUENCETEST_H
