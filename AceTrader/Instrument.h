#pragma once

#include <qstring.h>
#include "ThostFtdcMdApi.h"

class Instrument {
public:
	Instrument(QString c, QString n, int v,double t);
	void update(CThostFtdcDepthMarketDataField *p);
public:
	const QString code;   //��Լ����
	const QString name;   //��Լ��
	double lastPrice;     //���¼�
	double bidPrice;	  //���
	int bidVolumn;        //����
	double askPrice;      //����
	int askVolumn;        //����
	double upperLimitPrice;//��ͣ��
	double lowerLimitPrice;//��ͣ��
	int volumn;             //�ɽ���
	double openPrice;      //����
	double lowestPrice;    //��ͼ�
	double highestPrice;   //��߼�
	double preClosePrice;  //������
	double preSettlementPrice; //�����
	char updateTime[9];    //�������ʱ��
	int	VolumeMultiple;    //��Լ��������
	double PriceTick;         //��С�䶯��λ
};