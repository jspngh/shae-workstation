#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QStackedWidget>
#include "ui_mainwindow.h"
#include "core/mediator.h"
#include "configwidget.h"
#include "overviewwidget.h"
#include "welcomewidget.h"
/*!
 * \brief The MainWindow class
 * \ingroup Ui
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setMediator(Mediator *mediator);
    WelcomeWidget *getWelcomeWidget();
    ConfigWidget *getConfigWidget();
    OverviewWidget *getOverviewWidget();

private slots:
    void onSaveSearchClicked();
    void onSaveFootageClicked();

private:
    Mediator *mediator;

    Ui::MainWindow *ui;
    WelcomeWidget *welcomeWidget;
    ConfigWidget *configWidget;
    OverviewWidget *overviewWidget;
};

#endif // MAINWINDOW_H

