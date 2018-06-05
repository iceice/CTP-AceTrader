#include "Positions.h"
#include "GVAR.h"
#include <QDebug>

Positions::Positions(){
	InstrumentID = "";
	VolumeMultiple = 0;
	PosiDirection = '\0';
	Position = 0;
	TodayPosition = 0;
	OpenAverage = 0;
	PreSettlementPrice = 0;
	PositionProfit = 0;
}

Positions::Positions(CThostFtdcInvestorPositionField *p, int v) :VolumeMultiple(v) {
	
	InstrumentID = p->InstrumentID;
	//持仓多空方向
	PosiDirection = p->PosiDirection;
	//当前持仓
	Position = p->Position;
	//今日持仓
	TodayPosition = p->TodayPosition;
	//开仓均价=开仓金额/开仓量
	OpenAverage = p->OpenCost / (p->Position*VolumeMultiple);
	//持仓均价
	PreSettlementPrice = p->PreSettlementPrice;
	//持仓盈亏
	PositionProfit = p->PositionProfit;


}


Positions::~Positions(){

}

void Positions::update(CThostFtdcInvestorPositionField * p){
	
	//持仓多空方向
	PosiDirection = p->PosiDirection;
	//当前持仓
	Position = p->Position;
	//今日持仓
	TodayPosition = p->TodayPosition;
	//开仓均价=开仓金额/开仓量
	OpenAverage = p->OpenCost/(p->Position*VolumeMultiple);
	//持仓均价
	PreSettlementPrice = p->PreSettlementPrice;
	//持仓盈亏
	PositionProfit = p->PositionProfit;
}
