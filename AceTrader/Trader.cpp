#include "Trader.h"
#include "qdebug.h"
using std::shared_ptr;
using std::make_shared;

Trader::Trader() {
	api = make_shared<CTPTdApi>();
	spi = make_shared<CTPTdSpi>(api);
	api->registerSpi(spi);
	//api调用函数后,spi反馈结果信号，Receiver传递信号给控制器
	connect(spi.get(), SIGNAL(tradeLoginSuccess()), this, SIGNAL(loginSuccess()));
	connect(spi.get(), SIGNAL(confirmSuccess()), this, SIGNAL(confirmSuccess()));
	connect(spi.get(), SIGNAL(confirmFailed()), this, SIGNAL(confirmFailed()));
	connect(spi.get(), SIGNAL(querySettlementInfoSuccess()), this, SIGNAL(querySettlementInfoSuccess()));
	connect(spi.get(), SIGNAL(settlementInfoConfirmSuccess()), this, SIGNAL(settlementInfoConfirmSuccess()));
	connect(spi.get(), SIGNAL(queryInstrumentSuccess()), this, SIGNAL(queryInstrumentSuccess()));
	connect(spi.get(), SIGNAL(queryTradingAccountSuccess()), this, SIGNAL(queryTradingAccountSuccess()));
	connect(spi.get(), SIGNAL(queryInvestorPositionSuccess()), this, SIGNAL(queryInvestorPositionSuccess()));
	connect(spi.get(), SIGNAL(queryTradeSuccess()), this, SIGNAL(queryTradeSuccess()));
	connect(spi.get(), SIGNAL(queryOrderSuccess()), this, SIGNAL(queryOrderSuccess()));
	connect(spi.get(), SIGNAL(updateOrder()), this, SIGNAL(updateOrder()));
	connect(spi.get(), SIGNAL(updateTrade()), this, SIGNAL(updateTrade()));
	connect(spi.get(), SIGNAL(updateAccount()), this, SIGNAL(updateAccount()));
	connect(spi.get(), SIGNAL(updatePositon()), this, SIGNAL(updatePositon()));
	connect(spi.get(), SIGNAL(startClose(QString)), this, SIGNAL(startClose(QString)));
	connect(spi.get(), SIGNAL(startAction(QString)), this, SIGNAL(startAction(QString)));
	connect(spi.get(), SIGNAL(loginFailed(QString)), this, SIGNAL(loginFailed(QString)));

	//设置连接超时计时器
	connectOverTimer = new QTimer(this);
	connect(connectOverTimer, SIGNAL(timeout()), this, SLOT(detectOvertime()));
	connectOverTimer->setSingleShot(true);
}


Trader::~Trader() {
	//先让api对Spi解引用
	api->registerSpi(NULL);
	spi->release();
	qDebug() << "~Receiver";
}

//让api连接主机
void Trader::connectServer() {
	api->connectServer();
	connectOverTimer->start(3 * 1000);
}

int Trader::reqQrySettlementInfo(CThostFtdcQrySettlementInfoField * pQrySettlementInfo, int nRequestID) {
	return api->reqQrySettlementInfo(pQrySettlementInfo, nRequestID);
}

int Trader::reqQryInstrument(CThostFtdcQryInstrumentField * pQryInstrument, int nRequestID){
	return api->reqQryInstrument(pQryInstrument, nRequestID);
}

int Trader::reqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField * pQrySettlementInfoConfirm, int nRequestID){
	return api->reqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, nRequestID);
}

int Trader::reqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, int nRequestID){
	return api->reqSettlementInfoConfirm(pSettlementInfoConfirm, nRequestID);
}

int Trader::reqQryTradingAccount(CThostFtdcQryTradingAccountField * pQryTradingAccount, int nRequestID){
	return api->reqQryTradingAccount(pQryTradingAccount, nRequestID);
}

int Trader::reqQryInvestorPosition(CThostFtdcQryInvestorPositionField * pQryInvestorPosition, int nRequestID){
	return api->reqQryInvestorPosition(pQryInvestorPosition, nRequestID);
}

int Trader::reqQryTrade(CThostFtdcQryTradeField * pQryTrade, int nRequestID){
	return api->reqQryTrade(pQryTrade, nRequestID);
}

int Trader::reqQryOrder(CThostFtdcQryOrderField * pQryOrder, int nRequestID){
	return api->reqQryOrder(pQryOrder, nRequestID);
}

int Trader::reqOrderInsert(CThostFtdcInputOrderField * pInputOrder, int nRequestID){
	return api->reqOrderInsert(pInputOrder, nRequestID);
}

int Trader::reqOrderAction(CThostFtdcInputOrderActionField * pInputOrderAction, int nRequestID){
	return api->reqOrderAction(pInputOrderAction, nRequestID);
}

//配合连接超时计时器检测是否连接超时
void Trader::detectOvertime() {
	bool isCon = api->isConnect();
	if (isCon == false) {
		emit connectFailed();
	}
}
