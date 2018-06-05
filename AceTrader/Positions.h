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
	//合约代码
	QString InstrumentID;
	//合约数量乘数
	int VolumeMultiple;
	//持仓多空方向
	char PosiDirection;
	//当前持仓
	int	Position;
	//今日持仓
	int	TodayPosition;
	//开仓均价=开仓金额/开仓量
	double OpenAverage;
	//持仓均价
	double PreSettlementPrice;
	//持仓盈亏
	double PositionProfit;
};

