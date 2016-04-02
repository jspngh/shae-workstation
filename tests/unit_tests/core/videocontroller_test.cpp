#include "videocontroller_test.h"

using namespace std;

VideoController_Test::VideoController_Test(QObject *parent) : QObject(parent)
{
}

void VideoController_Test::initTestCase()
{
    QString program = "python";
    QStringList arguments;
    qDebug() << "opening simulator";
    arguments << "../../../drone/simulator/src/simulator.py";
    simulatorProcess = new QProcess(this);
    qDebug() << "simulator opened";
    simulatorProcess->start(program, arguments);
    QThread::sleep(5);
    streamConnection = new StreamConnection("127.0.0.1", 5502);
    streamConnection->onStreamRequest();
    QThread::sleep(1);

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
    emit this->startStream(drone);
    QThread::sleep(10);
    qDebug("testing if stream was successfully captured");
    emit this->stopStream(drone);
    QFile droneFile("dependencies/drone_stream.mpg");
    if (droneFile.open(QIODevice::ReadOnly)){
        int size = droneFile.size();  //when file does open.
        if(size>10){
            fileExists = true;
        }
        droneFile.close();
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
    streamConnection->stopConnection();
    simulatorProcess->close();
    delete simulatorProcess;
    delete streamConnection;
}



