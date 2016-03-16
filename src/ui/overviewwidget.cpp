#include "overviewwidget.h"
#include "ui_overviewwidget.h"

OverviewWidget::OverviewWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::OverviewWidget)
{
	ui->setupUi(this);

	ui->helloWorldLabel->setText("");
	count = 0;

	//lowerbuttons:
	connect(ui->clickButton, SIGNAL(clicked()), this, SLOT(clickButtonPush()));
	connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButtonPush()));
}

OverviewWidget::~OverviewWidget()
{
	delete ui;
}

void OverviewWidget::clickButtonPush()
{
	count ++;
	if (count % 2 == 1)
		ui->helloWorldLabel->setText("Hello World!");
	else
		ui->helloWorldLabel->setText("Bye World!");
}

void OverviewWidget::backButtonPush()
{
	((QStackedWidget *) this->parent())->setCurrentIndex(1);
}
