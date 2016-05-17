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
 * \brief The ProgressBarController class keeps track of the progressbar in the welcome screen
 * \ingroup Controllers

 */
class ProgressBarController : public QObject
{
    Q_OBJECT
public:
    explicit ProgressBarController(QObject *parent = 0);
    void setProgressBar(QProgressBar *pb);
    bool aborted;
signals:
    void incrementProcessBar();

public slots:
    void update(int percentage, int time);

private:
    QProgressBar *pb;
};

#endif // PROGRESSBARCONTROLLER_H
