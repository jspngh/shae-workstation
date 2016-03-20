#ifndef VIDEOSEQUENCE_H
#define VIDEOSEQUENCE_H
#include <QTime>
#include <QString>
#include <QUuid>


class VideoSequence
{
public:
    VideoSequence(QString path, QUuid videoId);
private:
    QString path;
    QUuid videoId;
};

#endif // VIDEOSEQUENCE_H
