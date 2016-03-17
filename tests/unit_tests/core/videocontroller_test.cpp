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

    QObject::connect( &this->vc, &VideoController::streamStarted,
                     this, &VideoController_Test::onStreamStarted);

    QObject::connect( &this->vc, &VideoController::streamStopped,
                     this, &VideoController_Test::onStreamStopped);


}

void VideoController_Test::testCreateFile()
{
    bool fileExists = false;
    QUuid id;
    emit this->startStream(id, QString("test.sdp"));
    sleep(5);
    emit this->stopStream(id);
    if (FILE *file = fopen("footage/drone_stream.mpg", "r"))
    {
        fileExists = true;
    }
    QVERIFY(fileExists&&this->started &&this->stopped);
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



