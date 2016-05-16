#ifndef RESETSCRIPTCONTROLLER_H
#define RESETSCRIPTCONTROLLER_H

#include <QObject>

class ResetScriptController: public QObject
{
    Q_OBJECT
public:
    ResetScriptController(QObject *parent = 0);

signals:
    void resetSuccessful();

public slots:
    void reset();
};

#endif // RESETSCRIPTCONTROLLER_H
