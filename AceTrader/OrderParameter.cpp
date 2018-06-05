#include "OrderParameter.h"



OrderParameter::OrderParameter(QString c): code(c){
	
	offset_flag = '\0';
	direction = '\0';
	num = 0;
	price = 0;
	close_price = 0;
	stop_price = 0;
	condition = '\0';
	timeCondition = '\0';

}

void OrderParameter::update(CThostFtdcTradeField * p){
	//��������Ҫ�෴
	if (p->Direction == THOST_FTDC_D_Buy)
		direction = THOST_FTDC_D_Sell;
	if (p->Direction == THOST_FTDC_D_Sell)
		direction = THOST_FTDC_D_Buy;
	
	//������Ϊ�ɽ�����
	num = p->Volume;
	//��Ϊƽ��
	offset_flag = THOST_FTDC_OF_CloseToday;

	//��Ч������
	timeCondition = THOST_FTDC_TC_GFD;

}
