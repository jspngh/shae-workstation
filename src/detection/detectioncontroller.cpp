#include "detectioncontroller.h"

using namespace std;

DetectionController::DetectionController(Search *search, QString path, QObject *parent)
    : QThread(parent)
{
    this->search = search;
    this->path = path;
    parseConfiguration(this->search->getHeight(), this->search->getGimbalAngle());
}

void DetectionController::run()
{
    // this->sequence.isOpened() should not be used, since this does not work together with vlc writing to the file.

    // setup variables required for processing
    this->streaming = true;
    double fpsOriginal = (double) this->sequence.get(CV_CAP_PROP_FPS);
    int numFrames = this->sequence.get(CV_CAP_PROP_FRAME_COUNT);
    int oldnumFrames = 0;
    int iteratorFrames = 0;
    // frameHop is the number of frames that need to be skipped to process the sequence at the desired fps
    this->frameHop = fpsOriginal / (double) this->search->getFpsProcessing();
    qDebug() << "original number of frames " << numFrames;
    cv::Mat frame;
    do {

        while (iteratorFrames < numFrames) {
            this->sequence.set(CV_CAP_PROP_POS_FRAMES, iteratorFrames);
            this->sequence >> frame;
            double timeFrame = iteratorFrames * this->search->getFpsProcessing();

            extractDetectionsFromFrame(frame,timeFrame);
            iteratorFrames += this->frameHop;
        }

        qDebug() << "frames need to buffer, old total " << numFrames;
        //allow for frames to buffer
        QThread::sleep(1);
        //check if new frames have arrived
        this->sequence = cv::VideoCapture(path.toStdString());
        oldnumFrames = numFrames;
        numFrames = this->sequence.get(CV_CAP_PROP_FRAME_COUNT);
        qDebug() << "new frames have been found, new total " << numFrames;

    } while (this->streaming || (oldnumFrames!=numFrames));
    qDebug() << "Processing is finished at " << iteratorFrames;

    if(this->sequence.isOpened()){
        this->sequence.release();
    }
    emit this->detectionFinished();


}

void DetectionController::setMediator(Mediator *mediator)
{
    this->mediator = mediator;;
    mediator->addSignal(this, (char *) SIGNAL(newDetection(DetectionResult)), QString("newDetection(DetectionResult))"));
    mediator->addSlot(this, (char *) SIGNAL(detectionFinished()), QString("detectionFinished()"));
}

void DetectionController::streamFinished()
{
    qDebug() << "DetectionController: stream has been stopped";
    this->streaming = false;
}


int DetectionController::getNrDetections()
{
    return this->nrDetections;
}

cv::VideoCapture DetectionController::getSequence() const
{
    return sequence;
}

void DetectionController::setSequence(const cv::VideoCapture &value)
{
    sequence = value;
}


void DetectionController::extractDetectionsFromFrame(cv::Mat frame, double timeFrame){
    if(frame.rows != 0 && frame.cols != 0){
        //TODO Persistence component should be called to retrieve the statusmessage that is closest in time to the time of the frame (timeFrame)
        QGeoCoordinate frameLocation(10, 10);
        double orientation = 1;
        DetectionList detectionList = this->manager.applyDetector(frame);
        vector<pair<double, double>> locations = this->manager.calculatePositions(detectionList, pair<double, double>(frameLocation.longitude(), frameLocation.latitude()), this->xLUT, this->yLUT, orientation);
        for (int i = 0; i < detectionList.getSize(); i++) {
            emit this->newDetection(DetectionResult(QGeoCoordinate(locations[i].first, locations[i].second), 1));
            nrDetections++;
        }

    }else{
        qDebug() << "Frame is empty";
    }
}


void DetectionController::parseConfiguration(int height, int gimbalAngle)
{
    string line;
    string path = "dependencies/gopro_" + to_string(height) + "m" + "_" + to_string(gimbalAngle) + "deg.cfg";
    std::size_t location;
    ifstream file;
    file.open(path);
    //if the file does not exist, fall back to the original configuration
    //might result in faulty detections
    if(!file.is_open())
    {
       path = "dependencies/gopro_3m_65deg.cfg";
       file.open(path);
    }
    if (file.is_open()) {
        //first seven lines are currently not used
        //TODO: parse first seven lines for checks
        getline(file, line);
        getline(file, line);
        getline(file, line);
        getline(file, line);
        getline(file, line);
        getline(file, line);
        getline(file, line);
        getline(file, line);
        //next lines are used for the xLUT and yLUT
        location = line.find_last_of("=");
        int xLUTsize = atoi(line.substr(location + 1).c_str());
        for (int i = 0; i < xLUTsize; i++) {
            getline(file, line);
            char firstComma, secondComma, leftBrace, rightBrace;
            int pixelWidth, realWidth, pixelY;
            istringstream iss(line);
            iss >> leftBrace  >> pixelY >> firstComma >> pixelWidth >> secondComma  >> realWidth >> rightBrace;
            vector<double> temp;
            temp.push_back(pixelY);
            temp.push_back(pixelWidth);
            temp.push_back(realWidth);
            this->xLUT.push_back(temp);
        }
        getline(file, line);
        location = line.find_last_of("=");
        int yLUTsize = atoi(line.substr(location + 1).c_str());
        for (int i = 0; i < yLUTsize; i++) {
            getline(file, line);
            char comma, leftBrace, rightBrace;
            int pixelY, realY;
            istringstream iss(line);
            iss >> leftBrace  >> pixelY >> comma >> realY >> rightBrace;
            vector<double> temp;
            temp.push_back(pixelY);
            temp.push_back(realY);
            this->yLUT.push_back(temp);
        }

    }
}

