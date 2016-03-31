#ifndef VIDEOSTREAMDETECTION_H
#define VIDEOSTREAMDETECTION_H



#include <QString>
#include <QtTest/QtTest>

class VideostreamDetection_Test : public QObject
{
    Q_OBJECT

private:

public:
    VideostreamDetection_Test();
    ~VideostreamDetection_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void VideostreamDetectionTest();
};



#endif // VIDEOSTREAMDETECTION_H
