#include "ConnectController.h"
#include "windows.h"
#include "QDebug"
using std::shared_ptr;
using std::make_shared;

ConnectController::ConnectController() = default;

//���ӿ�������ʼ���Լ�
void ConnectController::reset() {
	receiver = nullptr;
	trader = nullptr;
}

//�������ӿ������жԶ�����������
shared_ptr<Receiver> ConnectController::getReceiver() {
	return receiver;
}

std::shared_ptr<Trader> ConnectController::getTrader() {
	return trader;
}

//����һ��״ֵ̬���Ƿ�����������
bool ConnectController::isConnect() {
	if (receiver != nullptr && trader != nullptr) {
		return true;
	}
	else {
		return false;
	}
}


/*************************************�ۺ���***********************************************/

void ConnectController::connectServer() {
	receiver = make_shared<Receiver>();
	//���������źţ��ﵽת��Receiver���źŸ������Ŀ��
	connect(receiver.get(), SIGNAL(connectFailed()), this, SIGNAL(connectFailed()));
	connect(receiver.get(), SIGNAL(loginSuccess()), this, SIGNAL(loginSuccess()));
	receiver->connectServer();
	emit connecting();		//֪ͨ���ڲ��������ڵ�״̬Ϊ��������
}

void ConnectController::tradeConnectServer(){
	trader = make_shared<Trader>();
	connect(trader.get(), SIGNAL(connectFailed()), this, SIGNAL(tradeConnectFailed()));
	connect(trader.get(), SIGNAL(loginSuccess()), this, SIGNAL(tradeLoginSuccess()));
	connect(trader.get(), SIGNAL(loginFailed(QString)), this, SIGNAL(loginFailed(QString)));
	
	trader->connectServer();
	emit tradeConnecting();
}
