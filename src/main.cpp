#include <QApplication>
#include <QDebug>

#include "core/controller.h"
#include "mainwindow.h"
#include "pathlogic/geopolygon.h"
#include "pathlogic/polygonpathalgorithm.h"



#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    qRegisterMetaType<DetectionResult>("DetectionResult");
    qRegisterMetaType<VideoSequence>("VideoSequence");
    qRegisterMetaType<Search>("Search");
    qRegisterMetaType<DroneStatus>("DroneStatus");
    qRegisterMetaType<Drone>("Drone");

    MainWindow w;
    w.show();

    Controller controller(&w);
    controller.init();


    return a.exec();*/
    libvlc_media_player_t *mp;
    libvlc_instance_t *inst;
    libvlc_media_t *m;

    const char *vlc_args[] = { "--sout=file/ps:drone_stream.mpg" };
    // Launch VLC
    inst = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    /* Create a new item */
    int bufferSize = 0;
    m = libvlc_media_new_location(inst, "rtp://127.0.0.1:5000");
    bufferSize = 8*1024*1024;

    /* Create a media player playing environement */
    mp = libvlc_media_player_new_from_media(m);

    /* play the media_player */
    libvlc_media_player_play(mp);
    //allow vlc some time to create the file
    QThread::sleep(1);
    int size = 0;
    //buffer maximally 60 seconds
    int maxBuffertime = 60;
    int buffertime = 0;
    QFile droneFile("drone_stream.mpg");
    if (droneFile.open(QIODevice::ReadOnly)){
        size = droneFile.size();  //when file does open.
        while(size<bufferSize && buffertime<maxBuffertime){
            buffertime++;
            QThread::sleep(1);
            size = droneFile.size();  //when file does open.
            qDebug() << "Videocontroller: File has not been fully buffered by vlc yet, " << size;
        }
        droneFile.close();
    }
    qDebug() << "Videocontroller: File has been created by vlc.";
    qDebug() << "Videocontroller: File has a size of " << size;
    cv::VideoCapture cap;

    cap.open("drone_stream.mpg");
    while(!cap.isOpened()){
        usleep(1000);
        cout << "stream not opened yet";}


    cv::Mat frame;
    cout << "done opening";
    while(1)
    {
        bool captured =  cap.read(frame);
        if(!captured){
           cout << "no data in the frame";}
        else{
        cout << "data in the frame";
        cv::imshow("Video", frame);
        cv::waitKey(0);
        }

    }

}

