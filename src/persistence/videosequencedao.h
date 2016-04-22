#ifndef VIDEOSEQUENCEDAO_H
#define VIDEOSEQUENCEDAO_H

#include <QtSql>
#include <QTime>
#include "models/videosequence.h"
#include "generaldao.h"

/**
 * \brief The videosequenceDAO class is responsible for loading and saving
 * videosequence models into the database.
 */

class VideoSequenceDAO : GeneralDAO
{
public:
    /**
     * \brief The basic constructor for a VideoSequenceDAO needs a database as input.
     */
    VideoSequenceDAO();
    VideoSequenceDAO(QSqlDatabase *projectShaeDatabase);
    //
    /**
     * \brief dbSaveVideoSequence saves a detection result into the database.
     * Its inputs are a droneid and videosequence object.
     * The id is for referencing to the drone table in the database while the object is
     * the one that needs to be stored.
     */
    VideoSequence* dbSaveVideoSequence(QUuid droneId, QUuid searchId, VideoSequence *sequence);
    /**
     * \brief dbRetrieveVideoSequence Retrieves a videosequence for a
     * certain droneid and searchid.
     */

    VideoSequence* dbRetrieveVideoSequence(QUuid droneId, QUuid searchId);
private:
    QSqlDatabase *projectShaeDatabase;
};

#endif // VIDEOSEQUENCEDAO_H
