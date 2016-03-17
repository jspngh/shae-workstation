#ifndef VIDEOSEQUENCE_H
#define VIDEOSEQUENCE_H
#include <QTime>
#include <QString>
#include <QUuid>


class VideoSequence
{
public:
    VideoSequence();
    QTime start;
    QTime end;
    int frameCount;
    QString path;
    QUuid videoId;
};

#endif // VIDEOSEQUENCE_H
