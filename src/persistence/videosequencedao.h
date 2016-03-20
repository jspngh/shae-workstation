#ifndef VIDEOSEQUENCEDAO_H
#define VIDEOSEQUENCEDAO_H

#include <QtSql>
#include "models/videosequence.h"

class VideoSequenceDAO
{
public:
    VideoSequenceDAO();
    VideoSequenceDAO(QSqlDatabase* projectShaeDatabase);
    //
    VideoSequence dbSaveVideoSequence(QUuid droneId, QUuid searchId, VideoSequence sequence);
    VideoSequence dbRetrieveVideoSequence(QUuid droneId, QUuid searchId, QUuid videoId);
private:
    QSqlDatabase* projectShaeDatabase;
};

#endif // VIDEOSEQUENCEDAO_H
