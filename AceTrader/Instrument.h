#pragma once

#include <qstring.h>
#include "ThostFtdcMdApi.h"

class Instrument {
public:
	Instrument(QString c, QString n, int v,double t);
	void update(CThostFtdcDepthMarketDataField *p);
public:
	const QString code;   //合约代码
	const QString name;   //合约名
	double lastPrice;     //最新价
	double bidPrice;	  //买价
	int bidVolumn;        //买量
	double askPrice;      //卖价
	int askVolumn;        //卖量
	double upperLimitPrice;//涨停价
	double lowerLimitPrice;//跌停价
	int volumn;             //成交量
	double openPrice;      //今开盘
	double lowestPrice;    //最低价
	double highestPrice;   //最高价
	double preClosePrice;  //昨收盘
	double preSettlementPrice; //昨结算
	char updateTime[9];    //行情更新时间
	int	VolumeMultiple;    //合约数量乘数
	double PriceTick;         //最小变动价位
};