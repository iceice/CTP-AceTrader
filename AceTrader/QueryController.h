#pragma once
#include <QObject>
#include <memory>
#include "Trader.h"
using std::shared_ptr;

class QueryController :public QObject{
	Q_OBJECT
public:
	QueryController();
	void reset(); //�ָ���ʼ״̬
	void setTrader(std::shared_ptr<Trader> t);
	
	public slots:
	void startquerySettlementInfoTimer();
	void startshowConfirmDialogTimer();
	void startqueryInstrumentsTimer();
	void startqueryTradingAccountTimer();
	void startqueryInvestorPositionTimer();
	void startqueryTradeTimer();
	void startqueryOrderTimer();

	void querySettlementInfoConfirm();          //1����ѯ�Ƿ��Ѿ�����ȷ��
	void querySettlementInfo();                 //2�������ѯȷ�ϵ�
	void settlementInfoConfirm();               //3��Ͷ���߽�����ȷ��
	void queryInstruments();                    //4����ѯ��Լ
	void queryTradingAccount();                 //5�������ѯ�ʽ��˻�
	void queryInvestorPosition();               //6�������ѯͶ���ֲ߳�
	void queryTrade();                          //7�������ѯ�ɽ�
	void queryOrder();                          //8�������ѯ����
	void allSuccess();

private:
	std::shared_ptr<Trader> trader;
	QTimer *querySettlementInfoTimer;          //��ѯȷ����Ϣ����ʱ
	QTimer *showConfirmDialogTimer;            //չʾȷ����Ϣ����ʱ
	QTimer *queryInstrumentsTimer;             //��ѯ��Լ����ʱ
	QTimer *queryTradingAccountTimer;          //��ѯ�˻��ʽ𵹼�ʱ
	QTimer *queryInvestorPositionTimer;        //��ѯͶ���ֲֵ߳���ʱ
	QTimer *queryTradeTimer;                   //�����ѯ�ɽ�����ʱ
	QTimer *queryOrderTimer;                   //�����ѯ��������ʱ
	
signals:
	//֪ͨ���ڲ������ź�
	void querySignal(QString);
	
	void querySettlementInfoSuccess();

	void queryInstrumentSuccess();

	void queryOrderSuccess();

	void queryTradeSuccess();

	void queryInvestorPositionSuccess();

	void queryTradingAccountSuccess();

	void updateAccount();
	
	void updatePositon();
};

