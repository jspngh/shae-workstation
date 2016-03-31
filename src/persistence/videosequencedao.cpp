#include "videosequencedao.h"


VideoSequenceDAO::VideoSequenceDAO()
{

}

VideoSequenceDAO::VideoSequenceDAO(QSqlDatabase* projectShaeDatabase){
    this->projectShaeDatabase = projectShaeDatabase;
}

VideoSequence VideoSequenceDAO::dbSaveVideoSequence(QUuid droneId, QUuid searchId, VideoSequence sequence)
{
    // todo check if args are ok
    QSqlQuery query;
    query.prepare("INSERT INTO videosequences (videoID, searchID, droneID, start, end, frameCount, path) "
                  "VALUES (:videoID, :searchID, :droneID, :start, :end, :frameCount, :path)");
    query.bindValue(":videoID", sequence.getVideoID());
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    query.bindValue(":start", sequence.getStart());
    query.bindValue(":end", sequence.getEnd());
    query.bindValue(":frameCount", sequence.getFrameCount());
    query.bindValue(":path", sequence.getPath());
    if(query.exec())
    {
       qDebug() << "insert succes";
    }
    else
    {
       qDebug() << "addDetectionResult error:  "
                << query.lastError();
    }
    return sequence;
}

VideoSequence VideoSequenceDAO::dbRetrieveVideoSequence(QUuid droneId, QUuid searchId, QUuid videoId)
{
    VideoSequence sequence;
    QSqlQuery query;
    query.prepare("SELECT start, end, frameCount, path FROM videosequences WHERE videoID = (:videoID)");
    query.bindValue(":videoID", videoId);
    if(query.exec())
    {
        if(query.next())
        {
            sequence = VideoSequence(videoId, query.value(0).toTime(),
                                                    query.value(1).toTime(),
                                                    query.value(2).toInt(),
                                                    query.value(3).toString());
        }
    }
    else
    {
        qDebug() << "setVideoSequence error:  "
                         << query.lastError();
    }
    return sequence;
}
