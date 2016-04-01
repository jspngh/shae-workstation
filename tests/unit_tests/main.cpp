#include "core/simplepathalgorithm_test.h"
#include "core/detectioncontroller_test.h"
#include "core/videocontroller_test.h"
#include "core/json_messages_test.h"
#include "core/mediator_test.h"
#include "models/detectionresult.h"
#include <QList>
#include <QTest>
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<DetectionResult>("DetectionResult");
    QApplication a(argc, argv);

    QList<QObject *> tests;
    tests.append(new SimplePathAlgorithm_Test());
    tests.append(new Json_Messages_Test());
    tests.append(new DetectionController_Test());
    tests.append(new VideoController_Test());
    tests.append(new Mediator_Test());

    foreach (QObject *test, tests) {
        QTest::qExec(test, a.arguments());
    }

    qDeleteAll(tests.begin(), tests.end());

    return 0;
}

