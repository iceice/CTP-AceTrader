#pragma once
#include "ThostFtdcTraderApi.h"
#include "CTPTdApi.h"
#include <QObject>

class CTPTdSpi :public QObject, public CThostFtdcTraderSpi {
	Q_OBJECT
public:
	CTPTdSpi(std::shared_ptr<CTPTdApi> api);
	~CTPTdSpi();
	//当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用
	void OnFrontConnected() override;
	//登录请求响应
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//1、查询结算信息确认响应
	void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//2、请求查询投资者结算结果响应
	void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//3、投资者结算结果确认响应
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//4、查询全部合约响应
	void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);	
	//5、请求查询资金账户响应
	void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//6、请求查询投资者持仓响应
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//7、请求查询成交响应
	void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//8、请求查询报单响应
	void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//1、报单通知
	void OnRtnOrder(CThostFtdcOrderField *pOrder);
	//2、成交通知
	void OnRtnTrade(CThostFtdcTradeField *pTrade);

	void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
	void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);
	//释放资源
	void release();
private:
	std::shared_ptr<CTPTdApi> ctpTdApi;
signals:
	void tradeLoginSuccess();	//登陆成功信号
	void confirmSuccess();               //1、今日已经确认
	void confirmFailed();                //1、今日没有确认
	void querySettlementInfoSuccess();   //2、查询确认信息成功
	void settlementInfoConfirmSuccess(); //3、投资者结算结果确认成功
	void queryInstrumentSuccess();       //4、查询合约成功信号
	void queryTradingAccountSuccess();   //5、查询资金账户成功（bool是否第一次）
	void queryInvestorPositionSuccess(); //6、查询查询投资者持仓成功
	void queryTradeSuccess();            //7、查询成交成功
	void queryOrderSuccess();            //8、查询报单成功
	void updateOrder();
	void updateTrade();
	void updateAccount();
	void updatePositon();
	void startClose(QString);
	void startAction(QString);
	void loginFailed(QString);
};

