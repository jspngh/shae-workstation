#include "videosequence.h"

VideoSequence::VideoSequence(QString path, QUuid videoId)
{
    this->path = path;
    this->videoId = videoId;
}
