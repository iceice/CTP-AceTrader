#include "CTPTdSpi.h"
#include "ThostFtdcUserApiStruct.h"
#include "GVAR.h"
#include "qdebug.h"
#include "SubscribeController.h"
#include <algorithm>

using std::make_pair;

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

CTPTdSpi::CTPTdSpi(std::shared_ptr<CTPTdApi> api) {
	ctpTdApi = api;
}


CTPTdSpi::~CTPTdSpi() {
	qDebug() << "~CTPTdSpi";
}

//当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用
void CTPTdSpi::OnFrontConnected() {
	ctpTdApi->setConnect();
	ctpTdApi->login();
}
//登录请求响应
void CTPTdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast) {
	if (pRspInfo->ErrorID == 0) {
		qDebug() << "交易：登录成功";
		tradeDate = pRspUserLogin->TradingDay;
		// 保存会话参数
		trade_front_id = pRspUserLogin->FrontID;
		session_id = pRspUserLogin->SessionID;
		strcpy(order_ref, pRspUserLogin->MaxOrderRef);
		emit tradeLoginSuccess();	//发送登录成功信号
	}
	else {
		qDebug()  << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
		
		
		emit loginFailed(QString::fromLocal8Bit(pRspInfo->ErrorMsg));
	}
}
//1、查询结算信息确认响应
void CTPTdSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast) {
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
		if (pSettlementInfoConfirm == nullptr){
			qDebug() << "今天还没有确定！";
			emit confirmFailed();
		}
		else {
			qDebug() << "确认日期：" << pSettlementInfoConfirm->ConfirmDate;
			qDebug() << "交易日期：" << tradeDate;
			QString lastConfirmDate = pSettlementInfoConfirm->ConfirmDate;
			if (lastConfirmDate == tradeDate) {
				qDebug() << "今天已经确定！";
				emit confirmSuccess();
			}
			else{
				qDebug() << "今天还没有确定！(不为空)";
				emit confirmFailed();
			}
		}

	}
	else {
		qDebug() << "请求查询结算信息确认失败:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//2、请求查询投资者结算结果响应
void CTPTdSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField * pSettlementInfo, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
		COMFIRM_MESSAGE = COMFIRM_MESSAGE + QString::fromLocal8Bit(pSettlementInfo->Content);
		if (bIsLast) {
			qDebug() << "查询投资者结算结果成功！";
			emit querySettlementInfoSuccess();
		}
	}
	else{
		qDebug() << "请求查询投资者结算结果失败:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//3、投资者结算结果确认响应
void CTPTdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
		qDebug() << "投资者结算结果确认成功！";
		emit settlementInfoConfirmSuccess();
	}
	else {
		qDebug() << "投资者结算结果确认失败:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//4、查询全部合约响应
void CTPTdSpi::OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast) {
	QString code = QString::fromLocal8Bit(pInstrument->InstrumentID);
	QString name = QString::fromLocal8Bit(pInstrument->InstrumentName);
	QString inst = QString::fromLocal8Bit(pInstrument->ExchangeID);

	if (inst == "SHFE") {
		SHFE_Instru.insert(make_pair(code, name));
	}
	else if (inst == "CZCE") {
		CZCE_Instru.insert(make_pair(code, name));
	}
	else if (inst == "DCE") {
		DCE_Instru.insert(make_pair(code, name));
	}
	else if (inst == "CFFEX") {
		CFFEX_Instru.insert(make_pair(code, name));
	}
	instruList.insert(make_pair(code, new Instrument(code, name, pInstrument->VolumeMultiple, pInstrument->PriceTick)));
	if (bIsLast) {
		qDebug() << "查询全部合约成功！";
		emit queryInstrumentSuccess();
	}
}
//5、请求查询资金账户响应
void CTPTdSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField * pTradingAccount, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
		ACCOUNT->update(pTradingAccount);
		if (FIRST_FLAG)
			emit queryTradingAccountSuccess();
		else
			emit updateAccount();
	}
	else {
		qDebug() << "请求失败:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//6、请求查询投资者持仓响应
void CTPTdSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField * pInvestorPosition, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
		if (pInvestorPosition != nullptr) {
			QString code = QString::fromLocal8Bit(pInvestorPosition->InstrumentID);
			int v = instruList[code]->VolumeMultiple;
			if (pInvestorPosition->Position != 0) {
				positionInstru.insert(code);
				allPositions.push_back(new Positions(pInvestorPosition, v));
			}
		}
		if (bIsLast) {
			qDebug() << "查询投资者持仓成功！";
			if (FIRST_FLAG)
				emit queryInvestorPositionSuccess();
			else
				emit updatePositon();
		}
	}
	else {
		qDebug() << "请求失败:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//7、请求查询成交响应
void CTPTdSpi::OnRspQryTrade(CThostFtdcTradeField * pTrade, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
		if (pTrade != nullptr) {
			std::remove(pTrade->OrderSysID, pTrade->OrderSysID + 21, ' ');
			QString id = QString::fromLocal8Bit(pTrade->OrderSysID);
			QString code = QString::fromLocal8Bit(pTrade->InstrumentID);
			if (allTrade.find(id) == allTrade.end()) {
				allTrade.insert(make_pair(id, new Trade(id, code)));
			}
			allTrade[id]->update(pTrade);
		}
		if (bIsLast) {
			qDebug() << "查询成交成功！";
			emit queryTradeSuccess();
		}
	}
	else {
		qDebug() << "请求失败:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//8、请求查询报单响应
void CTPTdSpi::OnRspQryOrder(CThostFtdcOrderField * pOrder, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
		if (pOrder != nullptr) {
			std::remove(pOrder->OrderSysID, pOrder->OrderSysID + 21, ' ');
			QString id = QString::fromLocal8Bit(pOrder->OrderSysID);
			QString code = QString::fromLocal8Bit(pOrder->InstrumentID);
			QString this_ref = QString::fromLocal8Bit(pOrder->OrderRef);
			if (id != "") {
				if (allOrder.find(id) == allOrder.end()) {
					allOrder.insert(make_pair(id, new Order(id, code)));
				}
				allOrder[id]->update(pOrder);
			}

		}
		if (bIsLast) {
			qDebug() << "查询报单成功！";
			emit queryOrderSuccess();
		}
	}
	else {
		qDebug() << "请求失败:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}

void CTPTdSpi::OnRtnOrder(CThostFtdcOrderField * pOrder){
	if (FIRST_FLAG) {
		return;
	}
	qDebug() << "=====收到报单应答=====";
	std::remove(pOrder->OrderSysID, pOrder->OrderSysID + 21, ' ');
	QString id = QString::fromLocal8Bit(pOrder->OrderSysID);
	QString code = QString::fromLocal8Bit(pOrder->InstrumentID);
	QString this_ref = QString::fromLocal8Bit(pOrder->OrderRef);
	if (id == "")
		return;

	qDebug() << "id:" << id;
	qDebug() << "code:" << code;
	qDebug() << "ref:" << this_ref;
	
	if (pOrder->OrderStatus == THOST_FTDC_OST_Touched) {
		qDebug() << "已经触发:"<< this_ref;
		//找到止损单对应的平仓单的ref
		std::map<QString, QString>::iterator it = actionOrder.find(this_ref);
		if (it != actionOrder.end()) {
			//撤销平仓单
			emit startAction(it->second);
		}
		//return;
	}

	if (allOrder.find(id) == allOrder.end())
		allOrder.insert(make_pair(id, new Order(id, code)));
	allOrder[id]->update(pOrder);

	emit updateOrder();

	Ref_SysID.insert(make_pair(this_ref, id));
	
	if ( (pOrder->CombOffsetFlag[0] == THOST_FTDC_OF_CloseToday) && (pOrder->OrderStatus == THOST_FTDC_OST_Canceled) )
	{
		//撤销的平仓单，如果afterClose中，需要平仓止损
		for (auto iter = afterClose.begin(); iter != afterClose.end(); iter++)
			if (*iter == this_ref)
				emit startClose(this_ref);


		
		//部分止损的单的时间标志是立即完成否则撤销
		if (pOrder->TimeCondition == THOST_FTDC_TC_IOC)
		{
			OrderParameter *op = orderPara[this_ref];
			if (pOrder->Direction == THOST_FTDC_D_Buy)
				op->stop_price += instruList[code]->PriceTick;
			else
				op->stop_price -= instruList[code]->PriceTick;
			
			op->num = pOrder->VolumeTotal;
			emit startClose(this_ref);
		}
	}
}

void CTPTdSpi::OnRtnTrade(CThostFtdcTradeField * pTrade){
	if (FIRST_FLAG)
		return;
	qDebug() << "=====收到成交应答=====";
	std::remove(pTrade->OrderSysID, pTrade->OrderSysID + 21, ' ');
	QString id = QString::fromLocal8Bit(pTrade->OrderSysID);
	QString code = QString::fromLocal8Bit(pTrade->InstrumentID);
	QString this_ref = QString::fromLocal8Bit(pTrade->OrderRef);
	qDebug() << "id:" << id;
	qDebug() << "code:" << code;
	qDebug() << "ref:" << this_ref;
	
	//如果是开仓单（需要平仓）
	if (pTrade->OffsetFlag == THOST_FTDC_OF_Open) {
		//更新参数
		OrderParameter *op = orderPara[this_ref];
		if (op != nullptr) {
			op->update(pTrade);
			emit startClose(this_ref);
		}	
		
	}
	//更新成交列表
	if (allTrade.find(id) == allTrade.end())
		allTrade.insert(make_pair(id, new Trade(id, code)));
	allTrade[id]->update(pTrade);



	emit updateTrade();
}

void CTPTdSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField * pInputOrder, CThostFtdcRspInfoField * pRspInfo){
	qDebug() << "报单录入错误：" << pInputOrder->OrderRef;
	qDebug() << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
}

void CTPTdSpi::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField * pErrorConditionalOrder){
	qDebug() << "====条件单错误：===";
	qDebug() << QString::fromLocal8Bit(pErrorConditionalOrder->ErrorMsg);
}

//释放资源,必须先在api中对spi解引用
void CTPTdSpi::release() {
	ctpTdApi = nullptr;
}
