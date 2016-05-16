#include "DetectorManager.h"


DetectorManager::DetectorManager(int fps,
                                 int processWidth,
                                 int processHeight,
                                 int resolutionWidth,
                                 int resolutionHeight,
                                 std::string path)
{
    std::string acfFile = path + "acf.xml";
    this->detector = new ACFDetector(acfFile);
    // this->detector = new HOGDetector();
    // TODO: remove hardcoding of values
    this->windowSelection = new SlidingWindow(processHeight, processWidth, 190, 100, 300, 50, 150, 20, 20);
    this->fps = fps;
    this->processWidth = processWidth;
    this->processHeight = processHeight;
    this->resolutionWidth = resolutionWidth;
    this->resolutionHeight = resolutionHeight;
    std::string videoFile = path + "drone_stream.avi";
    this->videoDetection = cv::VideoWriter(videoFile,
                                           CV_FOURCC('M', 'J', 'P', 'G'),
                                           this->fps,
                                           cv::Size(processWidth, processHeight),
                                           true);
}

DetectorManager::DetectorManager(Detector *det, WindowSelection *wndSel, int fps)
{
    this->detector = det;
    this->windowSelection = wndSel;
    this->fps = fps;
}

DetectorManager::~DetectorManager()
{
    delete this->detector;
    delete this->windowSelection;
}

string DetectorManager::getDetectorType()
{
    return this->detector->getType();
}

void DetectorManager::setDetector(Detector *detector)
{
    this->detector = detector;
}

void DetectorManager::setWindowSelection(WindowSelection *windowSelection)
{
    this->windowSelection = windowSelection;
}

DetectionList DetectorManager::process(std::string seq)
{
    DetectionList detections;
    FrameFromVideo producer(seq, this->fps);
    cv::Mat frame;

    while (producer.frameAvailable()) {
        frame = producer.giveFrame();
        detections = this->applyDetector(frame);
    }

    return detections;
}

DetectionList DetectorManager::applyDetector(cv::Mat &frame)
{
    DetectionList detections;
    NonMaximumSuppression NMS;
    if (this->detector->getType().compare("frame") == 0) {
        detections =  this->detector->applyDetectorOnFrame(frame);
        // use standardNMS as dollarNMS fails on the given detectionList from ACF
        if (detections.getSize() > 0)
            detections = NMS.standardNMS(detections, 0.2);
        detections.draw(frame);
        this->videoDetection.write(frame);
    }
    return detections;
}

//based on the location from which the frame is taken, the positions of the detections in the frame can be derived.
//location contains the geocoordinate of the frame
//dl contains the detections associated with the frame
//xLUT and yLUT contain lookuptables required to map the pixel locations in the frame on a geocoordinate
std::vector<std::pair<double, double>> DetectorManager::calculatePositions(DetectionList dl,
                                    std::pair<double, double> location,
                                    std::vector<vector<double>> xLUT,
                                    std::vector<vector<double>> yLUT,
                                    double orientation)
{
    vector<std::pair<double, double>> result;
    for (int i = 0; i < dl.getSize(); i++) {
        Detection D = dl.returnDetections()[i];
        std::pair<double, double> distance = derivePositionFromLUT(D, xLUT, yLUT);
        distance =  std::pair<double, double>(cos(abs(orientation)) * distance.first - sin(abs(orientation)) * distance.second, sin(abs(orientation)) * distance.first + cos(abs(orientation)) * distance.second);
        //scale the score based on the relative distance
        D.setScore(D.getScore()*yLUT[0][1] / distance.second);
        // distance contains an x,y distance pair,
        // that can be used to calculate a the coordinate of the detection, based on the coordinate of the frame.
        std::pair<double, double> temp1 = changeLatitude(location, distance.first);
        std::pair<double, double> temp2 = changeLongitude(location, distance.second);
        // save the location of the detection
        result.push_back(std::pair<double, double>(temp1.first, temp2.second));
    }
    return result;
}

/*
the yLUT contains vectors of doubles. each vector in an yLUT contains as a first number the distance in pixel value
and as a second number the distance in meters (vertical distance with respect to the origin of the frame)
the xLUT contains vectors of doubles. the first number of an xLUT vector contains the y position in pixel value,
the second number contains a distance in pixel value, and the final number contains the corresponding distance in meters.
positions are derivde from the LUT based on linear interpolation
    1. determine the yLUT vector with a pixelvalue that lies closest, but above the y pixelvalue of the detection.
    2. interpolate the vertical distance based on the 2 closest yLUT vectors.
    3. use the y pixelvalue of the detection to determine the xLUT vector.
    4. interpolate the horizontal distance based on the xLUT vector.
    origin is top left corner for a detection,
    while LUT uses bottom left corner
*/
std::pair<double, double> DetectorManager::derivePositionFromLUT(Detection d,
        std::vector<vector<double>> xLUT,
        std::vector<vector<double>> yLUT)
{
    double xPixel = (double)(d.getX());
    double yPixel = (double)(this->processHeight - (d.getY() + d.getHeight()));
    double xLoc = 0.0;
    double yLoc = 0.0;

    for (int i = 0; i < yLUT.size(); i++) {
        if (yPixel <= yLUT[i][0]) {
            if (i == 0) {
                yLoc = yLUT[i][1];
            } else {
                // use linear interpolation
                yLoc = (yLUT[i - 1][1]) * ((yLUT[i][0] - yPixel) / (yLUT[i][0] - yLUT[i - 1][0])) + yLUT[i][1] * ((yPixel - yLUT[i - 1][0]) / (yLUT[i][0] - yLUT[i - 1][0]));
            }
            break;
        }
    }
    for (int i = 0; i < xLUT.size(); i++) {
        if (yPixel <= xLUT[i][0]) {
            if (i == 0) {
                xLoc = ((xPixel - this->resolutionWidth / 2) / xLUT[0][1]) * xLUT[0][2] / 2;
            } else {
                xLoc = (((xPixel - this->resolutionWidth / 2) / xLUT[i][1]) * xLUT[i][2] / 2) * ((xLUT[i][0] - yPixel) / (xLUT[i][0] - xLUT[i - 1][0])) + (((xPixel - this->resolutionWidth / 2) / xLUT[i - 1][1]) * xLUT[i - 1][2] / 2) * ((yPixel - xLUT[i - 1][0]) / (xLUT[i][0] - xLUT[i - 1][0]));
            }
            break;
        }
    }
    return std::pair<double, double>(xLoc, yLoc);
}
