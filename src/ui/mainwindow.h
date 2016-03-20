#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QStackedWidget>
#include "core/mediator.h"
#include "configwidget.h"
#include "overviewwidget.h"
#include "welcomewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    WelcomeWidget *getWelcomeWidget();
    ConfigWidget *getConfigWidget();
    OverviewWidget *getOverviewWidget();
    void setMediator(Mediator *mediator);

private:
    Ui::MainWindow *ui;
    WelcomeWidget *welcomeWidget;
    ConfigWidget *configWidget;
    OverviewWidget *overviewWidget;
};

#endif // MAINWINDOW_H
