#include "Account.h"



Account::Account(){
	PreMortgage = 0;
	PreCredit = 0;
	PreDeposit = 0;
	PreBalance = 0;
	PreMargin = 0;
	InterestBase = 0;
	Interest = 0;
	Deposit = 0;
	Withdraw = 0;
	FrozenMargin = 0;
	FrozenCash = 0;
	FrozenCommission = 0;
	CurrMargin = 0;
	CashIn = 0;
	Commission = 0;
	CloseProfit = 0;
	PositionProfit = 0;
	Balance = 0;
	Available = 0;
	WithdrawQuota = 0;
	Reserve = 0;
	Credit = 0;
	Mortgage = 0;
	ExchangeMargin = 0;
	DeliveryMargin = 0;
	ExchangeDeliveryMargin = 0;
	SettlementID = 0;
	StaticInterest = 0;
	DynamicInterest = 0;
	Risk = 0;
}

void Account::update(CThostFtdcTradingAccountField *p) {
	PreMortgage = p->PreMortgage;
	PreCredit = p->PreCredit;
	PreDeposit = p->Deposit;
	PreBalance = p->PreBalance;
	PreMargin = p->PreMargin;
	InterestBase = p->InterestBase;
	Interest = p->Interest;
	Deposit = p->Deposit;
	Withdraw = p->Withdraw;
	FrozenMargin = p->FrozenMargin;
	FrozenCash = p->FrozenCash;
	FrozenCommission = p->FrozenCommission;
	CurrMargin = p->CurrMargin;
	CashIn = p->CashIn;
	Commission = p->Commission;
	CloseProfit = p->CloseProfit;
	PositionProfit = p->PositionProfit;
	Balance = p->Balance;
	Available = p->Available;
	WithdrawQuota = p->WithdrawQuota;
	Reserve = p->Reserve;
	Credit = p->Credit;
	Mortgage = p->Mortgage;
	ExchangeMargin = p->ExchangeMargin;
	DeliveryMargin = p->DeliveryMargin;
	ExchangeDeliveryMargin = p->ExchangeDeliveryMargin;
	SettlementID = p->SettlementID;

	StaticInterest = p->PreBalance - p->Withdraw + p->Deposit;
	DynamicInterest= StaticInterest + p->CloseProfit + p->PositionProfit - p->Commission;
	Risk = 100 * (StaticInterest + PositionProfit - Available) / StaticInterest;
}
