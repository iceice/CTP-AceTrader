#pragma once

//��������
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
	void startConnect();                //��ʼ����
private:
	void createStatusBur();
	//��ʼ�����ӿ�����
	void initController();
	private slots:
	void updatePrice();                 //���¼۸�
	void setAskPrice(const QString& text); //���ü۸�
	void setLastPrice(const QString& text); //���ü۸�
	void setBidPrice(const QString& text); //���ü۸�
	void statusConnectSuccess();	    //���ӳɹ���״̬���Ϊ���ߣ�ʹ�ö��ĺ��˶���ִ��
	void tradeStatusConnectSuccess();	//���ӳɹ���״̬���Ϊ���ߣ�ʹ�ö��ĺ��˶���ִ��
	void showSettingDialog();           //չʾ���ý���
	void showConfirmDialog();           //չʾͶ���߽�����ȷ��
	void showInstru();                  //������չʾ��Լ
	void keyPressEvent(QKeyEvent *k);   //��ݼ�
	void buttonChange(int buttonId);    //��Ϣ�л�
	void startSub(int num);             //��ʼ������غ�Լ
	void connectNoFocus();              //���Ӻ���ʾ����
	void tradeServer(int d);            //��ʼ�µ�
	void cancelOrder();                 //ȡ������
	void quickCancelOrder(int r, int c);
	void setpositonClose(Positions *p);
	void OnPriceValueChanged(double);
private:
	//��ť�������
	QPushButton *settingButton;	    //����
	//����
	QPushButton *buyButton;
	QPushButton *sellButton;
	QButtonGroup *bsButtonGroup;
/****************************************�µ����***************************************************/
	//������
	QLabel *insLabel;
	QComboBox *instruCombo;
	//ѡ�񿪲֣�ƽ�֣�ƽ��
	QRadioButton *openRadio;
	QLabel *ol;
	QRadioButton *closeRadio;
	QLabel *cl;
	QRadioButton *todayRadio;
	QLabel *tl;
	//����
	QLabel *numLabel;
	QSpinBox *numberSpin;

	//�۸�
	QLabel *priceLable;
	MyQDoubleSpinBox *priceSpin;
	ClickableLabel *askPriceLabel;   //����
	ClickableLabel *lastPriceLabel;  //���¼�
	ClickableLabel *bidPriceLabel;   //���
	QTimer *updatePriceTimer;  //�Զ�ˢ�¼�ʱ��
	
	QLabel *multiLable; //ƽ��
	QSpinBox *multiSpin;
	QLabel *emptyLable; //ƽ��
	QSpinBox *emptySpin;
	QLabel *waitLable; //�ȴ���ȫ���ɽ�
	QCheckBox *waitCheck;
	QLabel *stopLable; //����ֹ��
	QCheckBox *stopCheck;
	QSpinBox *stopSpin;

/****************************ί����ر�**********************************************/
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
	//״̬���Ŀؼ������
	
	QLabel *mdstatusLabel;
	QLabel *tradestatusLabel;

	//����
	SettingDialog *setDialog = nullptr;
	ConfirmDialog *confirmDialog = nullptr;

	//������
	std::shared_ptr<ConnectController> connectController;
	std::shared_ptr<QueryController> queryController;
	std::shared_ptr<SubscribeController> subController;
	std::shared_ptr<TradeController> tradeController;

	TitleBar *m_pTitleBar;

signals:
	void connecting();		//��������
	void connectFailed();	//����ʧ��
	void loginSuccess();	//��½�ɹ�
	void tradeConnecting();
	void tradeConnectFailed();
	void tradeLoginSuccess();
	void querySignal(QString);
	void allSuccess();
	void loginFailed(QString);
};