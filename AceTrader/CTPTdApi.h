#pragma once

#include "ThostFtdcTraderApi.h"
#include "GVAR.h"
#include <QObject>
#include <memory>

class CTPTdApi:public QObject{
	Q_OBJECT
public:
	CTPTdApi();
	~CTPTdApi();
	void registerSpi(std::shared_ptr<CThostFtdcTraderSpi> spi);
	void login();
	void release();

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

	bool isConnect();
	//����api��״̬��apiһ����ʼ�������������Ͳ��ٶϿ������һ����ʼ������״̬���ž�Ϊ���Ҳ���
	void setConnect();
	//ע��ǰ�û�����ʼ��Api,�ú�����Ҫͨ���̼߳�ӵ��ã�������ֱ�ӵ���
	void connectServer();
private:
	CThostFtdcTraderApi * ctpTdApi;
	std::shared_ptr<CThostFtdcTraderSpi> ctpTdSpi;
	bool connecFlag;
};

