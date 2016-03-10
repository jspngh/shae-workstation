//
// Created by lars on 2/25/16.
//

#include "SequenceTest.h"

SequenceTest::SequenceTest(std::string data, std:: string groundTruth, std::string dataExtension,
                           std::string GTExtension, DetectorManager* detectorManager):
        PerformanceTest(data,groundTruth,dataExtension,GTExtension,detectorManager) {

}


/*!
	\brief test performance of a detector on the drone footage dataset.
	The accuracy of a detector is measured by calculating the number of false and true positives.

*/



void SequenceTest::testSequence(bool debug, double* elapsedTime, double* elapsedSurface, int* truePositives, int* falsePositives,
                  cv::VideoCapture* sequence, vector<pair<int, DetectionList>> GT, DetectorManager* DM) {
    *elapsedTime = 0;
    *falsePositives = 0;
    *truePositives = 0;
    *elapsedSurface = 0;
    DetectionList detectorResult;
    //open sequence
    int iterationFrames = sequence->get(CV_CAP_PROP_FRAME_COUNT);
    int GTCounter = 0;
    for (int j = 0; j < iterationFrames; j++) {
        cv::Mat frame;
        // in CV 3.0, a frame is asynchronously loaded. Before continuing, it is necessary to check if the frame is
        // already completely loaded.
        while (frame.size().height == 0 && frame.size().width == 0)
            (*sequence) >> frame;
        pair<int, DetectionList> groundTruth = GT[GTCounter];
        if (groundTruth.first == j) {
            if (GTCounter < GT.size() - 1)
                GTCounter++;
            //measure time of detector execution
            clock_t beginTime = clock();
            detectorResult = DM->applyDetector(frame);
            NonMaximumSuppression NMS;
            detectorResult = NMS.dollarNMS(detectorResult);
            clock_t endTime = clock();
            double elapsedSecs = double(endTime - beginTime) / CLOCKS_PER_SEC;

            //draw results in debug mode
            if (debug) {

                std::vector<DetectionList> DL = {groundTruth.second, detectorResult};
                std::vector<cv::Scalar> colour = {cv::Scalar(255, 0, 0), cv::Scalar(0, 0, 255)};
                drawDetectionLists(DL, colour, frame, 0);
            }

            //update variables for test measurements
            *elapsedTime += elapsedSecs;
            *elapsedSurface += frame.size().height * frame.size().width;
            pair<int, int> results = PerformanceTest::compareDetectionList(groundTruth.second, detectorResult);
            *falsePositives += results.first;
            *truePositives += results.second;
        }
    }
}

void SequenceTest::test(bool debug) {
//open the local directory to search for files
    this->filesData = listFiles(this->data, this->dataExtension);
    this->filesGroundTruth = listFiles(this->groundTruth, this->GTExtension);

    //initialize DetectionLists for GT and detectorResults
    vector<pair<int, DetectionList>> groundTruths;
    pair<int, DetectionList> groundTruth;

    //variables for test measurements

    int iterationsSequences = this->filesData.size();
    //iterate over each sequence in the annotated drone footage dataset
    for(int i = 0; i<iterationsSequences; i++){
        double elapsedTime = 0; double elapsedSurface = 0; int truePositives = 0; int falsePositives = 0;
        groundTruths = parseAnnotationFile(this->filesGroundTruth[i]);
        cv::VideoCapture sequence = cv::VideoCapture(this->filesData[i]);
        cv::Mat frame;
        // in CV 3.0, a frame is asynchronously loaded. Before continuing, it is necessary to check if the frame is
        // already completely loaded.
        while (frame.size().height == 0 && frame.size().width == 0)
            (sequence) >> frame;
        SequenceTest::testSequence(debug, &elapsedTime, &elapsedSurface, &truePositives,&falsePositives, &sequence, groundTruths,this->detectorManager );
        std::cout << "Sequence: " << i+1 << "/" << iterationsSequences << std::endl;
        std::cout << "time (s): " << ((float)elapsedTime) << std::endl;
        std::cout << "surface (pixels): " << ((float)elapsedSurface) << std::endl;
        std::cout << "true positives: " << truePositives << std::endl;
        std::cout << "false positives: " << falsePositives << std::endl;
        }



}



