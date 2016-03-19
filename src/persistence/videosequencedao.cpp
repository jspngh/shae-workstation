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
    query.bindValue(":videoID", sequence.videoId.toString());
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    query.bindValue(":start", sequence.start.toString());
    query.bindValue(":end", sequence.end.toString());
    query.bindValue(":frameCount", sequence.frameCount);
    query.bindValue(":path", sequence.path);
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
    QSqlQuery queryVideoSequence;
    queryVideoSequence.prepare("SELECT start, end, frameCount, path FROM videosequences WHERE videoID = (:videoID)");
    queryVideoSequence.bindValue(":videoID", videoId);
    if(queryVideoSequence.exec())
    {
        if(queryVideoSequence.next())
        {
            sequence = VideoSequence(QUuid(videoId), queryVideoSequence.value(0),
                                               queryVideoSequence.value(1),
                                               queryVideoSequence.value(2),
                                               queryVideoSequence.value(3));
        }
    else
    {
        qDebug() << "setVideoSequence error:  "
                         << query.lastError();
    }
    return sequence;
}
