#ifndef GENERALDAO_H
#define GENERALDAO_H

#include <QtSql>
#include <QGeoCoordinate>

/**
 * \brief The GeneralDAO class is the overlapping class for the other DAOS
 * this class contains overlapping methods.
 * \ingroup Persistence
 */

class GeneralDAO
{
public:
    GeneralDAO();

    /**
     * \brief UncypherPathString: Method for decyphering a path string.
     */
    QList<QGeoCoordinate>* uncypherPathString(QString pathString);
};

#endif // GENERALDAO_H
