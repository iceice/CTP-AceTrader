#pragma once

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QString>
#include <map>
#include <set>
#include <vector>
#include "ThostFtdcTraderApi.h"
#include "Instrument.h"
#include "Account.h"
#include "Order.h"
#include "Trade.h"
#include "Positions.h"
#include "InstruParameter.h"
#include "OrderParameter.h"
#include "LoginParameter.h"
#include <mutex>

struct cmp {
	bool operator()(const QString& s1, const QString& s2) const{
		if (s1.length() == s2.length())
			return s1 < s2;
		else
			return s1.length() < s2.length();
	}
};

//�۸�仯��־
extern bool PriceFlag;

//�µ�����
extern int DefaultVolume;

//��¼������ʾ����Ϣ
extern std::vector<LoginParameter*> loginPar;

extern int requestID;

//�����������ڸı�order_ref��
extern std::mutex mtRef;

//ǰ�û���ַ
extern QString MD_FRONT_ADDRESS;
extern QString TD_FRONT_ADDRESS;

//�˻�
extern QString BROKER;
extern QString USER_NAME;
extern QString PASSWORD;

//�����״̬
extern const QString OFFLINE;
extern const QString CONNECTING;
extern const QString ONLINE;
extern const QString SUBSCRIBING;
extern const QString DISCONNECTING;
//���׻�״̬
extern const QString TRADE_OFFLINE;
extern const QString TRADE_CONNECTING;
extern const QString TRADE_ONLINE;

//�������������ļ�*.dat��ǰ׺��ַ
extern const QString DAT_PREDIR;

//������
extern QString tradeDate;

//�Ự����
extern TThostFtdcFrontIDType	trade_front_id;	 //ǰ�ñ��
extern TThostFtdcSessionIDType	session_id;	     //�Ự���
extern TThostFtdcOrderRefType	order_ref;	     //��������

//ȫ����Լ���б�(��Լ����)
extern std::map<QString, Instrument*> instruList;

//�ֲֺ�Լ(���ڶ������¼�)
extern std::set<QString> positionInstru;

//������չʾ�ĺ�Լ��
extern std::vector<QString> comboInstru;

//�������ڽ��׵ĺ�Լ���������
extern std::map<QString, QString> SHFE_Instru; //�Ϻ�������
extern std::map<QString, QString> CZCE_Instru; //֣�ݽ�����
extern std::map<QString, QString> DCE_Instru;  //����������
extern std::map<QString, QString> CFFEX_Instru;  //�й����ڽ�����

//ȷ�ϵ���Ϣ
extern QString COMFIRM_MESSAGE;

//�˻��ʽ���Ϣ
extern Account *ACCOUNT;

//ί����Ϣ
extern std::map<QString, Order*, cmp> allOrder;

//ֹ����Ϣ
extern std::map<QString, Order*, cmp> allStopOrder;

//�ɽ���Ϣ
extern std::map<QString, Trade*, cmp> allTrade;

//�ֲ���Ϣ
extern std::vector<Positions*> allPositions;

//�Ƿ��ǵ�һ�β�ѯ
extern bool FIRST_FLAG;

//��Լ�Ĳ���
extern std::map<QString, InstruParameter*> allInstruPara;
//��������
extern std::map<QString, InstruParameter*> temp;

//������Ϣ
extern std::map<QString, OrderParameter*> orderPara;

//������ref��ƽ�ֵ�ref����
extern std::map<QString, QString> actionOrder;

//����sysid��ref����(ƽ��ʱ��ʹ��)
extern std::map<QString, QString> Ref_SysID;

//��������Ҫֹ��ĺ�Լ
extern std::vector<QString> afterClose;