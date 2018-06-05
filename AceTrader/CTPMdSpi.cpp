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

//��¼�����յĵط�ִֻ��һ��
once_flag ONCEFLAG;


CTPMdSpi::CTPMdSpi(shared_ptr<CTPMdApi> api) {
	ctpMdApi = api;
}

CTPMdSpi::~CTPMdSpi() {
	qDebug() << "~CTPMdSpi";
}

//���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷���������
void CTPMdSpi::OnFrontConnected() {
	ctpMdApi->setConnect();
	ctpMdApi->login();		//���ӳɹ������ϵ�½
}

//��¼������Ӧ
void CTPMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (pRspInfo->ErrorID == 0) {
		qDebug() << "���飺��¼�ɹ�";
		emit loginSuccess();	//���͵�¼�ɹ��ź�
	}
	else {
		qDebug() << "���飺��¼ʧ��:" << pRspInfo->ErrorID<<" "<<QString::fromLocal8Bit(pRspInfo->ErrorMsg);
	}

}

//����ر���Ӧ
void CTPMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
	//����ȫ�ֱ����ĺ�Լ��Ϣ
	QString code(pDepthMarketData->InstrumentID);
	instruList[code]->update(pDepthMarketData);
}



//�ͷ���Դ,��������api�ж�spi������
void CTPMdSpi::release() {
	ctpMdApi = nullptr;
}