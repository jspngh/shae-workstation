#include "core/videostreamdetection.h"
#include <QList>
#include <QTest>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QList<QObject *> tests;
    //tests.append(new VideostreamDetection_Test());
    foreach(QObject * test, tests) {
        QTest::qExec(test, a.arguments());
    }

    qDeleteAll(tests.begin(), tests.end());

    return 0;
}


