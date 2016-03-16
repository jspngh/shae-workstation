#include "DetectionList.h"

DetectionList::DetectionList() {

}

DetectionList::DetectionList(const DetectionList& DL ) {
    detections.clear();
    for(int d=0; d<DL.getSize(); d++) {
        this->addDetection(DL.detections[d]->getX(),
                           DL.detections[d]->getY(),
                           DL.detections[d]->getWidth(),
                           DL.detections[d]->getHeight(),
                           DL.detections[d]->getScore());
    }
}

DetectionList::~DetectionList() {
    for(int d=0; d<this->detections.size(); d++) {
        delete detections[d];
    }
}

void DetectionList::addDetection(float x,float y, float width, float height) {
    this->addDetection(x, y, width, height, 1);
}

void DetectionList::addDetection(float x,float y, float width, float height, float score, cv::Scalar C) {
    Detection *D = new Detection(x, y, width, height, score);
    D->setColor(C);
    this->detections.push_back(D);
}

void DetectionList::addDetection(float x, float y, float width, float height,float score) {
    Detection *D = new Detection(x, y, width, height, score);
    D->setColor(cv::Scalar(255,0,0));
    this->detections.push_back(D);
}


void DetectionList::addDetection(float x, float y, float w, float h,float score, std::string name) {
    Detection *D = new Detection(x,y,w,h,score,name);

    D->setColor(cv::Scalar(255,0,0));
    this->detections.push_back(D);
}

void DetectionList::draw(cv::Mat &frame) {
    float topX, topY, bottomX, bottomY;
    for(int d=0; d < detections.size(); d++) {
        topX = detections[d]->getX();
        topY = detections[d]->getY();
        bottomX = detections[d]->getX() + detections[d]->getWidth();
        bottomY = detections[d]->getY() + detections[d]->getHeight();
        cv::rectangle(frame, cv::Point(topX, topY), cv::Point(bottomX, bottomY), detections[d]->getColor(), 3);
    }
}

void DetectionList::resizeDetections(float scale) {
    for(int d=0; d<this->detections.size(); d++) {
        detections[d]->resize(scale);
    }
}

DetectionList& DetectionList::operator=(const DetectionList &DL) {
    this->detections.clear();
    for(int d=0; d<DL.getSize(); d++) {
        this->addDetection(DL.detections[d]->getX(), DL.detections[d]->getY(), DL.detections[d]->getWidth(), DL.detections[d]->getHeight(), DL.detections[d]->getScore());
    }
    return *this;
}

void DetectionList::PrintList() const {
    for(int d=0; d < detections.size(); d++) {
        std::cout << "Score: " << detections[d]->getScore() << std::endl;
    }
}

std::vector<Detection*> DetectionList::returnDetections(){
   return detections;
}


