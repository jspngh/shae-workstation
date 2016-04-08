#include "videosequencedao.h"


VideoSequenceDAO::VideoSequenceDAO()
{

}

VideoSequenceDAO::VideoSequenceDAO(QSqlDatabase *projectShaeDatabase)
{
    this->projectShaeDatabase = projectShaeDatabase;
}

VideoSequence VideoSequenceDAO::dbSaveVideoSequence(QUuid droneId, VideoSequence sequence)
{
    // todo check if args are ok
    QSqlQuery query;
    query.prepare("INSERT INTO videosequences (videoID, droneID, start, end, frameCount, path) "
                  "VALUES (:videoID, :droneID, :start, :end, :frameCount, :path)");
    query.bindValue(":videoID", sequence.getVideoID());
    query.bindValue(":droneID", droneId);
    query.bindValue(":start", sequence.getStart());
    query.bindValue(":end", sequence.getEnd());
    query.bindValue(":frameCount", sequence.getFrameCount());
    query.bindValue(":path", sequence.getPath());
    if (query.exec()) {
        qDebug() << "insert succes";
    } else {
        qDebug() << "addDetectionResult error:  "
                 << query.lastError();
    }
    return sequence;
}

VideoSequence VideoSequenceDAO::dbRetrieveVideoSequence(QUuid droneId, QUuid searchId)
{
    VideoSequence sequence;
    QSqlQuery query;
    query.prepare("SELECT videoID, start, end, frameCount, path FROM videosequences WHERE droneID = (:droneID) and searchID =(:searchID)");
    query.bindValue(":droneID", droneId);
    query.bindValue(":searchID", searchId);
    if (query.exec()) {
        if (query.next()) {
            sequence = VideoSequence(query.value(0).toUuid() , query.value(1).toTime(),
                                     query.value(2).toTime(),
                                     query.value(3).toInt(),
                                     query.value(4).toString());
        }
    } else {
        qDebug() << "setVideoSequence error:  "
                 << query.lastError();
    }
    return sequence;
}
