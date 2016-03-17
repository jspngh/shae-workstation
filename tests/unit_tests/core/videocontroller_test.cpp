#include "videocontroller_test.h"

using namespace std;

VideoController_Test::VideoController_Test(QObject *parent) : QObject(parent)
{
}

void VideoController_Test::initTestCase()
{


    QObject::connect(this, &VideoController_Test::startStream,
                     &this->vc, &VideoController::onStartStream);

    QObject::connect(this, &VideoController_Test::stopStream,
                     &this->vc, &VideoController::onStopStream);

    QObject::connect( &this->vc, &VideoController::streamStarted,
                     this, &VideoController_Test::onStreamStarted);


}

void VideoController_Test::testCreateFile()
{
    QUuid id;
    emit this->startStream(id, QString("test.sdp"));
    sleep(15);
    //emit this->stopStream(id);
}

void VideoController_Test::cleanupTestCase()
{

}



