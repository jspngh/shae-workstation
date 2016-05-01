#ifndef PROGRESSBARCONTROLLER_H
#define PROGRESSBARCONTROLLER_H

#include <QObject>
#include <QtWidgets/QProgressBar>
#include <QThread>
#include <QDebug>

class ProgressBarController : public QObject
{
    Q_OBJECT
public:
    explicit ProgressBarController(QObject *parent = 0);
    void setProgressBar(QProgressBar *pb);
    bool aborted;
signals:

public slots:
    void update(int percentage, int time);

private:
    QProgressBar *pb;
};

#endif // PROGRESSBARCONTROLLER_H
