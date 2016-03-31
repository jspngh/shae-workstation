#include "detectioncontroller.h"

using namespace std;

DetectionController::DetectionController(Mediator *mediator, Search *search, double fps, cv::VideoCapture sequence, QObject *parent)
    : QThread(parent)
{
    this->fps = fps;
    this->sequence = sequence;
    this->search = search;
    parseConfiguration();
}

void DetectionController::run()
{
    this->streaming = true;
    // process a sequence
    cv::Mat frame;

    if(this->sequence.isOpened()){

        int numFrames = this->sequence.get(CV_CAP_PROP_FRAME_COUNT);
        int iteratorFrames = 0;
        double fpsOriginal = (double) this->sequence.get(CV_CAP_PROP_FPS);
        // frameHop is the number of frames that need to be skipped to process the sequence at the desired fps
        this->frameHop = fpsOriginal / (double) this->fps;

        do
        {

            //allow for frames to buffer
            QThread::sleep(1);       //check if new frames have arrived
            numFrames = this->sequence.get(CV_CAP_PROP_FRAME_COUNT);
            while(iteratorFrames < numFrames)
            {
                numFrames = this->sequence.get(CV_CAP_PROP_FRAME_COUNT);
                this->sequence.set(CV_CAP_PROP_POS_FRAMES, iteratorFrames);
                this->sequence >> frame;

                iteratorFrames += this->frameHop;
                DetectionList detectionList = this->manager.applyDetector(frame);
                double timeFrame = iteratorFrames*this->fps;
                //TODO Persistence component should be called to retrieve the statusmessage that is closest in time to the time of the frame (timeFrame)
                QGeoCoordinate frameLocation(10,10);
                //TODO the xLUT and yLUT should be derived from the config file present in the Search object.
                vector<pair<double,double>> locations = this->manager.calculatePositions(detectionList, pair<double,double>(frameLocation.longitude(),frameLocation.latitude()),this->xLUT, this->yLUT);
                for(int i = 0; i < detectionList.getSize(); i++){
                    emit this->newDetection(DetectionResult(QGeoCoordinate(locations[i].first,locations[i].second),1));
                    nrDetections++;
                }

            }

        }while(this->streaming);
        emit this->detectionFinished();

    }
}

void DetectionController::setController(Controller *value)
{
    controller = value;
    controller->getMediator()->addSignal(this, (char*) SIGNAL(pathCalculated(Search *)), QString("pathCalculated(Search*)"));
    controller->getMediator()->addSlot(this, (char*) SLOT(onStartSearch(Search *)), QString("startSearch(Search*)"));
}

void DetectionController::streamFinished(){
    this->streaming = false;
}


int DetectionController::getNrDetections(){
    return this->nrDetections;
}

void DetectionController::parseConfiguration(){
    string line;
    int height = this->search->getHeight();
    int gimbalAngle = this->search->getGimbalAngle();
    string path = "dependencies/gopro_" + to_string(height) + "m" + "_" + to_string(gimbalAngle) + "deg.cfg";
    std::size_t location;
    ifstream file(path);
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
        int xLUTsize = atoi(line.substr(location+1).c_str());
        for(int i = 0; i<xLUTsize;i++){
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
        int yLUTsize = atoi(line.substr(location+1).c_str());
        for(int i = 0; i<yLUTsize;i++){
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
