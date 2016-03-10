//
// Created by lars on 3/5/16.
//
#include "TestFramework.h"

void executeAccuracyTest(Detector* D, std::string type){
    //change slidingwindow as well, when resolution of footage is changed
    std::string data =  "../footage/local/drone footage/video/720p";
    std:: string groundTruth =  "../footage/local/drone footage/annotations";
    std::string dataExtension = "mp4";
    std::string GTExtension = "ann";
    WindowSelection *sliding;
    if(type.compare("frame")==0) {
        D->setType(type);
        sliding = new SlidingWindow(720, 1280, 190, 100, 300, 1280, 1280, 20, 20);
    }
    if(type.compare("band")==0){
        D->setType(type);
        sliding = new SlidingWindow(720, 1280, 190, 100, 300, 1280, 1280, 20, 20);
    }
    if(type.compare("window")==0){
        D->setType(type);
        sliding = new SlidingWindow(720, 1280, 190, 100, 300, 50, 150, 20, 20);
    }
    DetectorManager* detectorManager = new DetectorManager(D,sliding);
    SequenceTest* sequenceTest = new SequenceTest(data, groundTruth, dataExtension, GTExtension, detectorManager);
    sequenceTest->test(true);
    delete sliding;


}


void executePerformanceTest(Detector* D, std::string type){
    std::string data =  "../footage/local/INRIA/images";
    std:: string groundTruth =  "../footage/local/INRIA/annotations";
    std::string dataExtension = "png";
    std::string GTExtension = "txt";    WindowSelection *sliding;
    if(type.compare("frame")==0) {
        D->setType(type);
        sliding = new SlidingWindow(720, 1280, 190, 100, 300, 1280, 1280, 20, 20);
    }
    if(type.compare("band")==0){
        D->setType(type);
        sliding = new SlidingWindow(720, 1280, 190, 100, 300, 1280, 1280, 20, 20);
    }
    if(type.compare("window")==0){
        D->setType(type);
        sliding = new SlidingWindow(720, 1280, 190, 100, 300, 50, 150, 20, 20);
    }
    DetectorManager* detectorManager = new DetectorManager(D, sliding);

    FrameTest* frameTest = new FrameTest(data, groundTruth, dataExtension, GTExtension, detectorManager);
    frameTest->test(false);
    delete sliding;


}
