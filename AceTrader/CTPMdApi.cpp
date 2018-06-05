#include "GVAR.h"
#include "CTPMdApi.h"
#include <qdebug.h>
#include <string>
using std::string;
using std::shared_ptr;
using std::vector;

CTPMdApi::CTPMdApi() {
	ctpMdApi = CThostFtdcMdApi::CreateFtdcMdApi("./ctp_temp_file/");
	connectFlag = false;
}

CTPMdApi::~CTPMdApi() {
	qDebug() << "ctpMdApi->Release()";
	if (ctpMdApi != nullptr) {
		ctpMdApi->RegisterSpi(NULL);
		ctpMdApi->Release();
		ctpMdApi = NULL;
	}
}

/************************************public����**************************************************************/

void CTPMdApi::registerSpi(shared_ptr<CThostFtdcMdSpi> spi) {
	ctpMdSpi = spi;
	ctpMdApi->RegisterSpi(ctpMdSpi.get());
}

void CTPMdApi::login() {
	CThostFtdcReqUserLoginField loginField;
	strcpy(loginField.BrokerID, BROKER.toStdString().c_str());
	strcpy(loginField.UserID, USER_NAME.toStdString().c_str());
	strcpy(loginField.Password, PASSWORD.toStdString().c_str());
	ctpMdApi->ReqUserLogin(&loginField, 0);
}

void CTPMdApi::release() {
	ctpMdApi->Release();
	ctpMdApi = nullptr;
}

int CTPMdApi::subscribeData(char *ppInstrumentID[], int nCount) {
	return ctpMdApi->SubscribeMarketData(ppInstrumentID, nCount);
}

int CTPMdApi::unsubscribeData(char *ppInstrumentID[], int nCount) {
	return ctpMdApi->UnSubscribeMarketData(ppInstrumentID, nCount);
}

bool CTPMdApi::isConnect() {
	return connectFlag;
}

void CTPMdApi::setConnect() {
	connectFlag = true;
}

//ע��ǰ�û�����ʼ��Api
void CTPMdApi::connectServer() {
	//ע��ǰ�û�
	char address[100];
	strcpy(address, MD_FRONT_ADDRESS.toStdString().c_str());
	ctpMdApi->RegisterFront(address);
	//��ʼ��Api
	ctpMdApi->Init();
}

