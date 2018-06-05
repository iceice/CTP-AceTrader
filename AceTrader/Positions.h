#pragma once

#include <QString>
#include "ThostFtdcTraderApi.h"

class Positions{
public:
	Positions();
	Positions(CThostFtdcInvestorPositionField *p, int v);
	~Positions();
	void update(CThostFtdcInvestorPositionField *p);
public:
	//��Լ����
	QString InstrumentID;
	//��Լ��������
	int VolumeMultiple;
	//�ֲֶ�շ���
	char PosiDirection;
	//��ǰ�ֲ�
	int	Position;
	//���ճֲ�
	int	TodayPosition;
	//���־���=���ֽ��/������
	double OpenAverage;
	//�ֲ־���
	double PreSettlementPrice;
	//�ֲ�ӯ��
	double PositionProfit;
};

