#ifndef XMLWRITER_TEST_H
#define XMLWRITER_TEST_H

#include <QObject>
#include <iostream>
#include <QDebug>
#include <QtTest>
#include <string>
#include <QThread>
#include <QtSql>
#include <persistence/persistence.h>

#include "persistence/detectionresultdao.h"

class XMLWriter_Test : public QObject
{
    Q_OBJECT

public:
    XMLWriter_Test();
    ~XMLWriter_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    /*! \brief Basic detectionresultwriter test
     */
    void testSimpleDetectionResultXMLWriter();
    void testSimpleDetectionResultTXTWriter();
};


#endif // XMLWRITER_TEST_H
