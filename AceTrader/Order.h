#pragma once
#include <QString>
#include "ThostFtdcTraderApi.h"

class Order{
public:
	Order(QString id, QString code);
	~Order();
	void update(CThostFtdcOrderField *p);
public:
	//��������
	QString	OrderRef;
	//ǰ�ñ��
	int	FrontID;
	//�Ự���
	int	SessionID;
	//����������
	QString ExchangeID;
	//�������
	QString OrderSysID;
	//��Լ����
	QString InstrumentID;
	//��������
	char Direction;
	//��Ͽ�ƽ��־
	char CombOffsetFlag[5];
	//����
	int	VolumeTotalOriginal;
	//�۸�
	double LimitPrice;
	//��ɽ�����
	int	VolumeTraded;
	//����״̬
	char OrderStatus;
	//��������
	char InsertDate[9];
	//ί��ʱ��
	char InsertTime[9];
	//�����ύ״̬
	char OrderSubmitStatus;
};
