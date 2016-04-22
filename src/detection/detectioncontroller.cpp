#include "detectioncontroller.h"

using namespace std;

DetectionController::DetectionController(Search *search, DroneModule *dm, PersistenceController *pc, QObject *parent)
    : QThread(parent),
      search(search),
      persistenceController(pc),
      droneModule(dm)
{
    parseConfiguration(this->search->getHeight(), this->search->getGimbalAngle());
    this->streaming = true;
    this->manager = new DetectorManager(this->search->getFpsProcessing(), this->processWidth, this->processHeight);


}

void DetectionController::run()
{
    // this->sequence.isOpened() should not be used, since this does not work together with vlc writing to the file.
    // setup variables required for processing
    this->sequence = cv::VideoCapture(path.toStdString());
    double fpsOriginal = (double) this->sequence.get(CV_CAP_PROP_FPS);
    qDebug() << (double) fpsOriginal;
    int numFrames = this->sequence.get(CV_CAP_PROP_FRAME_COUNT);
    qDebug() << "frames have been found, total " << numFrames;

    int oldnumFrames = 0;
    int iteratorFrames = 0;
    // frameHop is the number of frames that need to be skipped to process the sequence at the desired fps
    this->frameHop = fpsOriginal / (double) this->search->getFpsProcessing();
    qDebug() << "framehop " << frameHop;
    if (!(this->frameHop > 0 && this->frameHop < 30)) {
        this->frameHop = 30;
    }
    droneId = this->droneModule->getGuid();
    QTime sequenceStartTime = this->persistenceController->retrieveVideoSequence(droneId, this->search->getSearchID())->getStart();

    cv::Mat frame;
    do {
        while (iteratorFrames < numFrames) {
            try {
                this->sequence.set(CV_CAP_PROP_POS_FRAMES, iteratorFrames);
                bool captured =  this->sequence.read(frame);
                double timeFrame = (double)iteratorFrames / (double)fpsOriginal;
                if (captured) {
                    QDateTime time = QDateTime::currentDateTime();
                    time.setTime(sequenceStartTime);
                    time = time.addMSecs((quint64) timeFrame * 1000.0);
                    QTime Timer;
                    Timer.start();
                    //TODO: remove hardcoding of resolution
                    cv::Mat croppedFrame = frame(cv::Rect(0,720-this->processHeight,this->processWidth,this->processHeight));
                    extractDetectionsFromFrame(croppedFrame, time);
                    int nMilliseconds = Timer.elapsed();
                    qDebug() << "processed frame " << iteratorFrames << "of " << numFrames << " in " << nMilliseconds;
                }
            } catch (cv::Exception e) {
                qDebug() << "opencv error";
            }
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
    } while (this->streaming || (oldnumFrames != numFrames));
    qDebug() << "Processing is finished at " << iteratorFrames;

    if (this->sequence.isOpened())
        this->sequence.release();
    emit this->detectionFinished();
}

void DetectionController::setMediator(Mediator *mediator)
{
    this->mediator = mediator;
    mediator->addSignal(this, SIGNAL(newDetection(QUuid, DetectionResult*)), QString("newDetection(QUuid, DetectionResult*)"));
    mediator->addSignal(this, SIGNAL(detectionFinished()), QString("detectionFinished()"));
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

void DetectionController::setPath(const QString &value)
{
    path = value;
}

void DetectionController::extractDetectionsFromFrame(cv::Mat frame, QDateTime time)
{
    if(frame.rows != 0 && frame.cols != 0)
    {
        DroneStatus *droneStatus = this->persistenceController->retrieveDroneStatus(droneId, time);
        QGeoCoordinate frameLocation = droneStatus->getCurrentLocation();
        double orientation = droneStatus->getOrientation();
        DetectionList detectionList = this->manager->applyDetector(frame);
        vector<pair<double, double>> locations = this->manager->calculatePositions(detectionList, pair<double, double>(frameLocation.latitude(), frameLocation.longitude()), this->xLUT, this->yLUT, orientation);

        for (int i = 0; i < detectionList.getSize(); i++) {
            emit this->newDetection(droneId, new DetectionResult(QGeoCoordinate(locations[i].first, locations[i].second), detectionList.returnDetections()[i]->getScore()));
            qDebug() << "detection score of " << detectionList.returnDetections()[i]->getScore();
            nrDetections++;
        }

    } else {
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
    if (!file.is_open()) {
        path = "dependencies/gopro_3m_65deg.cfg";
        file.open(path);
    }
    if (file.is_open()) {
        //first seven lines are currently not used
        //TODO: parse first seven lines for checks
        for (int i = 0; i < 7; i++)
         {
            getline(file, line);

             if(i==4)
            {
                location = line.find_last_of("=");
                this->processWidth = std::atoi(line.substr((location+1),line.size()).c_str());
            }
            if(i==5)
            {
                location = line.find_last_of("=");
                this->processHeight = std::atoi(line.substr((location+1),line.size()).c_str());
            }
        }
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

