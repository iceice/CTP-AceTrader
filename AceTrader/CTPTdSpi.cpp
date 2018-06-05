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

//���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷���������
void CTPTdSpi::OnFrontConnected() {
	ctpTdApi->setConnect();
	ctpTdApi->login();
}
//��¼������Ӧ
void CTPTdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast) {
	if (pRspInfo->ErrorID == 0) {
		qDebug() << "���ף���¼�ɹ�";
		tradeDate = pRspUserLogin->TradingDay;
		// ����Ự����
		trade_front_id = pRspUserLogin->FrontID;
		session_id = pRspUserLogin->SessionID;
		strcpy(order_ref, pRspUserLogin->MaxOrderRef);
		emit tradeLoginSuccess();	//���͵�¼�ɹ��ź�
	}
	else {
		qDebug()  << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
		
		
		emit loginFailed(QString::fromLocal8Bit(pRspInfo->ErrorMsg));
	}
}
//1����ѯ������Ϣȷ����Ӧ
void CTPTdSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast) {
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
		if (pSettlementInfoConfirm == nullptr){
			qDebug() << "���컹û��ȷ����";
			emit confirmFailed();
		}
		else {
			qDebug() << "ȷ�����ڣ�" << pSettlementInfoConfirm->ConfirmDate;
			qDebug() << "�������ڣ�" << tradeDate;
			QString lastConfirmDate = pSettlementInfoConfirm->ConfirmDate;
			if (lastConfirmDate == tradeDate) {
				qDebug() << "�����Ѿ�ȷ����";
				emit confirmSuccess();
			}
			else{
				qDebug() << "���컹û��ȷ����(��Ϊ��)";
				emit confirmFailed();
			}
		}

	}
	else {
		qDebug() << "�����ѯ������Ϣȷ��ʧ��:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//2�������ѯͶ���߽�������Ӧ
void CTPTdSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField * pSettlementInfo, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
		COMFIRM_MESSAGE = COMFIRM_MESSAGE + QString::fromLocal8Bit(pSettlementInfo->Content);
		if (bIsLast) {
			qDebug() << "��ѯͶ���߽������ɹ���";
			emit querySettlementInfoSuccess();
		}
	}
	else{
		qDebug() << "�����ѯͶ���߽�����ʧ��:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//3��Ͷ���߽�����ȷ����Ӧ
void CTPTdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
		qDebug() << "Ͷ���߽�����ȷ�ϳɹ���";
		emit settlementInfoConfirmSuccess();
	}
	else {
		qDebug() << "Ͷ���߽�����ȷ��ʧ��:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//4����ѯȫ����Լ��Ӧ
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
		qDebug() << "��ѯȫ����Լ�ɹ���";
		emit queryInstrumentSuccess();
	}
}
//5�������ѯ�ʽ��˻���Ӧ
void CTPTdSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField * pTradingAccount, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
		ACCOUNT->update(pTradingAccount);
		if (FIRST_FLAG)
			emit queryTradingAccountSuccess();
		else
			emit updateAccount();
	}
	else {
		qDebug() << "����ʧ��:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//6�������ѯͶ���ֲ߳���Ӧ
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
			qDebug() << "��ѯͶ���ֲֳ߳ɹ���";
			if (FIRST_FLAG)
				emit queryInvestorPositionSuccess();
			else
				emit updatePositon();
		}
	}
	else {
		qDebug() << "����ʧ��:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//7�������ѯ�ɽ���Ӧ
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
			qDebug() << "��ѯ�ɽ��ɹ���";
			emit queryTradeSuccess();
		}
	}
	else {
		qDebug() << "����ʧ��:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}
//8�������ѯ������Ӧ
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
			qDebug() << "��ѯ�����ɹ���";
			emit queryOrderSuccess();
		}
	}
	else {
		qDebug() << "����ʧ��:" << pRspInfo->ErrorID << " " << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}
}

void CTPTdSpi::OnRtnOrder(CThostFtdcOrderField * pOrder){
	if (FIRST_FLAG) {
		return;
	}
	qDebug() << "=====�յ�����Ӧ��=====";
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
		qDebug() << "�Ѿ�����:"<< this_ref;
		//�ҵ�ֹ�𵥶�Ӧ��ƽ�ֵ���ref
		std::map<QString, QString>::iterator it = actionOrder.find(this_ref);
		if (it != actionOrder.end()) {
			//����ƽ�ֵ�
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
		//������ƽ�ֵ������afterClose�У���Ҫƽ��ֹ��
		for (auto iter = afterClose.begin(); iter != afterClose.end(); iter++)
			if (*iter == this_ref)
				emit startClose(this_ref);


		
		//����ֹ��ĵ���ʱ���־��������ɷ�����
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
	qDebug() << "=====�յ��ɽ�Ӧ��=====";
	std::remove(pTrade->OrderSysID, pTrade->OrderSysID + 21, ' ');
	QString id = QString::fromLocal8Bit(pTrade->OrderSysID);
	QString code = QString::fromLocal8Bit(pTrade->InstrumentID);
	QString this_ref = QString::fromLocal8Bit(pTrade->OrderRef);
	qDebug() << "id:" << id;
	qDebug() << "code:" << code;
	qDebug() << "ref:" << this_ref;
	
	//����ǿ��ֵ�����Ҫƽ�֣�
	if (pTrade->OffsetFlag == THOST_FTDC_OF_Open) {
		//���²���
		OrderParameter *op = orderPara[this_ref];
		if (op != nullptr) {
			op->update(pTrade);
			emit startClose(this_ref);
		}	
		
	}
	//���³ɽ��б�
	if (allTrade.find(id) == allTrade.end())
		allTrade.insert(make_pair(id, new Trade(id, code)));
	allTrade[id]->update(pTrade);



	emit updateTrade();
}

void CTPTdSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField * pInputOrder, CThostFtdcRspInfoField * pRspInfo){
	qDebug() << "����¼�����" << pInputOrder->OrderRef;
	qDebug() << QString::fromLocal8Bit(pRspInfo->ErrorMsg);
}

void CTPTdSpi::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField * pErrorConditionalOrder){
	qDebug() << "====����������===";
	qDebug() << QString::fromLocal8Bit(pErrorConditionalOrder->ErrorMsg);
}

//�ͷ���Դ,��������api�ж�spi������
void CTPTdSpi::release() {
	ctpTdApi = nullptr;
}
