#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_helloWorldButton_clicked()
{
    count ++;
    if(count%2 == 1)
        ui->helloWorldLabel->setText("Hello World!");
    else
        ui->helloWorldLabel->setText("Bye World!");
}
