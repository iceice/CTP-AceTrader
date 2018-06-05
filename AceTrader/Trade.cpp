#include "Trade.h"
#include "string.h"


Trade::Trade(QString id, QString code) :OrderSysID(id), InstrumentID(code) {
	
	//��������
	Direction = '\0';
	//��Ͽ�ƽ��־
	OffsetFlag = '\0';
	//�۸�
	Price = 0;
	//����
	Volume = 0;
	//�ɽ�ʱ��
	memset(TradeTime, '\0', sizeof(TradeTime));
	//�ɽ�����
	memset(TradeDate, '\0', sizeof(TradeDate));
}


Trade::~Trade(){}

void Trade::update(CThostFtdcTradeField * p){
	//�������
	OrderSysID = QString::fromLocal8Bit(p->OrderSysID);
	//��Լ����
	InstrumentID = QString::fromLocal8Bit(p->InstrumentID);
	//��������
	Direction = p->Direction;
	//��Ͽ�ƽ��־
	OffsetFlag = p->OffsetFlag;
	//�۸�
	Price = p->Price;
	//����
	Volume = p->Volume;
	//�ɽ�ʱ��
	strcpy(TradeTime, p->TradeTime);
	//�ɽ�����
	strcpy(TradeDate, p->TradeDate);
}
