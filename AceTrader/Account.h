#pragma once
#include <QString>
#include "ThostFtdcTraderApi.h"

class Account{
public:
	Account();
	void update(CThostFtdcTradingAccountField *p);

public:
	///上次质押金额
	double PreMortgage;
	///上次信用额度
	double PreCredit;
	///上次存款额
	double PreDeposit;
	///上次结算准备金
	double	PreBalance;
	///上次占用的保证金
	double	PreMargin;
	///利息基数
	double	InterestBase;
	///利息收入
	double	Interest;
	///入金金额
	double	Deposit;
	///出金金额
	double	Withdraw;
	///冻结的保证金
	double	FrozenMargin;
	///冻结的资金
	double	FrozenCash;
	///冻结的手续费
	double	FrozenCommission;
	///当前保证金总额
	double	CurrMargin;
	///资金差额
	double	CashIn;
	///手续费
	double	Commission;
	///平仓盈亏
	double	CloseProfit;
	///持仓盈亏
	double	PositionProfit;
	///期货结算准备金
	double	Balance;
	///可用资金
	double	Available;
	///可取资金
	double	WithdrawQuota;
	///基本准备金
	double	Reserve;
	///信用额度
	double	Credit;
	///质押金额
	double	Mortgage;
	///交易所保证金
	double	ExchangeMargin;
	///投资者交割保证金
	double	DeliveryMargin;
	///交易所交割保证金
	double	ExchangeDeliveryMargin;
	///结算编号
	int	SettlementID;
	//静态权益
	double StaticInterest;
	//动态权益
	double DynamicInterest;
	//风险度
	double Risk;
};

