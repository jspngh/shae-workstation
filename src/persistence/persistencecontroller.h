#ifndef PERSISTENCECONTROLLER_H
#define PERSISTENCECONTROLLER_H

#include <QObject>
#include "core/mediator.h"
#include "persistence.h"

class PersistenceController : public QObject
{
    Q_OBJECT
public:
    explicit PersistenceController(Mediator *mediator, QObject *parent = 0);
    ~PersistenceController(){}

signals:

public slots:
    void saveSearch(Search *s);
    void saveDronePaths(Search *s);
    void saveDroneStatus(DroneStatus ds);
    void saveDetectionResult(DetectionResult dr);
    void saveVideoSequence(VideoSequence vs);

private:
    Mediator *mediator;
    Persistence *persistence;
};

#endif // PERSISTENCECONTROLLER_H
