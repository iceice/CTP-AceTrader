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

/******************************************�ۺ���*******************************************/
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

//1����ѯ�Ƿ��Ѿ�����ȷ��
void QueryController::querySettlementInfoConfirm() {
	CThostFtdcQrySettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());
	int rt = trader->reqQrySettlementInfoConfirm(&req, ++requestID);
	emit querySignal("��ѯ������Ϣ...");
	if (!rt) {
		qDebug() << ">>>>>>���Ͳ�ѯ������Ϣȷ������ɹ�" << endl;
	}
	else
		qDebug() << "--->>>���Ͳ�ѯ������Ϣȷ������ʧ��" << endl;
	//�Ѿ����㣬��ʼ��ѯ�˻��ʽ�
	connect(trader.get(), SIGNAL(confirmSuccess()), this, SLOT(startqueryInstrumentsTimer()));
	//û�н��㣬��ʼ���������Ϣ
	connect(trader.get(), SIGNAL(confirmFailed()), this, SLOT(startquerySettlementInfoTimer()));

}
//2�������ѯȷ�ϵ�
void QueryController::querySettlementInfo() {
	CThostFtdcQrySettlementInfoField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());
	int rt = trader->reqQrySettlementInfo(&req, ++requestID);
	if (!rt) {
		querySettlementInfoTimer->stop();
		qDebug() << ">>>>>>����Ͷ���߽���������ɹ�" << endl;
	}
	else
		qDebug() << "--->>>����Ͷ���߽���������ʧ��" << endl;

	connect(trader.get(), SIGNAL(querySettlementInfoSuccess()), this, SLOT(startshowConfirmDialogTimer()));
}

//3��Ͷ���߽�����ȷ��
void QueryController::settlementInfoConfirm(){
	showConfirmDialogTimer->stop();
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());
	int rt = trader->reqSettlementInfoConfirm(&req, ++requestID);
	if (!rt) 
		qDebug() << ">>>>>>����Ͷ���߽�����ȷ������ɹ�" << endl;
	else
		qDebug() << "--->>>����Ͷ���߽�����ȷ������ʧ��" << endl;

	connect(trader.get(), SIGNAL(settlementInfoConfirmSuccess()), this, SLOT(startqueryInstrumentsTimer()));
}

//4����ѯ��Լ
void QueryController::queryInstruments() {
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));

	int rt = trader->reqQryInstrument(&req, ++requestID);
	emit querySignal("��ѯ��Լ��Ϣ...");
	if (!rt) {
		queryInstrumentsTimer->stop();
		qDebug() << ">>>>>>���Ͳ�ѯ��Լ����ɹ�" << endl;
	}
	else
		qDebug() << "--->>>���Ͳ�ѯ��Լ����ʧ��" << endl;

	connect(trader.get(), SIGNAL(queryInstrumentSuccess()), this, SLOT(startqueryTradingAccountTimer()));
}

//5�������ѯ�ʽ��˻�
void QueryController::queryTradingAccount(){
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());
	int rt = trader->reqQryTradingAccount(&req, ++requestID);
	if (FIRST_FLAG)
		emit querySignal("��ѯ�ʽ���Ϣ...");
	if (!rt) {
		if(FIRST_FLAG)
			queryTradingAccountTimer->stop();
		//qDebug() << ">>>>>>���Ͳ�ѯ�ʽ��˻�����ɹ�" << endl;
	}
	else
		qDebug() << "--->>>���Ͳ�ѯ�ʽ��˻�����ʧ��" << endl;
	connect(trader.get(), SIGNAL(queryTradingAccountSuccess()), this, SLOT(startqueryInvestorPositionTimer()));
	connect(trader.get(), SIGNAL(queryTradingAccountSuccess()), this, SIGNAL(queryTradingAccountSuccess()));
}

//6�������ѯͶ���ֲ߳�
void QueryController::queryInvestorPosition(){
	//��ѯǰ�����
	allPositions.clear();
	positionInstru.clear();

	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());

	int rt = trader->reqQryInvestorPosition(&req, ++requestID);
	if (FIRST_FLAG)
		emit querySignal("��ѯ�ֲ���Ϣ...");
	if (!rt) {
		queryInvestorPositionTimer->stop();
		qDebug() << ">>>>>>���Ͳ�ѯͶ���ֲ߳�����ɹ�" << endl;
	}
	else
		qDebug() << "--->>>���Ͳ�ѯͶ���ֲ߳�����ʧ��" << endl;
	connect(trader.get(), SIGNAL(queryInvestorPositionSuccess()), this, SLOT(startqueryTradeTimer()));
	connect(trader.get(), SIGNAL(queryInvestorPositionSuccess()), this, SIGNAL(queryInvestorPositionSuccess()));
}

//7�������ѯ�ɽ�
void QueryController::queryTrade(){
	CThostFtdcQryTradeField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());

	int rt = trader->reqQryTrade(&req, ++requestID);
	if (FIRST_FLAG)
		emit querySignal("��ѯ�ɽ���Ϣ...");
	if (!rt) {
		queryTradeTimer->stop();
		qDebug() << ">>>>>>���Ͳ�ѯ�ɽ�����ɹ�" << endl;
	}
	else
		qDebug() << "--->>>���Ͳ�ѯ�ɽ�����ʧ��" << endl;
	connect(trader.get(), SIGNAL(queryTradeSuccess()), this, SLOT(startqueryOrderTimer()));
	connect(trader.get(), SIGNAL(queryTradeSuccess()), this, SIGNAL(queryTradeSuccess()));
}
//8�������ѯ����
void QueryController::queryOrder(){
	CThostFtdcQryOrderField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());

	int rt = trader->reqQryOrder(&req, ++requestID);
	if (FIRST_FLAG)
		emit querySignal("��ѯί����Ϣ...");
	if (!rt) {
		queryOrderTimer->stop();
		qDebug() << ">>>>>>���Ͳ�ѯ��������ɹ�" << endl;
	}
	else
		qDebug() << "--->>>���Ͳ�ѯ��������ʧ��" << endl;
	connect(trader.get(), SIGNAL(queryOrderSuccess()), this, SLOT(allSuccess()));
	connect(trader.get(), SIGNAL(queryOrderSuccess()), this, SIGNAL(queryOrderSuccess()));
}

void QueryController::allSuccess(){
	if (FIRST_FLAG)
		emit querySignal("");
	FIRST_FLAG = false;
	queryTradingAccountTimer->start(2000);
}



