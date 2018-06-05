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
	//买，卖方向要相反
	if (p->Direction == THOST_FTDC_D_Buy)
		direction = THOST_FTDC_D_Sell;
	if (p->Direction == THOST_FTDC_D_Sell)
		direction = THOST_FTDC_D_Buy;
	
	//数量变为成交数量
	num = p->Volume;
	//变为平今
	offset_flag = THOST_FTDC_OF_CloseToday;

	//有效期类型
	timeCondition = THOST_FTDC_TC_GFD;

}
