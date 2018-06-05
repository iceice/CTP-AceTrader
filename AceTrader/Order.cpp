#include "Order.h"
#include "string.h"
#include <QDebug>

#if _MSC_VER >= 1700
#pragma execution_character_set("utf-8")
#endif

Order::Order(QString id, QString code) :OrderSysID(id), InstrumentID(code) {
	//报单引用
	OrderRef = "";
	//前置编号
	FrontID = 0;
	//会话编号
	SessionID = 0;
	//交易所代码
	ExchangeID = "";
	//买卖方向
	Direction = '\0';
	//组合开平标志
	memset(CombOffsetFlag, '\0', sizeof(CombOffsetFlag));
	//数量
	VolumeTotalOriginal = 0;
	//价格
	LimitPrice = 0;
	//今成交数量
	VolumeTraded = 0;
	//报单状态
	OrderStatus = '\0';
	//报单日期
	memset(InsertDate, '\0', sizeof(InsertDate));
	//委托时间
	memset(InsertTime, '\0', sizeof(InsertTime));
	//报单提交状态
	OrderSubmitStatus = '\0';
}


Order::~Order(){
}

void Order::update(CThostFtdcOrderField * p){
	//报单引用
	OrderRef= QString::fromLocal8Bit(p->OrderRef);
	//前置编号
	FrontID = p->FrontID;
	//会话编号
	SessionID = p->SessionID;
	//交易所代码
	ExchangeID = p->ExchangeID;
	//报单编号
	OrderSysID = QString::fromLocal8Bit(p->OrderSysID);
	//合约代码
	InstrumentID = QString::fromLocal8Bit(p->InstrumentID);
	//买卖方向
	Direction = p->Direction;
	//组合开平标志
	strcpy(CombOffsetFlag,p->CombOffsetFlag);
	//数量
	VolumeTotalOriginal = p->VolumeTotalOriginal;
	//价格
	LimitPrice = p->LimitPrice;
	//今成交数量
	VolumeTraded = p->VolumeTraded;
	//报单状态
	OrderStatus = p->OrderStatus;
	//报单日期
	strcpy(InsertDate, p->InsertDate);
	//委托时间
	strcpy(InsertTime, p->InsertTime);
	//报单提交状态
	OrderSubmitStatus = p->OrderSubmitStatus;
}
