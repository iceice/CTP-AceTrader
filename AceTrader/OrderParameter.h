#pragma once
#include <QString>
#include "ThostFtdcTraderApi.h"

class OrderParameter
{
public:
	OrderParameter(QString c);
	void update(CThostFtdcTradeField * p);
public:
	QString code;       //交易合约
	char offset_flag;   //开、平仓
	int num;            //数量
	double price;       //价格
	double close_price; //平仓价格
	double stop_price;  //止损价格
	char condition;     //止损标志
	char direction;     //买卖方向
	char timeCondition; //有效期类型
};

