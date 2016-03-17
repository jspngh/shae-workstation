#include "videocontroller.h"

VideoController::VideoController(QObject *parent): QObject(parent)
{

}

void VideoController::onStartStream(QUuid drone, QString sdpFile){
    std::cout << "start" << std::endl;

    const char * vlc_args[] = { "--sout=file/ps:footage/drone_stream.mpg" };
    // Launch VLC
    std::cout << "new vlc" << std::endl;

    this->inst = libvlc_new(0, NULL);

    //inst = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);

    /* Create a new item */
    std::cout << "test" << std::endl;

    std::cout << sdpFile.toStdString() << std::endl;
    m = libvlc_media_new_path(inst, sdpFile.toStdString().c_str());

    /* Create a media player playing environement */
    mp = libvlc_media_player_new_from_media (m);

    /* play the media_player */
    libvlc_media_player_play (mp);

    sleep (15); /* Let it play a bit */


    emit this->streamStarted();
}


void VideoController::onStopStream(QUuid drone){
    /* Stop playing */
    libvlc_media_player_stop (mp);

    /* Free the media_player */
    libvlc_media_player_release (mp);

    libvlc_release (inst);
    emit this->streamStopped();


}
