#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QString>
#include <QList>

/*! \brief The mediator connects all components to each other.
 * Mediator is implemented as a singleton class
 * Get access to the singleton using the static method \ref Mediator::get()
 * Add signals and slots using the methods \ref Mediator::addSignal() and \ref Mediator::addSlot() respectivily.
 */
class Mediator: public QObject
{
    Q_OBJECT

public:
    Mediator(Mediator const &copy) = delete;            // Not Implemented: prevent the creation of multiple instances
    Mediator &operator=(Mediator const &copy) = delete; // Not Implemented: prevent the creation of multiple instances

    /*!
     * \brief instance static method to get access to the global instance (singleton) Mediator
     * \return Mediator instance
     */
    static Mediator &get();

    /*!
     * \brief addSignal will connect the signal to every slot with the same signalName. (thread-safe function)
     * \param sender the sending object
     * \param signal name of the signal method. Note: use QT's macro SIGNAL to construct the char* desired argument
     * \param signalName name of the signal. Note: the slot must choose the same signalName to connect both
     * \return the number of slots that implement the slot listing to the added signal
     */
    int addSignal(QObject *sender, char *signal, QString signalName);

    /*!
     * \brief addSlot will connect the slot to every signal with the same signalName. (thread-safe function)
     * \param receiver the receiving object
     * \param slot name of the slot method. Note: use QT's macro SLOT to construct the char* desired argument
     * \param signalName name of the signal. Note: the signal must choose the same signalName to connect both
     * \return the number of signal emitting the signal with the same signalName
     */
    int addSlot(QObject *receiver, char *slot, QString signalName);

    virtual ~Mediator() {}

private Q_SLOTS:
    void onReceiverObjectDestroyed(QObject *obj);
    void onSenderObjectDestroyed(QObject *obj);


private:
    //! Mediator constructor is set private because the class is implemented as a singleton
    Mediator(QObject *parent = 0);

    QMutex mutex;

    /*!
     * \brief The Element class holds the information from a signal or a slot.
     * To connect a signal and a slot the signalName must be identical
     * E.g.:
     * signal information:
     *      signalName = "newDetection"
     *      object: points to a instance of a detectionController (will emit the signal)
     *      method: name of the signal that will be emitted (convention: signalname = newDetection)
     * slot information:
     *      signalName = "newDetection"
     *      object: points to a instance of the gui that will implement the slot
     *      method: name of the slot (convention: on + SignalName, here: onNewDetection)
     */
    class Element
    {
    public:
        Element(QObject *obj, char *method, QString s)
            : signalName(s), object(obj), method(method)
        {

        }

        QString signalName; //!< the name of the signal
        QObject *object; //!< the sender or receiver object
        char *method; //!< can be the name of a signal or a slot method
    };

    QList<Element> signalList;
    QList<Element> slotList;

};

#endif // MEDIATOR_H

