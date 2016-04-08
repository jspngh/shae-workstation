#include "core/system_test.h"
#include <QList>
#include <QTest>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QList<QObject *> tests;
    //tests.append(new VideostreamDetection_Test());
    tests.append(new System_Test());
    foreach (QObject *test, tests) {
        QTest::qExec(test, a.arguments());
    }
    qDeleteAll(tests.begin(), tests.end());
    return 0;
}


