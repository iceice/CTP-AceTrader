#pragma once

#include <qobject.h>
#include <memory>
#include <qpushbutton.h>
#include "Receiver.h"
#include "Trader.h"

class ConnectController :public QObject {
	Q_OBJECT
public:
	ConnectController();
	void reset();
	std::shared_ptr<Receiver> getReceiver();
	std::shared_ptr<Trader> getTrader();
	bool isConnect();
private:
	std::shared_ptr<Receiver> receiver;
	std::shared_ptr<Trader> trader;
	public slots:
	void connectServer();
	void tradeConnectServer();
signals:
	//通知窗口部件的信号
	void connecting();		//正在连接
	void connectFailed();	//连接失败
	void loginSuccess();	//登陆成功
	//交易连接信号
	void tradeConnecting();
	void tradeConnectFailed();
	void tradeLoginSuccess();

	void loginFailed(QString);
};
