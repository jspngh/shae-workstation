#include "detectioncontroller_test.h"

using namespace std;

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{

}

void DetectionController_Test::initTestCase()
{
	this->controller = new DetectionController();
	this->controllerThread = new QThread();
	this->controller->moveToThread(this->controllerThread);
	this->controllerThread->start(/*specify priority*/);

	// this is the behaviour we need, the slot function 'processSequence' will be executed in a different thread
	QObject::connect(this, &DetectionController_Test::newSequence,
	                 this->controller, &DetectionController::processSequence,
	                 Qt::ConnectionType::QueuedConnection);

	QObject::connect(this->controller, &DetectionController::newDetection,
	                 this, &DetectionController_Test::onNewDetection,
	                 Qt::ConnectionType::QueuedConnection);
	this->numDetections = 0;
	this->threadId = QThread::currentThreadId();
}

// This function is NOT a Unit Test.
// It is used to count the number of times the newDetection signal is emitted in the controller.
void DetectionController_Test::onNewDetection()
{
	++(this->numDetections);
	std::cout <<  "new detection #" << (this->numDetections) << std::endl;
}

void DetectionController_Test::testQueue()
{
	std::cout << "Main thread in: " << QThread::currentThreadId() << std::endl;

	// emitting the signal 'newSequence' will cause the execution of the slot 'processSequence' in a different thread
	emit newSequence(QString("seq#1"));
	emit newSequence(QString("seq#2"));
}

void DetectionController_Test::cleanupTestCase()
{
	this->controllerThread->quit();
	delete this->controller;
	delete this->controllerThread;
}


