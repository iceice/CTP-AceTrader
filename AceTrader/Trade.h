#pragma once
#include <QString>
#include "ThostFtdcTraderApi.h"

class Trade{
public:
	Trade(QString id, QString code);
	~Trade();
	void update(CThostFtdcTradeField *p);
public:
	//报单编号
	QString OrderSysID;
	//合约代码
	QString InstrumentID;
	//买卖方向
	char Direction;
	//组合开平标志
	char OffsetFlag;
	//价格
	double Price;
	//数量
	int	Volume;
	//成交时间
	char TradeTime[9];
	//成交日期
	char TradeDate[9];
};

