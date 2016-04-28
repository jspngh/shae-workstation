#include "summarydialog.h"
#include "ui_summarydialog.h"

SummaryDialog::SummaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SummaryDialog)
{
    ui->setupUi(this);

    connect(ui->saveFootageBtn, SIGNAL(clicked()), this, SLOT(onSaveFootageClicked()));
    connect(ui->saveSearchBtn, SIGNAL(clicked()), this, SLOT(onSaveSearchClicked()));
    connect(ui->closeAppBtn,SIGNAL(clicked()), this, SLOT(onCloseAppClicked()));


}

SummaryDialog::~SummaryDialog()
{
    delete ui;
}

void SummaryDialog::setMediator(Mediator *mediator)
{
    this->mediator = mediator;
    mediator->addSignal(this, SIGNAL(printDetectionResultXML(QString)), QString("printDetectionResultXML(QString)"));
    mediator->addSignal(this, SIGNAL(printDetectionResultTXT(QString)), QString("printDetectionResultTXT(QString)"));
}

void SummaryDialog::onSaveFootageClicked()
{

}

void SummaryDialog::onSaveSearchClicked()
{
    QString filter = "XML sheet (*.xml);;Text File (*.txt)";
    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save Detection Results"), QDir::homePath(), filter, &filter);

    if(filter == QString("Text File (*.txt)"))
        emit printDetectionResultTXT(saveFileName.append(".txt"));
    else
        emit printDetectionResultXML(saveFileName.append(".xml"));
}

void SummaryDialog::onCloseAppClicked()
{
    QCoreApplication::quit();
}
