#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QProgressDialog>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
	Q_OBJECT

public:
	explicit WelcomeWidget(QWidget *parent = 0);
	~WelcomeWidget();

signals:
	void configFileSignal(QString fileName);

private slots:
	void continueButtonPush();
	void browse();
	void find();
	//void openFileOfItem(int row, int column);

private:
	Ui::WelcomeWidget *ui;

	QStringList findFiles(const QStringList &files, const QString &text);
	void showFiles(const QStringList &files);

	QDir currentDir;
};

#endif // WELCOMEWIDGET_H
