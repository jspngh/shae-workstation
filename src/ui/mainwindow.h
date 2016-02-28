#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMMapView.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QMMapView *mapView;

    void initializeMap();

public slots:
    void onMapLoaded();
};

#endif // MAINWINDOW_H
