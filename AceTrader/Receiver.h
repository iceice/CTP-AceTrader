#pragma once

#include <qobject.h>
#include <qtimer.h>
#include <memory>
#include "CTPMdApi.h"
#include "CTPMdSpi.h"

class Receiver :public QObject {
	Q_OBJECT
public:
	Receiver();
	~Receiver();
	//��ʼ���̣߳����̶߳��󷢳��ź�֪ͨapi��������
	void connectServer();
	//��������
	int subscribeData(char *ppInstrumentID[], int nCount);
	//�˶�����
	int unsubscribeData(char *ppInstrumentID[], int nCount);
private:
	std::shared_ptr<CTPMdApi> api;
	std::shared_ptr<CTPMdSpi> spi;
	QTimer *connectOverTimer;	//���ӳ�ʱ��ʱ��
signals:
	//���������ص��ź�
	void connectFailed();
	void loginSuccess();
	private slots:
	//������ӳ�ʱ��ʱ������Ƿ����ӳ�ʱ
	void detectOvertime();
};