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
	//֪ͨ���ڲ������ź�
	void connecting();		//��������
	void connectFailed();	//����ʧ��
	void loginSuccess();	//��½�ɹ�
	//���������ź�
	void tradeConnecting();
	void tradeConnectFailed();
	void tradeLoginSuccess();

	void loginFailed(QString);
};
