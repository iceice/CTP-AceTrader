#pragma once
#include <QObject>
#include <memory>
#include "Trader.h"
using std::shared_ptr;

class QueryController :public QObject{
	Q_OBJECT
public:
	QueryController();
	void reset(); //恢复初始状态
	void setTrader(std::shared_ptr<Trader> t);
	
	public slots:
	void startquerySettlementInfoTimer();
	void startshowConfirmDialogTimer();
	void startqueryInstrumentsTimer();
	void startqueryTradingAccountTimer();
	void startqueryInvestorPositionTimer();
	void startqueryTradeTimer();
	void startqueryOrderTimer();

	void querySettlementInfoConfirm();          //1、查询是否已经做了确认
	void querySettlementInfo();                 //2、请求查询确认单
	void settlementInfoConfirm();               //3、投资者结算结果确认
	void queryInstruments();                    //4、查询合约
	void queryTradingAccount();                 //5、请求查询资金账户
	void queryInvestorPosition();               //6、请求查询投资者持仓
	void queryTrade();                          //7、请求查询成交
	void queryOrder();                          //8、请求查询报单
	void allSuccess();

private:
	std::shared_ptr<Trader> trader;
	QTimer *querySettlementInfoTimer;          //查询确认信息倒计时
	QTimer *showConfirmDialogTimer;            //展示确认信息倒计时
	QTimer *queryInstrumentsTimer;             //查询合约倒计时
	QTimer *queryTradingAccountTimer;          //查询账户资金倒计时
	QTimer *queryInvestorPositionTimer;        //查询投资者持仓倒计时
	QTimer *queryTradeTimer;                   //请求查询成交倒计时
	QTimer *queryOrderTimer;                   //请求查询报单倒计时
	
signals:
	//通知窗口部件的信号
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

