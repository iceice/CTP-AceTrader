#pragma once
#include <QString>
#include "ThostFtdcTraderApi.h"

class Order{
public:
	Order(QString id, QString code);
	~Order();
	void update(CThostFtdcOrderField *p);
public:
	//报单引用
	QString	OrderRef;
	//前置编号
	int	FrontID;
	//会话编号
	int	SessionID;
	//交易所代码
	QString ExchangeID;
	//报单编号
	QString OrderSysID;
	//合约代码
	QString InstrumentID;
	//买卖方向
	char Direction;
	//组合开平标志
	char CombOffsetFlag[5];
	//数量
	int	VolumeTotalOriginal;
	//价格
	double LimitPrice;
	//今成交数量
	int	VolumeTraded;
	//报单状态
	char OrderStatus;
	//报单日期
	char InsertDate[9];
	//委托时间
	char InsertTime[9];
	//报单提交状态
	char OrderSubmitStatus;
};
