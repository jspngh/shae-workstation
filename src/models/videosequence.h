#ifndef VIDEOSEQUENCE_H
#define VIDEOSEQUENCE_H
#include <QTime>
#include <QString>
#include <QUuid>


class VideoSequence
{
public:
    //constructors
    VideoSequence();
    VideoSequence(QUuid videoId);
    VideoSequence(QString path, QUuid videoId);
    VideoSequence(QUuid videoId, QTime start, QTime end, int frameCount, QString path);

    //getters
    QUuid getVideoID();
    QTime getStart();
    QTime getEnd();
    int getFrameCount();
    QString getPath();

    //hulpfuncties
    void setVariables(QTime start, QTime end, int frameCount, QString path);
private:
    QTime start;
    QTime end;
    int frameCount;
    QString path;
    QUuid videoId;
};

#endif // VIDEOSEQUENCE_H
