#include "Positions.h"
#include "GVAR.h"
#include <QDebug>

Positions::Positions(){
	InstrumentID = "";
	VolumeMultiple = 0;
	PosiDirection = '\0';
	Position = 0;
	TodayPosition = 0;
	OpenAverage = 0;
	PreSettlementPrice = 0;
	PositionProfit = 0;
}

Positions::Positions(CThostFtdcInvestorPositionField *p, int v) :VolumeMultiple(v) {
	
	InstrumentID = p->InstrumentID;
	//�ֲֶ�շ���
	PosiDirection = p->PosiDirection;
	//��ǰ�ֲ�
	Position = p->Position;
	//���ճֲ�
	TodayPosition = p->TodayPosition;
	//���־���=���ֽ��/������
	OpenAverage = p->OpenCost / (p->Position*VolumeMultiple);
	//�ֲ־���
	PreSettlementPrice = p->PreSettlementPrice;
	//�ֲ�ӯ��
	PositionProfit = p->PositionProfit;


}


Positions::~Positions(){

}

void Positions::update(CThostFtdcInvestorPositionField * p){
	
	//�ֲֶ�շ���
	PosiDirection = p->PosiDirection;
	//��ǰ�ֲ�
	Position = p->Position;
	//���ճֲ�
	TodayPosition = p->TodayPosition;
	//���־���=���ֽ��/������
	OpenAverage = p->OpenCost/(p->Position*VolumeMultiple);
	//�ֲ־���
	PreSettlementPrice = p->PreSettlementPrice;
	//�ֲ�ӯ��
	PositionProfit = p->PositionProfit;
}
