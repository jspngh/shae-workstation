#include "summarydialog.h"
#include "ui_summarydialog.h"

SummaryDialog::SummaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SummaryDialog)
{
    ui->setupUi(this);
}

SummaryDialog::~SummaryDialog()
{
    delete ui;
}
