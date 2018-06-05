#include "CTPMdSpi.h"
#include "ThostFtdcUserApiStruct.h"
#include "GVAR.h"
#include <qdebug.h>
#include <qdatetime.h>
#include <mutex>
#include <iostream>
using std::shared_ptr;
using std::make_shared;
using std::set;
using std::map;
using std::make_pair;
using std::once_flag;

//记录交易日的地方只执行一次
once_flag ONCEFLAG;


CTPMdSpi::CTPMdSpi(shared_ptr<CTPMdApi> api) {
	ctpMdApi = api;
}

CTPMdSpi::~CTPMdSpi() {
	qDebug() << "~CTPMdSpi";
}

//当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用
void CTPMdSpi::OnFrontConnected() {
	ctpMdApi->setConnect();
	ctpMdApi->login();		//连接成功后马上登陆
}

//登录请求响应
void CTPMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (pRspInfo->ErrorID == 0) {
		qDebug() << "行情：登录成功";
		emit loginSuccess();	//发送登录成功信号
	}
	else {
		qDebug() << "行情：登录失败:" << pRspInfo->ErrorID<<" "<<QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}

}

//行情回报响应
void CTPMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
	//更新全局变量的合约信息
	QString code(pDepthMarketData->InstrumentID);
	instruList[code]->update(pDepthMarketData);
}



//释放资源,必须先在api中对spi解引用
void CTPMdSpi::release() {
	ctpMdApi = nullptr;
}