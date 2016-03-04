#include <QString>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>

class QtMapKit_Test : public QObject
{
    Q_OBJECT

public:
    QtMapKit_Test();
    ~QtMapKit_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
};

