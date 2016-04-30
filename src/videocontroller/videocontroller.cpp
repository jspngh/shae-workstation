#include "videocontroller.h"

VideoController::VideoController(QObject *parent): QObject(parent)
{
    initSdpFile();
}

QString VideoController::getSequencePath()
{
    return this->sequence_path;
}

void VideoController::setSequencePath(QString sp)
{
    this->sequence_path = sp;
}

void VideoController::setMediator(Mediator *m)
{
    this->mediator = m;
    mediator->addSignal(this, SIGNAL(streamStarted(QUuid, VideoSequence*)), QString("streamStarted(QUuid, VideoSequence*)"));
    mediator->addSignal(this, SIGNAL(streamStopped()), QString("streamStopped()"));
}


VideoSequence* VideoController::onStartStream(Drone *drone)
{

    removeExistingVideoFiles();

    QString params = QString("--sout=file/ps:") + streamMpgLocation();
    const char *vlc_args[] = {  params.toLocal8Bit().data() };

    // Launch VLC
    inst = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);

    /* Create a new item */
    qDebug(drone->getStreamPath().toStdString().c_str());
    int bufferSize = 0;
    if (drone->getStreamPath().contains(QString("rtp"))) {
        qDebug("started stream from rtp address");
        m = libvlc_media_new_location(inst, drone->getStreamPath().toStdString().c_str());
        bufferSize = 8 * 1024 * 1024;
    } else if(drone->getStreamPath().contains(QString("sdp"))) {
        qDebug("started stream from sdp file");
        m = libvlc_media_new_path(inst, streamSdpLocation().toStdString().c_str());
        bufferSize = 2 * 1024 * 1024;
    } else
    {
        qDebug("started stream from video file");
        VideoSequence* sequence =  new VideoSequence(QUuid::createUuid(), QTime::currentTime(), QTime::currentTime(), 0, QString(drone->getStreamPath()));
        this->sequence_path = sequence->getPath();
        QThread::sleep(10);
        emit this->streamStarted(drone->getGuid(), sequence);
        return sequence;
    }

    /* Create a media player playing environement */
    mp = libvlc_media_player_new_from_media(m);

    /* play the media_player */
    QTime startStreamTime = QTime::currentTime();
    libvlc_media_player_play(mp);
    //allow vlc some time to create the file
    QThread::sleep(1);
    int size = 0;
    //buffer maximally 60 seconds
    int maxBuffertime = 60;
    int buffertime = 0;
    QFile droneFile(streamMpgLocation());
    if (droneFile.open(QIODevice::ReadOnly)) {
        size = droneFile.size();  //when file does open.
        while (size < bufferSize && buffertime < maxBuffertime) {
            buffertime++;
            QThread::sleep(1);
            size = droneFile.size();  //when file does open.
            qDebug() << "Videocontroller: File has not been fully buffered by vlc yet, " << size;
        }
        droneFile.close();
    }
    qDebug() << "Videocontroller: File has been created by vlc.";
    qDebug() << "Videocontroller: File has a size of " << size;

    VideoSequence* sequence =  new VideoSequence(QUuid::createUuid(), startStreamTime, startStreamTime, 0, streamMpgLocation());
    this->sequence_path = sequence->getPath();
    emit this->streamStarted(drone->getGuid(), sequence);
    return sequence;
}


void VideoController::onStopStream(Drone *drone)
{

    if(mp != nullptr){
        /* Stop playing */
        libvlc_media_player_stop(mp);

        /* Free the media_player */
        libvlc_media_player_release(mp);
    }

    if(inst != nullptr){
        libvlc_release(inst);

        libvlc_release(inst);
    }

    emit this->streamStopped();
}


QString VideoController::streamMpgLocation()
{
    QString name = "drone_stream.mpg";
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    //create folder if not available
    QDir(QDir::root()).mkpath(folder);

    if (!folder.endsWith(QDir::separator()))
        folder.append(QDir::separator());

    return folder.append(name);
}


QString VideoController::streamAviLocation()
{
    QString name = "drone_stream.avi";
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    //create folder if not available
    QDir(QDir::root()).mkpath(folder);

    if (!folder.endsWith(QDir::separator()))
        folder.append(QDir::separator());

    return folder.append(name);
}

QString VideoController::streamSdpLocation()
{
    QString name = "sololink.sdp";
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    //create folder if not available
    QDir(QDir::root()).mkpath(folder);

    if (!folder.endsWith(QDir::separator()))
        folder.append(QDir::separator());

    return folder.append(name);
}

void VideoController::removeExistingVideoFiles()
{
    QFile mpgFile(streamMpgLocation());
    if (mpgFile.exists())
        mpgFile.remove();

    QFile aviFile(streamAviLocation());
    if (aviFile.exists())
        aviFile.remove();
}

void VideoController::initSdpFile()
{

    QFile sdpResFile(streamSdpLocation());

    // if the file already exists nothing needs to be done anymore
    // in general this function only needs to copy the file once, the first the time the application runs
    if (sdpResFile.exists()) return;


    QFile srcFile(":/video/sololink.sdp");
    srcFile.open(QIODevice::ReadOnly);
    QTextStream in(&srcFile);

    QFile dstFile(streamSdpLocation());
    dstFile.open(QIODevice::WriteOnly);

    QTextStream out(&dstFile);

    out << in.readAll();

    /* Close the files */
    dstFile.close();
    srcFile.close();
}
