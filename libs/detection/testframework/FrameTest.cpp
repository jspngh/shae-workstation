//
// Created by lars on 2/25/16.
//

#include "FrameTest.h"


FrameTest::FrameTest(std::string data, std:: string groundTruth, std::string dataExtension, std::string GTExtension,
                     DetectorManager* detectorManager):
        PerformanceTest(data,groundTruth,dataExtension,GTExtension,detectorManager) {

}


/*!
	\brief test performance of a detector on the INRIA dataset.
	FrameTests are performed on the INRIA dataset. As the accuracy on the INRIA dataset is non relevant, this test procedure
    is only used for measuring the throughput of the detector.
    The throughput of a detector is measured by calculating the average number of pixel per time instance .


*/

void FrameTest::test(bool debug) {
    //open the local directory to search for files
    this->filesData = listFiles(this->data, this->dataExtension);
    this->filesGroundTruth = listFiles(this->groundTruth, this->GTExtension);

    //initialize DetectionLists for GT and detectorResults
    DetectionList detectorResult;
    DetectionList groundTruth;

    //variables for test measurements
    double elapsedTime = 0;
    double surfacePixels = 0;
    int iterations = this->filesData.size();
    //iterate over each image in the INRIA dataset
    for(int i = 0; i<iterations; i++){
        //parse GT
        groundTruth = parseINRIA(this->filesGroundTruth[i]);

        //read the image
        cv::Mat frame = cv::imread(this->filesData[i]);

        //measure time of detector execution
        clock_t beginTime = clock();
        detectorResult = this->detectorManager->applyDetector(frame);
        NonMaximumSuppression NMS;
        detectorResult = NMS.dollarNMS(detectorResult);
        clock_t endTime = clock();
        double elapsedSecs = double(endTime - beginTime) / CLOCKS_PER_SEC;


        //draw results in debug mode
        if(debug){
            std::vector<DetectionList> DL = {groundTruth,detectorResult};
            std::vector<cv::Scalar> colour = {cv::Scalar(255,0,0),cv::Scalar(0,0,255)};
            drawDetectionLists(DL, colour, frame, 0);
        }

        //update variables for test measurements
        elapsedTime += elapsedSecs;
        surfacePixels+= frame.size().height*frame.size().width;
        std::cout << "Iteration: " << i << "/" << iterations << std::endl;

    }
    std::cout << "Average time (s): " << ((float)elapsedTime/iterations) << std::endl;
    std::cout << "Average surface (pixels): " << ((float)surfacePixels/iterations) << std::endl;
}

