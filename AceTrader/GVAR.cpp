#include "GVAR.h"

//价格变化标志
bool PriceFlag = true;

//下单手数
int DefaultVolume = 0;

//登录界面显示的信息
std::vector<LoginParameter*> loginPar;

int requestID = 0;

//互斥锁（用于改变order_ref）
std::mutex mtRef;

//前置机地址
QString MD_FRONT_ADDRESS("");
QString TD_FRONT_ADDRESS("");

//账户
QString BROKER("");
QString USER_NAME("");
QString PASSWORD("");

//行情机状态
const QString OFFLINE("行情：离线");
const QString CONNECTING("行情：正在连接...");
const QString ONLINE("行情：在线");
const QString SUBSCRIBING("正在接收行情...");
const QString DISCONNECTING("正在断开连接...");

//交易机状态
const QString TRADE_OFFLINE("交易：离线");
const QString TRADE_CONNECTING("交易：正在连接...");
const QString TRADE_ONLINE("交易：在线");


//放置行情数据文件*.dat的前缀地址
const QString DAT_PREDIR("data/");

//会话参数
TThostFtdcFrontIDType	trade_front_id;	 //前置编号
TThostFtdcSessionIDType	session_id;	     //会话编号
TThostFtdcOrderRefType	order_ref;	     //报单引用

//全部合约的列表(合约代码)
std::map<QString, Instrument*> instruList;

//持仓合约(用于订阅最新价)
std::set<QString> positionInstru;

//下拉框展示的合约名
std::vector<QString> comboInstru;

//所有正在交易的合约代码和名称
std::map<QString, QString> SHFE_Instru; //上海交易所
std::map<QString, QString> CZCE_Instru; //郑州交易所
std::map<QString, QString> DCE_Instru;  //大连交易所
std::map<QString, QString> CFFEX_Instru;  //中国金融交易所

//交易日
QString tradeDate("");

//确认单信息
QString COMFIRM_MESSAGE("");

//账户资金信息
Account *ACCOUNT = new Account();

//委托信息
std::map<QString, Order*, cmp> allOrder;

//止损信息
std::map<QString, Order*, cmp> allStopOrder;

//成交信息
std::map<QString, Trade*, cmp> allTrade;

//持仓信息
std::vector<Positions*> allPositions;

//是否是第一次查询
bool FIRST_FLAG = true;

//合约的参数
std::map<QString, InstruParameter*> allInstruPara;
std::map<QString, InstruParameter*> temp;

//交易信息
std::map<QString, OrderParameter*> orderPara;

//条件单与平仓单关联
std::map<QString, QString> actionOrder;

//报单ref与sysid关联(用于根据条件单撤销平仓单)
std::map<QString, QString> Ref_SysID;

//撤单后，需要止损的合约
std::vector<QString> afterClose;