#include "QueryController.h"
#include "qdebug.h"
#include <memory>

using std::shared_ptr;

QueryController::QueryController() = default;

void QueryController::reset(){
	trader = nullptr;
}

void QueryController::setTrader(std::shared_ptr<Trader> t){
	trader = t;

	querySettlementInfoTimer = new QTimer(this);
	showConfirmDialogTimer = new QTimer(this);
	queryInstrumentsTimer = new QTimer(this);
	queryTradingAccountTimer = new QTimer(this);
	queryInvestorPositionTimer = new QTimer(this);
	queryTradeTimer = new QTimer(this);
	queryOrderTimer = new QTimer(this);
	connect(querySettlementInfoTimer, SIGNAL(timeout()), this, SLOT(querySettlementInfo()));
	connect(showConfirmDialogTimer, SIGNAL(timeout()), this, SIGNAL(querySettlementInfoSuccess()));
	connect(queryInstrumentsTimer, SIGNAL(timeout()), this, SLOT(queryInstruments()));
	connect(queryTradingAccountTimer, SIGNAL(timeout()), this, SLOT(queryTradingAccount()));
	connect(queryInvestorPositionTimer, SIGNAL(timeout()), this, SLOT(queryInvestorPosition()));
	connect(queryTradeTimer, SIGNAL(timeout()), this, SLOT(queryTrade()));
	connect(queryOrderTimer, SIGNAL(timeout()), this, SLOT(queryOrder()));

	//connect(trader.get(), SIGNAL(updateTrade()), this, SLOT(startqueryTradingAccountTimer()));
	connect(trader.get(), SIGNAL(updateAccount()), this, SIGNAL(updateAccount()));
	
	connect(trader.get(), SIGNAL(updateTrade()), this, SLOT(startqueryInvestorPositionTimer()));
	connect(trader.get(), SIGNAL(updatePositon()), this, SIGNAL(updatePositon()));

}

/******************************************槽函数*******************************************/
void QueryController::startquerySettlementInfoTimer() {
	querySettlementInfoTimer->start(1000);
}

void QueryController::startshowConfirmDialogTimer() {
	showConfirmDialogTimer->start(1000);
}

void QueryController::startqueryInstrumentsTimer(){
	queryInstrumentsTimer->start(1000);
}

void QueryController::startqueryTradingAccountTimer(){
	queryTradingAccountTimer->start(1000);
}

void QueryController::startqueryInvestorPositionTimer(){
	queryInvestorPositionTimer->start(1000);
}

void QueryController::startqueryTradeTimer(){
	queryTradeTimer->start(1000);
}

void QueryController::startqueryOrderTimer(){
	queryOrderTimer->start(1000);
}

//1、查询是否已经做了确认
void QueryController::querySettlementInfoConfirm() {
	CThostFtdcQrySettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());
	int rt = trader->reqQrySettlementInfoConfirm(&req, ++requestID);
	emit querySignal("查询结算信息...");
	if (!rt) {
		qDebug() << ">>>>>>发送查询结算信息确认请求成功" << endl;
	}
	else
		qDebug() << "--->>>发送查询结算信息确认请求失败" << endl;
	//已经结算，开始查询账户资金
	connect(trader.get(), SIGNAL(confirmSuccess()), this, SLOT(startqueryInstrumentsTimer()));
	//没有结算，开始请求结算信息
	connect(trader.get(), SIGNAL(confirmFailed()), this, SLOT(startquerySettlementInfoTimer()));

}
//2、请求查询确认单
void QueryController::querySettlementInfo() {
	CThostFtdcQrySettlementInfoField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());
	int rt = trader->reqQrySettlementInfo(&req, ++requestID);
	if (!rt) {
		querySettlementInfoTimer->stop();
		qDebug() << ">>>>>>发送投资者结算结果请求成功" << endl;
	}
	else
		qDebug() << "--->>>发送投资者结算结果请求失败" << endl;

	connect(trader.get(), SIGNAL(querySettlementInfoSuccess()), this, SLOT(startshowConfirmDialogTimer()));
}

