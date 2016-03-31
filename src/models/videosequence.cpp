#include "videosequence.h"

VideoSequence::VideoSequence(QString path, QUuid videoId)
{
    this->path = path;
    this->videoId = videoId;
}

QString VideoSequence::getPath() const
{
    return path;
}

void VideoSequence::setPath(const QString &value)
{
    path = value;
}
