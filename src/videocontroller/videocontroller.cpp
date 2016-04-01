#include "videocontroller.h"

VideoController::VideoController(QObject *parent): QObject(parent)
{

}

VideoSequence VideoController::onStartStream(QString streamPath)
{
    const char *vlc_args[] = { "--sout=file/ps:dependencies/drone_stream.mpg" };
    // Launch VLC
    inst = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    /* Create a new item */
    qDebug(streamPath.toStdString().c_str());
    if (streamPath.contains(QString("rtp://"))) {
        qDebug("started stream from rtp address");
        m = libvlc_media_new_location(inst, streamPath.toStdString().c_str());
    } else {
        qDebug("started stream from sdp file");
        m = libvlc_media_new_path(inst, streamPath.toStdString().c_str());
    }

    /* Create a media player playing environement */
    mp = libvlc_media_player_new_from_media(m);

    /* play the media_player */
    libvlc_media_player_play(mp);
    VideoSequence sequence = VideoSequence(QString("dependencies/drone_stream.mpg"), QUuid::createUuid());
    emit this->streamStarted(sequence);
    return sequence;
}


void VideoController::onStopStream()
{
    /* Stop playing */
    libvlc_media_player_stop(mp);

    /* Free the media_player */
    libvlc_media_player_release(mp);

    libvlc_release(inst);
    emit this->streamStopped();
}
