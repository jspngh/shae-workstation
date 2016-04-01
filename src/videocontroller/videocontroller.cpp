#include "videocontroller.h"

VideoController::VideoController(QObject *parent): QObject(parent)
{

}


VideoSequence VideoController::onStartStream(Drone *drone)

{
    const char *vlc_args[] = { "--sout=file/ps:dependencies/drone_stream.mpg" };
    // Launch VLC
    inst = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    /* Create a new item */

    if (drone->getStreamPath().contains(QString("rtp://"))) {
        m = libvlc_media_new_location(inst, drone->getStreamPath().toStdString().c_str());
    } else {
        m = libvlc_media_new_path(inst, drone->getStreamPath().toStdString().c_str());

    }

    /* Create a media player playing environement */
    mp = libvlc_media_player_new_from_media(m);

    /* play the media_player */
    libvlc_media_player_play(mp);
    VideoSequence sequence = VideoSequence(QString("dependencies/drone_stream.mpg"), QUuid::createUuid());
    emit this->streamStarted(sequence);
    return sequence;
}



void VideoController::onStopStream(Drone *drone)
{
    /* Stop playing */
    libvlc_media_player_stop(mp);

    /* Free the media_player */
    libvlc_media_player_release(mp);

    libvlc_release(inst);
    emit this->streamStopped();
}
