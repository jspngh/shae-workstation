//
// Created by lars on 2/25/16.
//

#include "PerformanceTest.h"

PerformanceTest::PerformanceTest(std::string data, std:: string groundTruth, std::string dataExtension, std::string GTExtension, DetectorManager* detectorManager) {
    this->data = data;
    this->groundTruth = groundTruth;
    this->dataExtension = dataExtension;
    this->GTExtension = GTExtension;
    this->detectorManager = detectorManager;

}

PerformanceTest::~PerformanceTest() {
}


/*!
	\brief compare two DetectionLists.
	The accuracy of a DetectionList can be verified by providing a ground truth DetectionList for a given frame.
    The DetectionList result of the detector, for a given frame, is tested by calculating
    the number of true positives and false positives.
    A true positive is expressed as a detection that lies within the detection box of a GT detection, while a false
    positive is defined as the inverse (e.g. not lieing within a detection box of a GT detection).

*/

std::pair<int,int> PerformanceTest::compareDetectionList(DetectionList DL1, DetectionList DL2){
    //DL1 contains GT
    //DL2 contains detectorresults
    //
    int truePositive = 0;
    int falsePositive = 0;
    std::vector<Detection*> list1 = DL1.returnDetections();
    std::vector<Detection*> list2 = DL2.returnDetections();
    for(std::vector<Detection*>::size_type i = 0; i != list2.size(); i++) {

        for(std::vector<Detection*>::size_type j = 0; j != list1.size(); j++) {
            //if the center is within a box of a GT, we count a true positive
            if( (list2[i]->getCenter().x <= list1[j]->getX()+list1[j]->getWidth()) && (list2[i]->getCenter().x >= list1[j]->getX())
                && (list2[i]->getCenter().y <= list1[j]->getY() + list1[j]->getHeight()) && (list2[i]->getCenter().y >= list1[j]->getY())
                && list1[j]->getScore() != 1){
                // A GT detection should only be counted once, which is why,
                // after a succesful detection, the score is set to 1 (initially the score of GT's is 0)
                list1[j]->setScore(1);
                truePositive++;
            }else{
                falsePositive++;
            }
        }
    }

    return std::pair<int,int>(falsePositive,truePositive);


}

