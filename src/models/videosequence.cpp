#include "videosequence.h"

VideoSequence::VideoSequence()
{

}

VideoSequence::VideoSequence(const VideoSequence &d)
{
    start = d.start;
    end = d.end;
    frameCount = d.frameCount;
    path = d.path;
    videoId = d.videoId;
}

VideoSequence::~VideoSequence()
{

}

VideoSequence::VideoSequence(QUuid videoId)
{
    this->videoId = videoId;
}

VideoSequence::VideoSequence(QString path, QUuid videoId)
{
    this->path = path;
    this->videoId = videoId;
}

VideoSequence::VideoSequence(QUuid videoId, QTime start, QTime end, int frameCount, QString path)
{
    this->videoId = videoId;
    this->start = start;
    this->end = end;
    this->frameCount = frameCount;
    this->path = path;
}

//getters
QUuid VideoSequence::getVideoID()
{
    return videoId;
}

QTime VideoSequence::getStart()
{
    return start;
}

QTime VideoSequence::getEnd()
{
    return end;
}

int VideoSequence::getFrameCount()
{
    return frameCount;
}

QString VideoSequence::getPath() const
{
    return path;
}

void VideoSequence::setPath(const QString &value)
{
    path = value;
}
