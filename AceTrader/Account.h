#pragma once
#include <QString>
#include "ThostFtdcTraderApi.h"

class Account{
public:
	Account();
	void update(CThostFtdcTradingAccountField *p);

public:
	///�ϴ���Ѻ���
	double PreMortgage;
	///�ϴ����ö��
	double PreCredit;
	///�ϴδ���
	double PreDeposit;
	///�ϴν���׼����
	double	PreBalance;
	///�ϴ�ռ�õı�֤��
	double	PreMargin;
	///��Ϣ����
	double	InterestBase;
	///��Ϣ����
	double	Interest;
	///�����
	double	Deposit;
	///������
	double	Withdraw;
	///����ı�֤��
	double	FrozenMargin;
	///������ʽ�
	double	FrozenCash;
	///�����������
	double	FrozenCommission;
	///��ǰ��֤���ܶ�
	double	CurrMargin;
	///�ʽ���
	double	CashIn;
	///������
	double	Commission;
	///ƽ��ӯ��
	double	CloseProfit;
	///�ֲ�ӯ��
	double	PositionProfit;
	///�ڻ�����׼����
	double	Balance;
	///�����ʽ�
	double	Available;
	///��ȡ�ʽ�
	double	WithdrawQuota;
	///����׼����
	double	Reserve;
	///���ö��
	double	Credit;
	///��Ѻ���
	double	Mortgage;
	///��������֤��
	double	ExchangeMargin;
	///Ͷ���߽��֤��
	double	DeliveryMargin;
	///���������֤��
	double	ExchangeDeliveryMargin;
	///������
	int	SettlementID;
	//��̬Ȩ��
	double StaticInterest;
	//��̬Ȩ��
	double DynamicInterest;
	//���ն�
	double Risk;
};

