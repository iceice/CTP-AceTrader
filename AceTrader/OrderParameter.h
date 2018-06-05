#pragma once
#include <QString>
#include "ThostFtdcTraderApi.h"

class OrderParameter
{
public:
	OrderParameter(QString c);
	void update(CThostFtdcTradeField * p);
public:
	QString code;       //���׺�Լ
	char offset_flag;   //����ƽ��
	int num;            //����
	double price;       //�۸�
	double close_price; //ƽ�ּ۸�
	double stop_price;  //ֹ��۸�
	char condition;     //ֹ���־
	char direction;     //��������
	char timeCondition; //��Ч������
};

