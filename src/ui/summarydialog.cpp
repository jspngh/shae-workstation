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
    QFile stream(streamLocation());
    if (stream.exists()) {
        QString filter = "Video (*.avi)";
        QString saveLocation = QFileDialog::getSaveFileName(this, tr("Save Detection Results"), QDir::homePath(), filter, &filter);
        qDebug() << saveLocation;
        stream.copy(saveLocation);
    } else {
        QMessageBox::warning(this, "Warning!","The stream has not been created. It is not possible to save it.", "OK");
    }
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

QString SummaryDialog::streamLocation()
{
    QString name = "drone_stream.avi";
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    //create folder if not available
    QDir(QDir::root()).mkpath(folder);

    if (!folder.endsWith(QDir::separator()))
        folder.append(QDir::separator());

    return folder.append(name);
}

