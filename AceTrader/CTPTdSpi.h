#pragma once
#include "ThostFtdcTraderApi.h"
#include "CTPTdApi.h"
#include <QObject>

class CTPTdSpi :public QObject, public CThostFtdcTraderSpi {
	Q_OBJECT
public:
	CTPTdSpi(std::shared_ptr<CTPTdApi> api);
	~CTPTdSpi();
	//���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷���������
	void OnFrontConnected() override;
	//��¼������Ӧ
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//1����ѯ������Ϣȷ����Ӧ
	void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//2�������ѯͶ���߽�������Ӧ
	void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//3��Ͷ���߽�����ȷ����Ӧ
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//4����ѯȫ����Լ��Ӧ
	void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);	
	//5�������ѯ�ʽ��˻���Ӧ
	void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//6�������ѯͶ���ֲ߳���Ӧ
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//7�������ѯ�ɽ���Ӧ
	void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//8�������ѯ������Ӧ
	void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//1������֪ͨ
	void OnRtnOrder(CThostFtdcOrderField *pOrder);
	//2���ɽ�֪ͨ
	void OnRtnTrade(CThostFtdcTradeField *pTrade);

	void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
	void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);
	//�ͷ���Դ
	void release();
private:
	std::shared_ptr<CTPTdApi> ctpTdApi;
signals:
	void tradeLoginSuccess();	//��½�ɹ��ź�
	void confirmSuccess();               //1�������Ѿ�ȷ��
	void confirmFailed();                //1������û��ȷ��
	void querySettlementInfoSuccess();   //2����ѯȷ����Ϣ�ɹ�
	void settlementInfoConfirmSuccess(); //3��Ͷ���߽�����ȷ�ϳɹ�
	void queryInstrumentSuccess();       //4����ѯ��Լ�ɹ��ź�
	void queryTradingAccountSuccess();   //5����ѯ�ʽ��˻��ɹ���bool�Ƿ��һ�Σ�
	void queryInvestorPositionSuccess(); //6����ѯ��ѯͶ���ֲֳ߳ɹ�
	void queryTradeSuccess();            //7����ѯ�ɽ��ɹ�
	void queryOrderSuccess();            //8����ѯ�����ɹ�
	void updateOrder();
	void updateTrade();
	void updateAccount();
	void updatePositon();
	void startClose(QString);
	void startAction(QString);
	void loginFailed(QString);
};

