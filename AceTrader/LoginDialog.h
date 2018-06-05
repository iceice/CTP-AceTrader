#pragma once

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include "ConnectController.h"
#include "QueryController.h"
#include "MainWindow.h"

class LoginDialog : public QDialog{
	Q_OBJECT
public:
	LoginDialog();
	public slots:
	void startConnect();                //开始连接
private:
	QLabel *company;
	QLabel *server;
	QLabel *username;
	QLabel *psw;
	QComboBox *companyCombo;
	QComboBox *serverCombo;
	QLineEdit *nameLine;
	QLineEdit *pswLine;
	QPushButton *loginButton;
	QPushButton *cancelButoon;
	MainWindow *mw;
	QLabel *statusLabel;
	
	private slots:
	void showMainWindow();
	void changeCompany(int d);
	void statusConnecting();
	void statusConnectFailed();
	void tradeStatusConnecting();
	void tradeStatusConnectFailed();
	void statusQuery(QString msg);      //传递消息
	void statusLoginFailed(QString msg);
};
