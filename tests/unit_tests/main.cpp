#include "core/simplepathalgorithm_test.h"
#include "core/detectioncontroller_test.h"
#include "core/json_messages_test.h"
#include "core/mediator_test.h"
#include "core/geopolygon_test.h"
#include "core/polygonpathalgorithm_test.h"

#include <QList>
#include <QTest>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList<QObject*> tests;
    tests.append(new SimplePathAlgorithm_Test());
    tests.append(new Json_Messages_Test());
    tests.append(new DetectionController_Test());
    tests.append(new Mediator_Test());
    tests.append(new GeoPolygon_test());
    tests.append(new PolygonPathAlgorithm_Test());

    foreach(QObject* test, tests) {
        QTest::qExec(test, a.arguments());
    }

    qDeleteAll(tests.begin(), tests.end());

    return 0;
}

