#include "welcomewidget.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    ui->configTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->configTable->verticalHeader()->hide();
    ui->configTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->browseEdit->setText(QDir::currentPath());

    connect(ui->continueButton,SIGNAL(clicked()),this, SLOT(continueButtonPush()));
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browse()));
    connect(ui->findButton,SIGNAL(clicked()),this, SLOT(find()));
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}

void WelcomeWidget::continueButtonPush(){
    if(ui->configTable->selectedItems().size() == 3)
    {
        QString ss = ui->configTable->selectedItems().at(0)->text();
        emit configFileSignal(ss);
    } else {
        emit configFileSignal("");
    }
    ((QStackedWidget*) this->parent())->setCurrentIndex(1);
}

void WelcomeWidget::browse()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Find Files"), QDir::currentPath());
}

void WelcomeWidget::find()
{
    ui->configTable->setRowCount(0);

    QString fileName = "*.conf";
    QString path =  ui->browseEdit->text();

    currentDir = QDir(path);
    QStringList files;
    files = currentDir.entryList(QStringList(fileName),
                                 QDir::Files | QDir::NoSymLinks);
    showFiles(files);
}

QStringList WelcomeWidget::findFiles(const QStringList &files, const QString &text)
{
    QProgressDialog progressDialog(this);
    progressDialog.setCancelButtonText(tr("&Cancel"));
    progressDialog.setRange(0, files.size());
    progressDialog.setWindowTitle(tr("Find Files"));
    QStringList foundFiles;

    for (int i = 0; i < files.size(); ++i) {
        progressDialog.setValue(i);
        progressDialog.setLabelText(tr("Searching file number %1 of %2...")
                                    .arg(i).arg(files.size()));
        qApp->processEvents();
        QFile file(currentDir.absoluteFilePath(files[i]));

        if (file.open(QIODevice::ReadOnly)) {
            QString line;
            QTextStream in(&file);
            while (!in.atEnd()) {
                if (progressDialog.wasCanceled())
                    break;
                line = in.readLine();
                if (line.contains(text)) {
                    foundFiles << files[i];
                    break;
                }
            }
        }
    }
    return foundFiles;
}

void WelcomeWidget::showFiles(const QStringList &files)
{
    for (int i = 0; i < files.size(); ++i) {
        QFile file(currentDir.absoluteFilePath(files[i]));
        QString dateString = QFileInfo(file).created().toString();
        qint64 size = QFileInfo(file).size();

        QTableWidgetItem *fileNameItem = new QTableWidgetItem(files[i]);
        fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *dateItem = new QTableWidgetItem(dateString);
        dateItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *sizeItem = new QTableWidgetItem(tr("%1 KB")
                                             .arg(int((size + 1023) / 1024)));
        sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);

        int row = ui->configTable->rowCount();
        ui->configTable->insertRow(row);
        ui->configTable->setItem(row, 0, fileNameItem);
        ui->configTable->setItem(row, 1, dateItem);
        ui->configTable->setItem(row, 2, sizeItem);
    }
}