//3、投资者结算结果确认
void QueryController::settlementInfoConfirm(){
	showConfirmDialogTimer->stop();
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());
	int rt = trader->reqSettlementInfoConfirm(&req, ++requestID);
	if (!rt) 
		qDebug() << ">>>>>>发送投资者结算结果确认请求成功" << endl;
	else
		qDebug() << "--->>>发送投资者结算结果确认请求失败" << endl;

	connect(trader.get(), SIGNAL(settlementInfoConfirmSuccess()), this, SLOT(startqueryInstrumentsTimer()));
}

//4、查询合约
void QueryController::queryInstruments() {
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));

	int rt = trader->reqQryInstrument(&req, ++requestID);
	emit querySignal("查询合约信息...");
	if (!rt) {
		queryInstrumentsTimer->stop();
		qDebug() << ">>>>>>发送查询合约请求成功" << endl;
	}
	else
		qDebug() << "--->>>发送查询合约请求失败" << endl;

	connect(trader.get(), SIGNAL(queryInstrumentSuccess()), this, SLOT(startqueryTradingAccountTimer()));
}

//5、请求查询资金账户
void QueryController::queryTradingAccount(){
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());
	int rt = trader->reqQryTradingAccount(&req, ++requestID);
	if (FIRST_FLAG)
		emit querySignal("查询资金信息...");
	if (!rt) {
		if(FIRST_FLAG)
			queryTradingAccountTimer->stop();
		//qDebug() << ">>>>>>发送查询资金账户请求成功" << endl;
	}
	else
		qDebug() << "--->>>发送查询资金账户请求失败" << endl;
	connect(trader.get(), SIGNAL(queryTradingAccountSuccess()), this, SLOT(startqueryInvestorPositionTimer()));
	connect(trader.get(), SIGNAL(queryTradingAccountSuccess()), this, SIGNAL(queryTradingAccountSuccess()));
}

//6、请求查询投资者持仓
void QueryController::queryInvestorPosition(){
	//查询前，清空
	allPositions.clear();
	positionInstru.clear();

	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());

	int rt = trader->reqQryInvestorPosition(&req, ++requestID);
	if (FIRST_FLAG)
		emit querySignal("查询持仓信息...");
	if (!rt) {
		queryInvestorPositionTimer->stop();
		qDebug() << ">>>>>>发送查询投资者持仓请求成功" << endl;
	}
	else
		qDebug() << "--->>>发送查询投资者持仓请求失败" << endl;
	connect(trader.get(), SIGNAL(queryInvestorPositionSuccess()), this, SLOT(startqueryTradeTimer()));
	connect(trader.get(), SIGNAL(queryInvestorPositionSuccess()), this, SIGNAL(queryInvestorPositionSuccess()));
}

//7、请求查询成交
void QueryController::queryTrade(){
	CThostFtdcQryTradeField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());

	int rt = trader->reqQryTrade(&req, ++requestID);
	if (FIRST_FLAG)
		emit querySignal("查询成交信息...");
	if (!rt) {
		queryTradeTimer->stop();
		qDebug() << ">>>>>>发送查询成交请求成功" << endl;
	}
	else
		qDebug() << "--->>>发送查询成交请求失败" << endl;
	connect(trader.get(), SIGNAL(queryTradeSuccess()), this, SLOT(startqueryOrderTimer()));
	connect(trader.get(), SIGNAL(queryTradeSuccess()), this, SIGNAL(queryTradeSuccess()));
}
//8、请求查询报单
void QueryController::queryOrder(){
	CThostFtdcQryOrderField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());

	int rt = trader->reqQryOrder(&req, ++requestID);
	if (FIRST_FLAG)
		emit querySignal("查询委托信息...");
	if (!rt) {
		queryOrderTimer->stop();
		qDebug() << ">>>>>>发送查询报单请求成功" << endl;
	}
	else
		qDebug() << "--->>>发送查询报单请求失败" << endl;
	connect(trader.get(), SIGNAL(queryOrderSuccess()), this, SLOT(allSuccess()));
	connect(trader.get(), SIGNAL(queryOrderSuccess()), this, SIGNAL(queryOrderSuccess()));
}

void QueryController::allSuccess(){
	if (FIRST_FLAG)
		emit querySignal("");
	FIRST_FLAG = false;
	queryTradingAccountTimer->start(2000);
}



