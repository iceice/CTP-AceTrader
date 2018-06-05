#include "GVAR.h"

//�۸�仯��־
bool PriceFlag = true;

//�µ�����
int DefaultVolume = 0;

//��¼������ʾ����Ϣ
std::vector<LoginParameter*> loginPar;

int requestID = 0;

//�����������ڸı�order_ref��
std::mutex mtRef;

//ǰ�û���ַ
QString MD_FRONT_ADDRESS("");
QString TD_FRONT_ADDRESS("");

//�˻�
QString BROKER("");
QString USER_NAME("");
QString PASSWORD("");

//�����״̬
const QString OFFLINE("���飺����");
const QString CONNECTING("���飺��������...");
const QString ONLINE("���飺����");
const QString SUBSCRIBING("���ڽ�������...");
const QString DISCONNECTING("���ڶϿ�����...");

//���׻�״̬
const QString TRADE_OFFLINE("���ף�����");
const QString TRADE_CONNECTING("���ף���������...");
const QString TRADE_ONLINE("���ף�����");


//�������������ļ�*.dat��ǰ׺��ַ
const QString DAT_PREDIR("data/");

//�Ự����
TThostFtdcFrontIDType	trade_front_id;	 //ǰ�ñ��
TThostFtdcSessionIDType	session_id;	     //�Ự���
TThostFtdcOrderRefType	order_ref;	     //��������

//ȫ����Լ���б�(��Լ����)
std::map<QString, Instrument*> instruList;

//�ֲֺ�Լ(���ڶ������¼�)
std::set<QString> positionInstru;

//������չʾ�ĺ�Լ��
std::vector<QString> comboInstru;

//�������ڽ��׵ĺ�Լ���������
std::map<QString, QString> SHFE_Instru; //�Ϻ�������
std::map<QString, QString> CZCE_Instru; //֣�ݽ�����
std::map<QString, QString> DCE_Instru;  //����������
std::map<QString, QString> CFFEX_Instru;  //�й����ڽ�����

//������
QString tradeDate("");

//ȷ�ϵ���Ϣ
QString COMFIRM_MESSAGE("");

//�˻��ʽ���Ϣ
Account *ACCOUNT = new Account();

//ί����Ϣ
std::map<QString, Order*, cmp> allOrder;

//ֹ����Ϣ
std::map<QString, Order*, cmp> allStopOrder;

//�ɽ���Ϣ
std::map<QString, Trade*, cmp> allTrade;

//�ֲ���Ϣ
std::vector<Positions*> allPositions;

//�Ƿ��ǵ�һ�β�ѯ
bool FIRST_FLAG = true;

//��Լ�Ĳ���
std::map<QString, InstruParameter*> allInstruPara;
std::map<QString, InstruParameter*> temp;

//������Ϣ
std::map<QString, OrderParameter*> orderPara;

//��������ƽ�ֵ�����
std::map<QString, QString> actionOrder;

//����ref��sysid����(���ڸ�������������ƽ�ֵ�)
std::map<QString, QString> Ref_SysID;

//��������Ҫֹ��ĺ�Լ
std::vector<QString> afterClose;