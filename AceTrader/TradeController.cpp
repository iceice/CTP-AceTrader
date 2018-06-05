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
	strcpy(req.BrokerID, BROKER.toStdString().c_str());        //���͹�˾����  
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());   //Ͷ���ߴ���
	strcpy(req.InstrumentID, op->code.toStdString().c_str());  //��Լ����
	req.Direction = op->direction;                             //��������
	req.VolumeTotalOriginal = op->num;                         //����
	req.LimitPrice = op->price;                                //�۸�
	req.TimeCondition = op->timeCondition;                     //��Ч������
	req.CombOffsetFlag[0] = op->offset_flag;                   //��Ͽ�ƽ��־
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;          //���Ͷ���ױ���־
	req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;            //�����۸�����: �޼�
	req.VolumeCondition = THOST_FTDC_VC_AV;                    //�ɽ�������: �κ�����
	req.ContingentCondition = THOST_FTDC_CC_Immediately;       //��������: ���� 
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;       //ǿƽԭ��: ��ǿƽ
	req.MinVolume = 1;                                         //��С�ɽ���: 1
	req.IsAutoSuspend = 0;                                     //�Զ������־: ��
	req.UserForceClose = 0;                                    //�û�ǿƽ��־: ��
	
	mtRef.lock();
	strcpy(req.OrderRef, order_ref);                           //��������
	orderPara.insert(make_pair(QString(order_ref), op));       //�����뱨���Ĳ�������      
	int r;
	sscanf(order_ref, "%d", &r);
	r++;
	sprintf(order_ref, "%d", r);
	mtRef.unlock();

	int rt = trader->reqOrderInsert(&req, ++requestID);
	if (!rt) {
		qDebug() << ">>>>>>���ͱ���¼������ɹ�:" << endl;
	}
	else
		qDebug() << "--->>>���ͱ���¼������ʧ��:" << endl;

}
/******************************************�ۺ���*******************************************/
void TradeController::tradeClose(QString oref) {
	qDebug() << "��ʼƽ��";
	
	OrderParameter *op = orderPara[oref];
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER.toStdString().c_str());         //���͹�˾����  
	strcpy(req.InvestorID, USER_NAME.toStdString().c_str());    //Ͷ���ߴ���
	strcpy(req.InstrumentID, op->code.toStdString().c_str());   //��Լ����
	req.Direction = op->direction;                              //��������
	req.VolumeTotalOriginal = op->num;                          //����
	if (op->condition != '\0') {                                //ֹ��
		req.ContingentCondition = op->condition;
		req.StopPrice = op->stop_price;
		req.LimitPrice = op->stop_price;                        //�۸�
	}
	else { //ƽ�ֵ�
		req.LimitPrice = op->close_price;                       //�۸�
		req.ContingentCondition = THOST_FTDC_CC_Immediately;
	}
	req.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;           //��Ͽ�ƽ��־
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;           //���Ͷ���ױ���־
	req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;             //�����۸�����: �޼�
	req.TimeCondition = THOST_FTDC_TC_GFD;                      //��Ч������: ������Ч
	req.VolumeCondition = THOST_FTDC_VC_AV;                     //�ɽ�������: �κ�����
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;        //ǿƽԭ��: ��ǿƽ
	req.MinVolume = 1;                                          //��С�ɽ���: 1
	req.IsAutoSuspend = 0;                                      //�Զ������־: ��
	req.UserForceClose = 0;                                     //�û�ǿƽ��־: ��

	mtRef.lock();
	strcpy(req.OrderRef, order_ref);                            //��������
	orderPara.insert(make_pair(QString(order_ref), op));
	int r;
	sscanf(order_ref, "%d", &r);
	r++;
	sprintf(order_ref, "%d", r);
	mtRef.unlock();


	int rt = trader->reqOrderInsert(&req, ++requestID);
	if (!rt) {
		if (op->condition != '\0') {
			qDebug() << ">>>>>>���ͣ�ֹ�𵥣�¼������ɹ�:" << endl;
			//��������ƽ�ֵ�
			req.LimitPrice = op->close_price;
			req.ContingentCondition = THOST_FTDC_CC_Immediately;
			op->condition = '\0';
			op->close_price = op->stop_price;
			
			mtRef.lock();
			
			orderPara.insert(make_pair(QString(order_ref), op));
			//ͨ��ֹ���ҵ�ƽ�ֵ�
			actionOrder.insert(make_pair(req.OrderRef, order_ref));

			qDebug() << "��ԣ�" << req.OrderRef << "==" << order_ref;
			strcpy(req.OrderRef, order_ref);
			int r;
			sscanf(order_ref, "%d", &r);
			r++;
			sprintf(order_ref, "%d", r);
			mtRef.unlock();
			
			int ct = trader->reqOrderInsert(&req, ++requestID);
			if (!ct) {
				qDebug() << ">>>>>>���ͣ�ƽ�֡�ֹ�𵥣�¼������ɹ�:" << endl;
			}
			else
				qDebug() << "--->>>���ͣ�ƽ�֡�ֹ�𵥣�¼������ʧ��:" << endl;

		}
		else {


			qDebug() << ">>>>>>���ͣ�ƽ�ֵ���¼������ɹ�:" << endl;
		}
	}
	else
		qDebug() << "--->>>���ͣ�ƽ�ֵ���¼������ʧ��:" << endl;

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
		qDebug() << ">>>>>>���ͳ�������ɹ�:" <<id<< endl;
	}
	else {
		qDebug() << "--->>>���ͳ�������ʧ��:" <<id<< endl;
	}
}

void TradeController::actionClose(QString oref){
	
	//��Ϊ��������sysIdΪ����
	qDebug() << "��ʼ����andƽ��";
	//����ref�ҵ�id
	QString id = Ref_SysID[oref];
	
	//ֹ��Ӧ���������ɽ�����೷��
	orderPara[oref]->timeCondition = THOST_FTDC_TC_IOC;
	//���볷������Ҫƽ�ֵ�����
	afterClose.push_back(oref);
	
	reqOrderAction(id);
}
