#include "TradeController.h"
#include <QDebug>


using std::make_pair;

TradeController::TradeController() = default;

void TradeController::reset(){
	trader = nullptr;
}

void TradeController::setTrader(std::shared_ptr<Trader> t){
	trader = t;
	connect(trader.get(), SIGNAL(updateOrder()), this, SIGNAL(updateOrder()));
	connect(trader.get(), SIGNAL(updateTrade()), this, SIGNAL(updateTrade()));
	connect(trader.get(), SIGNAL(startClose(QString)), this, SLOT(tradeClose(QString)));
	connect(trader.get(), SIGNAL(startAction(QString)), this, SLOT(actionClose(QString)));
}

void TradeController::tradeServer(OrderParameter *op){
	
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());        //经纪公司代码  
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());   //投资者代码
	strcpy(req.InstrumentID, op->code.toStdString().c_str());  //合约代码
	req.Direction = op->direction;                             //买卖方向
	req.VolumeTotalOriginal = op->num;                         //数量
	req.LimitPrice = op->price;                                //价格
	req.TimeCondition = op->timeCondition;                     //有效期类型
	req.CombOffsetFlag[0] = op->offset_flag;                   //组合开平标志
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;          //组合投机套保标志
	req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;            //报单价格条件: 限价
	req.VolumeCondition = THOST_FTDC_VC_AV;                    //成交量类型: 任何数量
	req.ContingentCondition = THOST_FTDC_CC_Immediately;       //触发条件: 立即 
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;       //强平原因: 非强平
	req.MinVolume = 1;                                         //最小成交量: 1
	req.IsAutoSuspend = 0;                                     //自动挂起标志: 否
	req.UserForceClose = 0;                                    //用户强平标志: 否
	
	mtRef.lock();
	strcpy(req.OrderRef, order_ref);                           //报单引用
	orderPara.insert(make_pair(QString(order_ref), op));       //报单与报单的参数关联      
	int r;
	sscanf(order_ref, "%d", &r);
	r++;
	sprintf(order_ref, "%d", r);
	mtRef.unlock();

	int rt = trader->reqOrderInsert(&req, ++requestID);
	if (!rt) {
		qDebug() << ">>>>>>发送报单录入请求成功:" << endl;
	}
	else
		qDebug() << "--->>>发送报单录入请求失败:" << endl;

}
/******************************************槽函数*******************************************/
void TradeController::tradeClose(QString oref) {
	qDebug() << "开始平仓";
	
	OrderParameter *op = orderPara[oref];
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());         //经纪公司代码  
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());    //投资者代码
	strcpy(req.InstrumentID, op->code.toStdString().c_str());   //合约代码
	req.Direction = op->direction;                              //买卖方向
	req.VolumeTotalOriginal = op->num;                          //数量
	if (op->condition != '\0') {                                //止损单
		req.ContingentCondition = op->condition;
		req.StopPrice = op->stop_price;
		req.LimitPrice = op->stop_price;                        //价格
	}
	else { //平仓单
		req.LimitPrice = op->close_price;                       //价格
		req.ContingentCondition = THOST_FTDC_CC_Immediately;
	}
	req.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;           //组合开平标志
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;           //组合投机套保标志
	req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;             //报单价格条件: 限价
	req.TimeCondition = THOST_FTDC_TC_GFD;                      //有效期类型: 当日有效
	req.VolumeCondition = THOST_FTDC_VC_AV;                     //成交量类型: 任何数量
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;        //强平原因: 非强平
	req.MinVolume = 1;                                          //最小成交量: 1
	req.IsAutoSuspend = 0;                                      //自动挂起标志: 否
	req.UserForceClose = 0;                                     //用户强平标志: 否

	mtRef.lock();
	strcpy(req.OrderRef, order_ref);                            //报单引用
	orderPara.insert(make_pair(QString(order_ref), op));
	int r;
	sscanf(order_ref, "%d", &r);
	r++;
	sprintf(order_ref, "%d", r);
	mtRef.unlock();


	int rt = trader->reqOrderInsert(&req, ++requestID);
	if (!rt) {
		if (op->condition != '\0') {
			qDebug() << ">>>>>>发送（止损单）录入请求成功:" << endl;
			//继续发送平仓单
			req.LimitPrice = op->close_price;
			req.ContingentCondition = THOST_FTDC_CC_Immediately;
			op->condition = '\0';
			op->close_price = op->stop_price;
			
			mtRef.lock();
			
			orderPara.insert(make_pair(QString(order_ref), op));
			//通过止损单找到平仓单
			actionOrder.insert(make_pair(req.OrderRef, order_ref));

			qDebug() << "配对：" << req.OrderRef << "==" << order_ref;
			strcpy(req.OrderRef, order_ref);
			int r;
			sscanf(order_ref, "%d", &r);
			r++;
			sprintf(order_ref, "%d", r);
			mtRef.unlock();
			
			int ct = trader->reqOrderInsert(&req, ++requestID);
			if (!ct) {
				qDebug() << ">>>>>>发送（平仓、止损单）录入请求成功:" << endl;
			}
			else
				qDebug() << "--->>>发送（平仓、止损单）录入请求失败:" << endl;

		}
		else {


			qDebug() << ">>>>>>发送（平仓单）录入请求成功:" << endl;
		}
	}
	else
		qDebug() << "--->>>发送（平仓单）录入请求失败:" << endl;

}

void TradeController::reqOrderAction(QString id) {
	CThostFtdcInputOrderActionField req;
	Order *p = allOrder[id];

	if (p == nullptr)
		return;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());
	strcpy(req.InstrumentID, p->InstrumentID.toStdString().c_str());
	strcpy(req.OrderRef, p->OrderRef.toStdString().c_str());
	req.FrontID = p->FrontID;
	req.SessionID = p->SessionID;
	req.ActionFlag = THOST_FTDC_AF_Delete;
	int rt = trader->reqOrderAction(&req, ++requestID);
	if (!rt) {
		qDebug() << ">>>>>>发送撤单请求成功:" <<id<< endl;
	}
	else {
		qDebug() << "--->>>发送撤单请求失败:" <<id<< endl;
	}
}

void TradeController::actionClose(QString oref){
	
	//因为订单是以sysId为主键
	qDebug() << "开始撤单and平仓";
	//根据ref找到id
	QString id = Ref_SysID[oref];
	
	//止损单应该是立即成交，否侧撤单
	orderPara[oref]->timeCondition = THOST_FTDC_TC_IOC;
	//加入撤单后需要平仓的序列
	afterClose.push_back(oref);
	
	reqOrderAction(id);
}
