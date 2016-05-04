#ifndef SUMMARYDIALOG_H
#define SUMMARYDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include "core/mediator.h"

namespace Ui {
class SummaryDialog;
}

class SummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SummaryDialog(QWidget *parent = 0);
    ~SummaryDialog();

    void setMediator(Mediator *mediator);

private:
    QString streamLocation();

private slots:
    void onSaveFootageClicked();
    void onSaveSearchClicked();
    void onCloseAppClicked();

signals:
    void  printDetectionResultXML(QString);
    void  printDetectionResultTXT(QString);

private:
    Ui::SummaryDialog *ui;
    Mediator *mediator;
};

#endif // SUMMARYDIALOG_H
