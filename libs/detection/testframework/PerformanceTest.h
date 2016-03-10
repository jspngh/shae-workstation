//
// Created by lars on 2/25/16.
//

#ifndef DETECTION_PERFORMANCETEST_H
#define DETECTION_PERFORMANCETEST_H


#include <tuple>
#include <vector>
#include "../utils/FileUtils.h"
#include "../utils/DrawUtils.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "../detection/DetectorManager.h"
#include "../detection/suppression/NonMaximumSuppression.h"
#include "../detection/window_selection/SlidingWindow.h"



class PerformanceTest {
public:
    PerformanceTest(){}
    PerformanceTest(std::string data, std:: string groundTruth, std::string dataExtension, std::string GTExtension, DetectorManager* detectorManager);
    ~PerformanceTest();
    std::tuple<int,int> test(int treshold);
    static std::pair<int,int> compareDetectionList(DetectionList DL1, DetectionList DL2);

protected:
    std::string data;
    std::string groundTruth;
    std::string dataExtension;
    std::string GTExtension;
    DetectorManager* detectorManager;
};


#endif //DETECTION_PERFORMANCETEST_H
