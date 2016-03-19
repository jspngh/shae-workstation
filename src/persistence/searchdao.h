#ifndef SEARCHDAO_H
#define SEARCHDAO_H

#include "models/search.h"
#include <QtSql>

class SearchDAO
{
public:
    SearchDAO();
    SearchDAO(QSqlDatabase* projectShaeDatabase);

    Search dbSaveSearch(Search search);
    Search dbRetrieveSearch(QUuid searchId);
private:
    QSqlDatabase* projectShaeDatabase;
};

#endif // SEARCHDAO_H
