#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QStackedWidget>
#include <QThread>
#include "ui_mainwindow.h"
#include "core/mediator.h"
#include "configwidget.h"
#include "overviewwidget.h"
#include "welcomewidget.h"
#include "ui/controllers/resetscriptcontroller.h"

/*!
 * \brief The MainWindow class represents the window the user sees the whole time
 * \ingroup Ui
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Constructor creates the widgets and connects the ui signals
    explicit MainWindow(QWidget *parent = 0);
    //! Destructor deletes the different widgets and the mainwindow
    ~MainWindow();
    //! sets the mediator to connect signals to slots from the logic of the application
    void setMediator(Mediator *mediator);

    WelcomeWidget *getWelcomeWidget();
    ConfigWidget *getConfigWidget();
    OverviewWidget *getOverviewWidget();

private slots:
    //! links the slot from the menu to the saveSearch slot from the summary dialog
    void onSaveSearchClicked();
    //! links the slot from the menu to the saveFootage slot from the summary dialog
    void onSaveFootageClicked();
    void onResetDroneClicked();
    void onResetSuccessful();

private:
    //! a pointer to the mediator that connects all signals and slots between components
    Mediator *mediator;
    ResetScriptController *resetCtrl;
    QThread *resetThread;
    QMessageBox msgBox;

    //! a pointer to the ui_mainwindow
    Ui::MainWindow *ui;
    //! a pointer to the welcomewidget (the first screen of the app)
    WelcomeWidget *welcomeWidget;
    //! a pointer to the configwidget (the second screen of the app)
    ConfigWidget *configWidget;
    //! a pointer to the overviewwidget (the third screen of the app)
    OverviewWidget *overviewWidget;
};

#endif // MAINWINDOW_H

