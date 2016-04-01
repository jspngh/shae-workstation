#ifndef SEARCHDAO_H
#define SEARCHDAO_H

#include "models/search.h"
#include <QtSql>
#include "generaldao.h"

/**
 * \brief The SearchDAO class is responsible for loading and saving
 * search models into the database.
 */

class SearchDAO : GeneralDAO
{
public:
    /**
     * \brief The basic constructor for a SearchDAO needs a database as input.
     */
    SearchDAO();
    SearchDAO(QSqlDatabase *projectShaeDatabase);
    /**
     * \brief dbSaveSearch saves a detection result into the database.
     * Its inputs are a search object.
     * The object is the one that needs to be stored.
     */
    Search dbSaveSearch(Search search);
    /**
     * \brief dbRetrieveSearch Retrieves a search for a
     * certain searchid.
     */
    Search dbRetrieveSearch(QUuid searchId);
private:
    QSqlDatabase *projectShaeDatabase;
};

#endif // SEARCHDAO_H
