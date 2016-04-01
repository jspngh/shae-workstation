#ifndef GENERALDAO_TEST_H
#define GENERALDAO_TEST_H


#include <QString>
#include "persistence/generaldao.h"

class GeneralDAO_Test
{
public:
    GeneralDAO_Test();
};

class GeneralDAO_Test : public QObject
{
    Q_OBJECT

public:
    GeneralDAO_Test();
    ~GeneralDAO_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    /*! \brief Basic generaldao test
     */
    void testUncypherGeneralDAO();
    void testUncypherEmptyStringGeneralDAO();
};

#endif // GENERALDAO_TEST_H
