#pragma once

#include <QObject>
#include <memory>
#include "Trader.h"

class TradeController : public QObject{
	Q_OBJECT
public:
	TradeController();
	void reset();
	void setTrader(std::shared_ptr<Trader> t);
	//int reqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID);

	public slots:
	void tradeServer(OrderParameter *orderPara);
	void tradeClose(QString oref);
	void reqOrderAction(QString id);
	void actionClose(QString oref);
private:
	std::shared_ptr<Trader> trader;
signals:
	void updateOrder();
	void updateTrade();
};