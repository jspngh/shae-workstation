#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QMMapView.h>
#include <QStackedWidget>
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
    QWidget *getWelcomeWidget();

private:
    Ui::MainWindow *ui;
    WelcomeWidget *welcome_widget;
    ConfigWidget *config_widget;
    OverviewWidget *overview_widget;
};

#endif // MAINWINDOW_H
