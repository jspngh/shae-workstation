#ifndef OVERVIEWWIDGET_H
#define OVERVIEWWIDGET_H

#include <QWidget>

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
};

#endif // OVERVIEWWIDGET_H
