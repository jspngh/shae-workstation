#include "videosequence.h"

VideoSequence::VideoSequence(){

}

VideoSequence::VideoSequence(QUuid videoId)
{
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

QString VideoSequence::getPath()
{
    return path;
}


//hulpfuncties
void VideoSequence::setVariables(QTime start, QTime end, int frameCount, QString path)
{
    this->start = start;
    this->end = end;
    this->frameCount = frameCount;
    this->path = path;
}
