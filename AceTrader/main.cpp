#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#include "MainWindow.h"
#include "LoginDialog.h"
#include "initialize.h"


int main(int argc, char *argv[]) {
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	
	QApplication a(argc, argv);

	QFile qss("ico/style.qss");
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();
	iniComboShow();
	iniLogin();

	/*LoginDialog *loginDialog = new LoginDialog();
	loginDialog->setObjectName("loginDialog");
	loginDialog->setFocus();
	loginDialog->show();*/
	
	MainWindow *mw = new MainWindow();
	mw = new MainWindow();
	mw->setObjectName("MainWindow");
	mw->resize(1100, 200);
	mw->show();
	mw->setFocus();

	return a.exec();
}
