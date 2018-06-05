#pragma once

#include "ThostFtdcTraderApi.h"
#include "GVAR.h"
#include <QObject>
#include <memory>

class CTPTdApi:public QObject{
	Q_OBJECT
public:
	CTPTdApi();
	~CTPTdApi();
	void registerSpi(std::shared_ptr<CThostFtdcTraderSpi> spi);
	void login();
	void release();

	int reqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID);
	int reqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID);
	int reqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID);
	int reqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID);
	int reqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID);
	int reqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID);
	int reqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID);
	int reqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID);
	int reqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID);
	int reqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID);

	bool isConnect();
	//设置api的状态，api一旦初始化连接上主机就不再断开，因此一旦初始化连接状态符号就为真且不变
	void setConnect();
	//注册前置机并初始化Api,该函数需要通过线程间接调用，不可以直接调用
	void connectServer();
private:
	CThostFtdcTraderApi * ctpTdApi;
	std::shared_ptr<CThostFtdcTraderSpi> ctpTdSpi;
	bool connecFlag;
};

