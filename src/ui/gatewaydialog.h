#ifndef GATEWAYDIALOG_H
#define GATEWAYDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>

namespace Ui {
class GatewayDialog;
}

class GatewayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GatewayDialog(QWidget *parent = 0);
    ~GatewayDialog();
    QDialogButtonBox* getButtonBox();
    QString getSSID();
    QString getPassword();

private:
    Ui::GatewayDialog *ui;
};

#endif // GATEWAYDIALOG_H
