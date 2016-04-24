#ifndef SUMMARYDIALOG_H
#define SUMMARYDIALOG_H

#include <QDialog>

namespace Ui {
class SummaryDialog;
}

class SummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SummaryDialog(QWidget *parent = 0);
    ~SummaryDialog();

private:
    Ui::SummaryDialog *ui;
};

#endif // SUMMARYDIALOG_H
