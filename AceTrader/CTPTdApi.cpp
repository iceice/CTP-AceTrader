#include "CTPTdApi.h"
#include "qdebug.h"
#include "string.h"
#include "GVAR.h"
using std::shared_ptr;

CTPTdApi::CTPTdApi(){
	ctpTdApi = CThostFtdcTraderApi::CreateFtdcTraderApi("./ctp_temp_file/");
	connecFlag = false;
}


CTPTdApi::~CTPTdApi(){
	qDebug() << "ctpTdApi->Release()";
	if (ctpTdApi != nullptr) {
		ctpTdApi->RegisterSpi(NULL);
		ctpTdApi->Release();
		ctpTdApi = NULL;

	}
}

/************************************public函数**************************************************************/
void CTPTdApi::registerSpi(std::shared_ptr<CThostFtdcTraderSpi> spi){
	ctpTdSpi = spi;
	ctpTdApi->RegisterSpi(ctpTdSpi.get());
}

void CTPTdApi::login(){
	CThostFtdcReqUserLoginField loginField;
	strcpy(loginField.BrokerID, BROKER.toStdString().c_str());
	strcpy(loginField.UserID, USER_NAME.toStdString().c_str());
	strcpy(loginField.Password, PASSWORD.toStdString().c_str());
	ctpTdApi->ReqUserLogin(&loginField, 0);
}

void CTPTdApi::release(){
	ctpTdApi->Release();
	ctpTdApi = nullptr;
}

int CTPTdApi::reqQrySettlementInfo(CThostFtdcQrySettlementInfoField * pQrySettlementInfo, int nRequestID){
	return ctpTdApi->ReqQrySettlementInfo(pQrySettlementInfo, nRequestID);
}

int CTPTdApi::reqQryInstrument(CThostFtdcQryInstrumentField * pQryInstrument, int nRequestID){
	return ctpTdApi->ReqQryInstrument(pQryInstrument, nRequestID);
}

int CTPTdApi::reqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField * pQrySettlementInfoConfirm, int nRequestID){
	return ctpTdApi->ReqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, nRequestID);
}

int CTPTdApi::reqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, int nRequestID){
	return ctpTdApi->ReqSettlementInfoConfirm(pSettlementInfoConfirm, nRequestID);
}

int CTPTdApi::reqQryTradingAccount(CThostFtdcQryTradingAccountField * pQryTradingAccount, int nRequestID){
	return ctpTdApi->ReqQryTradingAccount(pQryTradingAccount, nRequestID);
}

int CTPTdApi::reqQryInvestorPosition(CThostFtdcQryInvestorPositionField * pQryInvestorPosition, int nRequestID){
	return ctpTdApi->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
}

int CTPTdApi::reqQryTrade(CThostFtdcQryTradeField * pQryTrade, int nRequestID){
	return ctpTdApi->ReqQryTrade(pQryTrade, nRequestID);
}

int CTPTdApi::reqQryOrder(CThostFtdcQryOrderField * pQryOrder, int nRequestID){
	return ctpTdApi->ReqQryOrder(pQryOrder, nRequestID);
}

int CTPTdApi::reqOrderInsert(CThostFtdcInputOrderField * pInputOrder, int nRequestID){
	return ctpTdApi->ReqOrderInsert(pInputOrder, nRequestID);
}

int CTPTdApi::reqOrderAction(CThostFtdcInputOrderActionField * pInputOrderAction, int nRequestID){
	return ctpTdApi->ReqOrderAction(pInputOrderAction, nRequestID);
}

bool CTPTdApi::isConnect(){
	return connecFlag;
}

void CTPTdApi::setConnect(){
	connecFlag = true;
}

void CTPTdApi::connectServer(){
	char address[100];
	strcpy(address, TD_FRONT_ADDRESS.toStdString().c_str());
	ctpTdApi->RegisterFront(address);
	ctpTdApi->SubscribePublicTopic(THOST_TERT_RESTART);		// 订阅公共流: RESTART, RESUME, QUICK
	ctpTdApi->SubscribePrivateTopic(THOST_TERT_RESTART);		// 订阅私有流
	ctpTdApi->Init();
	//ctpTdApi->Join();
}
