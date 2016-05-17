#ifndef PROGRESSBARCONTROLLER_H
#define PROGRESSBARCONTROLLER_H

#include <QObject>
#include <QtWidgets/QProgressBar>
#include <QThread>
#include <QDebug>

/*!
  \defgroup Controllers
  \ingroup Ui
  \brief Controllers are simple controllers used in the ui to keep track of a progressbar and to control the scripts to automate manual drone controls such as setting a gateway

  */


/*!
 * \brief The ProgressBarController class keeps track of the progress bar in the welcome screen
 * \ingroup Controllers
 The ProgressBarController class controls a progress bar which is set with the method setProgressBar(QProgressbar).
 The incrementation of a progress bar cannot happen within another thread than the thread where the ui is running in.
 Thus, this class decides on which time a signal to increment the progress bar must be send to the ui thread.
 The value of the progress bar is not directly set by this class.
 */
class ProgressBarController : public QObject
{
    Q_OBJECT
public:
    explicit ProgressBarController(QObject *parent = 0);
    //! Sets the progress bar to controll
    void setProgressBar(QProgressBar *pb);
    //! If aborted is true, the incrementation of the progress bar is directly stopped
    bool aborted;
signals:
    //! Signal that is send to the ui thread to increment the process bar
    void incrementProcessBar();

public slots:
    //! Slot that needs the destination percentage and the time required to reach this percentage
    //! Calculates equal timeslots. In each timeslot a signal is emmited to the ui thread to increment the progress bar
    void update(int percentage, int time);

private:
    QProgressBar *pb;
};

#endif // PROGRESSBARCONTROLLER_H
