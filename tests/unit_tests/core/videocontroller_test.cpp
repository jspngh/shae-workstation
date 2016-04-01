#include "videocontroller_test.h"

using namespace std;

VideoController_Test::VideoController_Test(QObject *parent) : QObject(parent)
{
}

void VideoController_Test::initTestCase()
{
    this->started = false;
    this->stopped = false;


    QObject::connect(this, &VideoController_Test::startStream,
                     &this->vc, &VideoController::onStartStream);

    QObject::connect(this, &VideoController_Test::stopStream,
                     &this->vc, &VideoController::onStopStream);

    QObject::connect(&this->vc, &VideoController::streamStarted,
                     this, &VideoController_Test::onStreamStarted);

    QObject::connect(&this->vc, &VideoController::streamStopped,
                     this, &VideoController_Test::onStreamStopped);


}

void VideoController_Test::testCreateFile()
{
    bool fileExists = false;
    Drone *drone = new Drone();
    drone->setStreamPath(QString("rtp://127.0.0.1:5000"));
    qDebug("opening the stream");
    emit this->startStream(drone->getStreamPath());
    QThread::sleep(10);
    qDebug("testing if stream was successfully captured");
    emit this->stopStream();
    if (FILE *file = fopen("dependencies/drone_stream.mpg", "r")) {
        std::ifstream in("dependencies/drone_stream.mpg", std::ifstream::ate | std::ifstream::binary);
        std::ifstream::pos_type size = in.tellg();
        if (size > 10) { //header file should not be taken into account
            fileExists = true;
        }
        std::remove("dependencies/drone_stream.mpg"); // delete file
    }

    QVERIFY(fileExists && this->started && this->stopped);
}

void VideoController_Test::onStreamStarted()
{
    this->started = true;
}
void VideoController_Test::onStreamStopped()
{
    this->stopped = true;
}
void VideoController_Test::cleanupTestCase()
{

}



