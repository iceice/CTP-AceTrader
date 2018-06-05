#pragma once

#include "ThostFtdcMdApi.h"
#include "CTPMdApi.h"
//#include "Recorder.h"
#include <qobject.h>
#include <qstring.h>
#include <memory>
#include <set>
#include <map>

class CTPMdSpi :public QObject, public CThostFtdcMdSpi {
	Q_OBJECT
public:
	CTPMdSpi(std::shared_ptr<CTPMdApi> api);
	~CTPMdSpi();
	//���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷���������
	void OnFrontConnected() override;

	//��¼������Ӧ
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	//����ر���Ӧ
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) override;

	//�ͷ���Դ
	void release();
private:
	std::shared_ptr<CTPMdApi> ctpMdApi;
signals:
	void loginSuccess();	//��½�ɹ��ź�
};
