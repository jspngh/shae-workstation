#include "videocontroller.h"

VideoController::VideoController(QObject *parent): QObject(parent)
{

}

void VideoController::onStartStream(QUuid drone, QString sdpFile){
    const char * vlc_args[] = { "--sout=file/ps:dependencies/drone_stream.mpg" };
    // Launch VLC
    this->inst = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);

    /* Create a new item */

    m = libvlc_media_new_path(inst, sdpFile.toStdString().c_str());

    /* Create a media player playing environement */
    mp = libvlc_media_player_new_from_media (m);

    /* play the media_player */
    libvlc_media_player_play (mp);


    emit this->streamStarted(VideoSequence(QString("dependencies/drone_stream.mpg"),QUuid::createUuid()));
}


void VideoController::onStopStream(QUuid drone){
    /* Stop playing */
    libvlc_media_player_stop (mp);

    /* Free the media_player */
    libvlc_media_player_release (mp);

    libvlc_release (inst);
    emit this->streamStopped();
}
