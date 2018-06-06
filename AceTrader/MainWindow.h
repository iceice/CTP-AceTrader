#pragma once

//主窗口类
#include <QObject>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QLineEdit>
#include <QAction>
#include <QMenu>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QKeyEvent>
#include <QButtonGroup>
#include <QBoxLayout>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QCheckBox>
#include <memory>
#include "ConnectController.h"
#include "QueryController.h"
#include "TradeController.h"
#include "SettingDialog.h"
#include "SubscribeController.h"
#include "ConfirmDialog.h"
#include "OrderTable.h"
#include "TradeTable.h"
#include "PositionTable.h"
#include "AccountTable.h"
#include "MyQDoubleSpinBox.h"
#include "ClickableLabel.h"
#include "TitleBar.h"
#include "SumTable.h"
#include "StopOrderTable.h"


class MainWindow :public QMainWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);

	public slots:
	void startConnect();                //开始连接
private:
	void createStatusBur();
	//初始化连接控制器
	void initController();
	private slots:
	void updatePrice();                 //更新价格
	void setAskPrice(const QString& text); //设置价格
	void setLastPrice(const QString& text); //设置价格
	void setBidPrice(const QString& text); //设置价格
	void statusConnectSuccess();	    //连接成功后状态变更为在线，使得订阅和退订可执行
	void tradeStatusConnectSuccess();	//连接成功后状态变更为在线，使得订阅和退订可执行
	void showSettingDialog();           //展示设置界面
	void showConfirmDialog();           //展示投资者结算结果确认
	void showInstru();                  //下拉框展示合约
	void keyPressEvent(QKeyEvent *k);   //快捷键
	void buttonChange(int buttonId);    //信息切换
	void startSub(int num);             //开始订阅相关合约
	void connectNoFocus();              //连接后不显示焦点
	void tradeServer(int d);            //开始下单
	void cancelOrder();                 //取消订单
	void quickCancelOrder(int r, int c);
	void setpositonClose(Positions *p);
	void OnPriceValueChanged(double);
private:
	//按钮和输入框
	QPushButton *settingButton;	    //设置
	//买卖
	QPushButton *buyButton;
	QPushButton *sellButton;
	QButtonGroup *bsButtonGroup;
/****************************************下单面板***************************************************/
	//下拉单
	QLabel *insLabel;
	QComboBox *instruCombo;
	//选择开仓，平仓，平今
	QRadioButton *openRadio;
	QLabel *ol;
	QRadioButton *closeRadio;
	QLabel *cl;
	QRadioButton *todayRadio;
	QLabel *tl;
	//数量
	QLabel *numLabel;
	QSpinBox *numberSpin;

	//价格
	QLabel *priceLable;
	MyQDoubleSpinBox *priceSpin;
	ClickableLabel *askPriceLabel;   //卖价
	ClickableLabel *lastPriceLabel;  //最新价
	ClickableLabel *bidPriceLabel;   //买价
	QTimer *updatePriceTimer;  //自动刷新计时器
	
	QLabel *multiLable; //平多
	QSpinBox *multiSpin;
	QLabel *emptyLable; //平空
	QSpinBox *emptySpin;
	QLabel *waitLable; //等待至全部成交
	QCheckBox *waitCheck;
	QLabel *stopLable; //逆向止损
	QCheckBox *stopCheck;
	QSpinBox *stopSpin;

/****************************委托与回报**********************************************/
	QPushButton *orderButton;
	QPushButton *tradeMsgButton;
	QPushButton *positionButton;
	QPushButton *accountButton;
	QPushButton *stopMsgButoon;
	QButtonGroup *mainButtonGroup;
	QStackedWidget *stackWidget;
	
	QPushButton *withdrawButton;

	OrderTable *orderTable;
	OrderTable *partOrderTable;
	PositionTable *positionTable;
	AccountTable *accountTable;
	SumTable *tradeTable;
	StopOrderTable *stopOrderTable;
	
/**************************************************************************************/	
	//状态栏的控件及相关
	
	QLabel *mdstatusLabel;
	QLabel *tradestatusLabel;

	//窗口
	SettingDialog *setDialog = nullptr;
	ConfirmDialog *confirmDialog = nullptr;

	//控制器
	std::shared_ptr<ConnectController> connectController;
	std::shared_ptr<QueryController> queryController;
	std::shared_ptr<SubscribeController> subController;
	std::shared_ptr<TradeController> tradeController;

	TitleBar *m_pTitleBar;

signals:
	void connecting();		//正在连接
	void connectFailed();	//连接失败
	void loginSuccess();	//登陆成功
	void tradeConnecting();
	void tradeConnectFailed();
	void tradeLoginSuccess();
	void querySignal(QString);
	void allSuccess();
	void loginFailed(QString);
};