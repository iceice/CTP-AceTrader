#include "Trade.h"
#include "string.h"


Trade::Trade(QString id, QString code) :OrderSysID(id), InstrumentID(code) {
	
	//买卖方向
	Direction = '\0';
	//组合开平标志
	OffsetFlag = '\0';
	//价格
	Price = 0;
	//数量
	Volume = 0;
	//成交时间
	memset(TradeTime, '\0', sizeof(TradeTime));
	//成交日期
	memset(TradeDate, '\0', sizeof(TradeDate));
}


Trade::~Trade(){}

void Trade::update(CThostFtdcTradeField * p){
	//报单编号
	OrderSysID = QString::fromLocal8Bit(p->OrderSysID);
	//合约代码
	InstrumentID = QString::fromLocal8Bit(p->InstrumentID);
	//买卖方向
	Direction = p->Direction;
	//组合开平标志
	OffsetFlag = p->OffsetFlag;
	//价格
	Price = p->Price;
	//数量
	Volume = p->Volume;
	//成交时间
	strcpy(TradeTime, p->TradeTime);
	//成交日期
	strcpy(TradeDate, p->TradeDate);
}
