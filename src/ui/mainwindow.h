#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QWidget>
#include <QMainWindow>
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
    WelcomeWidget* getWelcomeWidget();
    ConfigWidget* getConfigWidget();
    OverviewWidget* getOverviewWidget();

private:
    Ui::MainWindow *ui;
    WelcomeWidget *welcome_widget;
    ConfigWidget *config_widget;
    OverviewWidget *overview_widget;
};

#endif // MAINWINDOW_H
