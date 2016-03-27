#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QStackedWidget>

#include "ui_mainwindow.h"
#include "configwidget.h"
#include "overviewwidget.h"
#include "welcomewidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    WelcomeWidget *getWelcomeWidget();
    ConfigWidget *getConfigWidget();
    OverviewWidget *getOverviewWidget();

private:
    Ui::MainWindow *ui;
    WelcomeWidget *welcomeWidget;
    ConfigWidget *configWidget;
    OverviewWidget *overviewWidget;
};

#endif // MAINWINDOW_H
