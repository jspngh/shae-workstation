#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMMapView.h>

namespace Ui {
class ConfigWidget;
}

class ConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigWidget(QWidget *parent = 0);
    ~ConfigWidget();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::ConfigWidget *ui;
    QMMapView *mapView;
    void initializeMap();

public slots:
    void onMapLoaded();

private slots:
    void startButtonPush();
    void backButtonPush();
    void sliderChanged(int);

};

#endif // CONFIGWIDGET_H
