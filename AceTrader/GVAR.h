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

//价格变化标志
extern bool PriceFlag;

//下单手数
extern int DefaultVolume;

//登录界面显示的信息
extern std::vector<LoginParameter*> loginPar;

extern int requestID;

//互斥锁（用于改变order_ref）
extern std::mutex mtRef;

//前置机地址
extern QString MD_FRONT_ADDRESS;
extern QString TD_FRONT_ADDRESS;

//账户
extern QString BROKER;
extern QString USER_NAME;
extern QString PASSWORD;

//行情机状态
extern const QString OFFLINE;
extern const QString CONNECTING;
extern const QString ONLINE;
extern const QString SUBSCRIBING;
extern const QString DISCONNECTING;
//交易机状态
extern const QString TRADE_OFFLINE;
extern const QString TRADE_CONNECTING;
extern const QString TRADE_ONLINE;

//放置行情数据文件*.dat的前缀地址
extern const QString DAT_PREDIR;

//交易日
extern QString tradeDate;

//会话参数
extern TThostFtdcFrontIDType	trade_front_id;	 //前置编号
extern TThostFtdcSessionIDType	session_id;	     //会话编号
extern TThostFtdcOrderRefType	order_ref;	     //报单引用

//全部合约的列表(合约代码)
extern std::map<QString, Instrument*> instruList;

//持仓合约(用于订阅最新价)
extern std::set<QString> positionInstru;

//下拉框展示的合约名
extern std::vector<QString> comboInstru;

//所有正在交易的合约代码和名称
extern std::map<QString, QString> SHFE_Instru; //上海交易所
extern std::map<QString, QString> CZCE_Instru; //郑州交易所
extern std::map<QString, QString> DCE_Instru;  //大连交易所
extern std::map<QString, QString> CFFEX_Instru;  //中国金融交易所

//确认单信息
extern QString COMFIRM_MESSAGE;

//账户资金信息
extern Account *ACCOUNT;

//委托信息
extern std::map<QString, Order*, cmp> allOrder;

//止损信息
extern std::map<QString, Order*, cmp> allStopOrder;

//成交信息
extern std::map<QString, Trade*, cmp> allTrade;

//持仓信息
extern std::vector<Positions*> allPositions;

//是否是第一次查询
extern bool FIRST_FLAG;

//合约的参数
extern std::map<QString, InstruParameter*> allInstruPara;
//参数副本
extern std::map<QString, InstruParameter*> temp;

//交易信息
extern std::map<QString, OrderParameter*> orderPara;

//条件单ref与平仓单ref关联
extern std::map<QString, QString> actionOrder;

//报单sysid与ref关联(平仓时候使用)
extern std::map<QString, QString> Ref_SysID;

//撤单后，需要止损的合约
extern std::vector<QString> afterClose;