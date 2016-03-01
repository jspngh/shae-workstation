#ifndef OVERVIEWWIDGET_H
#define OVERVIEWWIDGET_H

#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class OverviewWidget;
}

class OverviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewWidget(QWidget *parent = 0);
    ~OverviewWidget();

private:
    Ui::OverviewWidget *ui;
    int count;

private slots:
    void clickButtonPush();
    void backButtonPush();

};

#endif // OVERVIEWWIDGET_H
