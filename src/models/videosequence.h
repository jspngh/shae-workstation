#ifndef VIDEOSEQUENCE_H
#define VIDEOSEQUENCE_H
#include <QTime>
#include <QString>
#include <QUuid>


class VideoSequence
{
public:
    VideoSequence();
    VideoSequence(QUuid videoId);
    VideoSequence(QUuid videoId, QTime start, QTime end, int frameCount, QString path);
    void setVariables(QString start, QString end, int frameCount, QString path);
    QTime start;
    QTime end;
    int frameCount;
    QString path;
    QUuid videoId;
};

#endif // VIDEOSEQUENCE_H
