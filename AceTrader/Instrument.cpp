#include "Instrument.h"
#include "string.h"
#define MAX 100000000

Instrument::Instrument(QString c, QString n, int v, double t) :code(c), name(n), VolumeMultiple(v),PriceTick(t) {
	lastPrice = 0;
	bidPrice = 0;
	bidVolumn = 0;
	askPrice = 0;
	askVolumn = 0;
	upperLimitPrice = 0;
	lowerLimitPrice = 0;
	volumn = 0;
	openPrice = 0;
	lowestPrice = 0;
	highestPrice = 0;
	preClosePrice = 0;
	preSettlementPrice = 0;
	memset(updateTime, '\0', sizeof(updateTime));
}

void Instrument::update(CThostFtdcDepthMarketDataField *p) {
	if (p->LastPrice > MAX) 
		lastPrice = 0;
	else
		lastPrice = p->LastPrice;
	if (p->BidPrice1 > MAX)
		bidPrice = 0;
	else
		bidPrice = p->BidPrice1;
	bidVolumn = p->BidVolume1;
	if (p->AskPrice1 > MAX)
		askPrice = 0;
	else
		askPrice = p->AskPrice1;
	askVolumn = p->AskVolume1;
	upperLimitPrice = p->UpperLimitPrice;
	lowerLimitPrice = p->LowerLimitPrice;
	volumn = p->Volume;
	openPrice = p->OpenPrice;
	lowestPrice = p->LowestPrice;
	highestPrice = p->HighestPrice;
	preClosePrice = p->PreClosePrice;
	preSettlementPrice = p->PreSettlementPrice;
	strcpy(updateTime, p->UpdateTime);
}