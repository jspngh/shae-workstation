#ifndef PARSEEXCEPTION_TEST_H
#define PARSEEXCEPTION_TEST_H
#include <QtTest>
#include "communication/parseexception.h"

class ParseException_Test : public QObject
{
    Q_OBJECT

public:
    ParseException_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanUpTestCase();
    void testConstructor();
    void testThrow();

};

#endif // PARSEEXCEPTION_TEST_H
