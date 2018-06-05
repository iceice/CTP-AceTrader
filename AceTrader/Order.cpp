#include "Order.h"
#include "string.h"
#include <QDebug>

#if _MSC_VER >= 1700
#pragma execution_character_set("utf-8")
#endif

Order::Order(QString id, QString code) :OrderSysID(id), InstrumentID(code) {
	//��������
	OrderRef = "";
	//ǰ�ñ��
	FrontID = 0;
	//�Ự���
	SessionID = 0;
	//����������
	ExchangeID = "";
	//��������
	Direction = '\0';
	//��Ͽ�ƽ��־
	memset(CombOffsetFlag, '\0', sizeof(CombOffsetFlag));
	//����
	VolumeTotalOriginal = 0;
	//�۸�
	LimitPrice = 0;
	//��ɽ�����
	VolumeTraded = 0;
	//����״̬
	OrderStatus = '\0';
	//��������
	memset(InsertDate, '\0', sizeof(InsertDate));
	//ί��ʱ��
	memset(InsertTime, '\0', sizeof(InsertTime));
	//�����ύ״̬
	OrderSubmitStatus = '\0';
}


Order::~Order(){
}

void Order::update(CThostFtdcOrderField * p){
	//��������
	OrderRef= QString::fromLocal8Bit(p->OrderRef);
	//ǰ�ñ��
	FrontID = p->FrontID;
	//�Ự���
	SessionID = p->SessionID;
	//����������
	ExchangeID = p->ExchangeID;
	//�������
	OrderSysID = QString::fromLocal8Bit(p->OrderSysID);
	//��Լ����
	InstrumentID = QString::fromLocal8Bit(p->InstrumentID);
	//��������
	Direction = p->Direction;
	//��Ͽ�ƽ��־
	strcpy(CombOffsetFlag,p->CombOffsetFlag);
	//����
	VolumeTotalOriginal = p->VolumeTotalOriginal;
	//�۸�
	LimitPrice = p->LimitPrice;
	//��ɽ�����
	VolumeTraded = p->VolumeTraded;
	//����״̬
	OrderStatus = p->OrderStatus;
	//��������
	strcpy(InsertDate, p->InsertDate);
	//ί��ʱ��
	strcpy(InsertTime, p->InsertTime);
	//�����ύ״̬
	OrderSubmitStatus = p->OrderSubmitStatus;
}
