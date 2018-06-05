#pragma once
#include <QString>
#include "ThostFtdcTraderApi.h"

class Trade{
public:
	Trade(QString id, QString code);
	~Trade();
	void update(CThostFtdcTradeField *p);
public:
	//�������
	QString OrderSysID;
	//��Լ����
	QString InstrumentID;
	//��������
	char Direction;
	//��Ͽ�ƽ��־
	char OffsetFlag;
	//�۸�
	double Price;
	//����
	int	Volume;
	//�ɽ�ʱ��
	char TradeTime[9];
	//�ɽ�����
	char TradeDate[9];
};

