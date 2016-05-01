#include "progressbarcontroller.h"

ProgressBarController::ProgressBarController(QObject *parent) : QObject(parent)
{

}

void ProgressBarController::setProgressBar(QProgressBar *pb)
{
    this->pb = pb;
}

void ProgressBarController::update(int percentage, int time)
{
    aborted = false;
    int current = pb->value();
    int difference = percentage - current;
    if (difference > 0)
    {
        long interval = (float) time / (float) difference * 1000;
        int value = pb->value();
        while (value < percentage && (!aborted))
        {
            pb->setValue(value + 1);
            QThread::msleep(interval);
            value = pb->value();
        }
    }
}
