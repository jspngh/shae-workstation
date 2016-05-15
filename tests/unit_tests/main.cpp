#include <QApplication>
#include <QList>
#include <QTest>
#include "core/databasecreator.h"
#include "core/detectioncontroller_test.h"
#include "core/detectionresultdao_test.h"
#include "core/dronedao_test.h"
#include "core/dronesearchdao_test.h"
#include "core/dronestatusdao_test.h"
#include "core/geopolygon_test.h"
#include "core/json_messages_test.h"
#include "core/mediator_test.h"
#include "core/pathalgorithm_test.h"
#include "core/dronestatus_test.h"
#include "core/hellomessage_test.h"
#include "core/controller_test.h"

#include "core/parseexception_test.h"
#include "core/streamconnection_test.h"
#include "core/droneheartbeatreceiver_test.h"

#include "core/xmlwriter_test.h"



#include "core/polygonpathalgorithm_test.h"
#include "core/searchdao_test.h"
#include "core/simplepathalgorithm_test.h"
#include "core/videocontroller_test.h"
#include "core/videosequencedao_test.h"
#include "models/detectionresult.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<DetectionResult>("DetectionResult");
    QApplication a(argc, argv);
    DatabaseCreator db = DatabaseCreator();
    db.removeDatabase();
    db.initDatabase();

    QList<QObject *> tests;

    /********************
     * Testing pathlogic
     * *****************/

    tests.append(new Pathalgorithm_Test());
    tests.append(new SimplePathAlgorithm_Test());
    tests.append(new GeoPolygon_test());
    tests.append(new PolygonPathAlgorithm_Test());

    /********************
     * Testing jsonstuff
     * *****************/

    // sending using dronemodule (inside communication)
    tests.append(new Json_Messages_Test());
    // receiving using dronestatus (inside models)
    tests.append(new DroneStatus_Test());
    tests.append(new HelloMessage_Test());

    /************************
     * Testing communication
     * *********************/

    tests.append(new ParseException_Test());
    tests.append(new StreamConnection_Test());
    tests.append(new DroneHeartbeatReceiver_Test());


    /********************
     * Testing persistence
     * *****************/

    tests.append(new SearchDAO_Test());

    tests.append(new DetectionResultDAO_Test());
    tests.append(new DroneDAO_Test());
    tests.append(new DroneSearchDAO_Test());
    tests.append(new DroneStatusDAO_Test());
    tests.append(new VideoSequenceDAO_Test());


    /********************
     * Testing videostuff
     * *****************/

    tests.append(new VideoController_Test());
    tests.append(new DetectionController_Test());



    /********************
     * Testing other stuff
     * *****************/

    tests.append(new XMLWriter_Test());


    /*********************
     *  Testing core
     * *******************/
    tests.append(new Mediator_Test());
    tests.append(new Controller_Test());



    foreach (QObject *test, tests) {
        QTest::qExec(test, a.arguments());
    }

    qDeleteAll(tests.begin(), tests.end());
    db.removeDatabase();

    return 0;
}

