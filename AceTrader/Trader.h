#pragma once
#include <QObject>
#include <qtimer.h>
#include <memory>
#include "CTPTdApi.h"
#include "CTPTdSpi.h"


class Trader :public QObject {
	Q_OBJECT
public:
	Trader();
	~Trader();
	//初始化线程，让线程对象发出信号通知api连接主机
	void connectServer();
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

private:
	std::shared_ptr<CTPTdApi> api;
	std::shared_ptr<CTPTdSpi> spi;
	QTimer *connectOverTimer;	//连接超时计时器
signals:
	//与控制器相关的信号
	void connectFailed();
	void loginSuccess();
	
	void confirmSuccess();      
	void confirmFailed();       
	void querySettlementInfoSuccess();
	void settlementInfoConfirmSuccess();
	void queryInstrumentSuccess();
	void queryTradingAccountSuccess();
	void queryInvestorPositionSuccess();
	void queryTradeSuccess();
	void queryOrderSuccess();
	void updateOrder();
	void updateTrade();
	void updateAccount();
	void updatePositon();
	void startClose(QString);
	void startAction(QString);
	void loginFailed(QString);
	private slots:
	//配合连接超时计时器检测是否连接超时
	void detectOvertime();
};

