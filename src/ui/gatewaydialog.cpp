#include "gatewaydialog.h"
#include "ui_gatewaydialog.h"

GatewayDialog::GatewayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GatewayDialog)
{
    ui->setupUi(this);
}

GatewayDialog::~GatewayDialog()
{
    delete ui;
}

QDialogButtonBox* GatewayDialog::getButtonBox()
{
    return ui->buttonBox;
}

QString GatewayDialog::getSSID()
{
    return ui->networkNameEdit->text();
}

QString GatewayDialog::getPassword()
{
    return ui->passwordEdit->text();
}
