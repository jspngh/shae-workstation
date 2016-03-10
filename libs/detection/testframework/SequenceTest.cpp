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
    // scalefactor different from 1 should only be used in a full frame setting (otherwise the sliding window needs to be adapted)
    float scaleFactor = 1;
    DetectionList detectorResult;
    //open sequence and skip the first frame
    int iterationFrames = sequence->get(CV_CAP_PROP_FRAME_COUNT);
    int GTCounter = 0;
    for (int j = 0; j < iterationFrames; j++) {
        cv::Mat frame,frameResized;
        // in CV 3.0, a frame is asynchronously loaded. Before continuing, it is necessary to check if the frame is
        // already completely loaded.
        while (frame.size().height == 0 && frame.size().width == 0) {
            (*sequence) >> frame;
        }
        //when resizing, dont forget to rescale detections
        cv::resize(frame,frameResized, cv::Size(frame.size().width/scaleFactor,frame.size().height/scaleFactor));
        pair<int, DetectionList> groundTruth = GT[GTCounter];
        if (groundTruth.first == j) {
            if (GTCounter < GT.size() - 1)
                GTCounter++;
            //measure time of detector execution
            clock_t beginTime = clock();
            detectorResult = DM->applyDetector(frameResized);
            clock_t endTime = clock();
            double elapsedSecs = double(endTime - beginTime) / CLOCKS_PER_SEC;
            groundTruth.second.resizeDetections(scaleFactor);

            //draw results in debug mode
            if (debug) {
                std::vector<DetectionList> DL = {groundTruth.second, detectorResult};
                std::vector<cv::Scalar> colour = {cv::Scalar(255, 0, 0), cv::Scalar(0, 0, 255)};
                drawDetectionLists(DL, colour, frameResized, 0);
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

    //variables for test measurements
    float averageTime = 0;
    float averageAccuracy = 0;
    int iterationsSequences = this->filesData.size();
    //iterate over each sequence in the annotated drone footage dataset
    for(int i = 0; i<iterationsSequences; i++){
        double elapsedTime = 0; double elapsedSurface = 0; int truePositives = 0; int falsePositives = 0;
        groundTruths = parseAnnotationFile(this->filesGroundTruth[i]);
        cv::VideoCapture sequence = cv::VideoCapture(this->filesData[i]);

        SequenceTest::testSequence(debug, &elapsedTime, &elapsedSurface, &truePositives,&falsePositives, &sequence, groundTruths,this->detectorManager );
        int actualFrames = groundTruths.size();
        int truths = 0;
        for(int j = 0; j < groundTruths.size(); j++){
            truths += groundTruths[j].second.getSize();
        }
        averageAccuracy+=((float)truePositives)/((float)truths);
        averageTime+=((float)elapsedTime)/((float)(actualFrames));
        std::cout << "Sequence: " << i + 1 << "/" << iterationsSequences << std::endl;
        std::cout << "s/frames: " << ((float) elapsedTime) / ((float) (actualFrames)) << std::endl;
        std::cout << "accuracy: " << ((float)truePositives)/((float)truths) << std::endl;

        }
    std::cout << "-----------------" << std::endl;

    std::cout << "average s/frames overall: " << averageTime/(float)(iterationsSequences) << std::endl;
    std::cout << "average accuracy overall: " << averageAccuracy/(float)(iterationsSequences) << std::endl;



}


