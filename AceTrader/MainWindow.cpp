#include "MainWindow.h"
#include "GVAR.h"
#include "stdio.h"
#include <QTabWidget>
#include <QDateTime>
#include <QString>
#include <QStatusBar>
#include <QDebug>
#include <QMessageBox>
#include <QStyledItemDelegate>
#include <QPixmap>
#include <QApplication>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>

using std::shared_ptr;
using std::make_shared;
using std::make_pair;

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent){

/****************************************�µ����***************************************************/
	QGroupBox *tradeBox = new QGroupBox("�µ����");
	
	//1����Լ
	insLabel = new QLabel("F1:��Լ");
	insLabel->setFixedWidth(50);
	insLabel->setObjectName("insLabel");
	instruCombo = new QComboBox();
	instruCombo->setFixedWidth(100);
	instruCombo->setFixedHeight(22);
	instruCombo->setObjectName("instruCombo");
	instruCombo->setItemDelegate(new QStyledItemDelegate());
	instruCombo->setMaxVisibleItems(5);
	for (auto iter = allInstruPara.begin(); iter != allInstruPara.end(); iter++) {
		instruCombo->addItem(iter->first);
	}
	instruCombo->setCurrentIndex(-1);
	connect(instruCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(startSub(int)));
	QHBoxLayout *insLayout = new QHBoxLayout();
	insLayout->setSpacing(5);
	insLayout->addWidget(insLabel);
	insLayout->addWidget(instruCombo);
	insLayout->addStretch();

	//2��ѡ�񿪲֣�ƽ�֣�ƽ��
	openRadio = new QRadioButton();
	openRadio->setShortcut(tr("O"));
	openRadio->setObjectName("openRadio");
	openRadio->setFixedSize(14, 14);
	ol = new QLabel("<u>O</u>:����");
	ol->setObjectName("openLabel");
	ol->setFixedWidth(42);
	closeRadio = new QRadioButton();
	closeRadio->setShortcut(tr("C"));
	closeRadio->setObjectName("closeRadio");
	closeRadio->setFixedSize(14, 14);
	cl = new QLabel("<u>C</u>:ƽ��");
	cl->setObjectName("closeLabel");
	cl->setFixedWidth(42);
	todayRadio = new QRadioButton();
	todayRadio->setShortcut(tr("T"));
	todayRadio->setObjectName("todayRadio");
	todayRadio->setFixedSize(14, 14);
	tl = new QLabel("<u>T</u>:ƽ��");
	tl->setObjectName("todayLabel");
	tl->setFixedWidth(42);
	openRadio->setChecked(true);
	QHBoxLayout *radioLayout = new QHBoxLayout();
	radioLayout->setSpacing(7);
	radioLayout->addWidget(openRadio);
	radioLayout->addWidget(ol);
	radioLayout->addSpacing(5);
	radioLayout->addWidget(closeRadio);
	radioLayout->addWidget(cl);
	radioLayout->addSpacing(5);
	radioLayout->addWidget(todayRadio);
	radioLayout->addWidget(tl);
	radioLayout->addStretch();
	

	//3������
	numLabel = new QLabel("F2:����");
	numLabel->setFixedWidth(50);
	numLabel->setObjectName("numLabel");
	numberSpin = new QSpinBox();
	numberSpin->setMaximum(9999999);
	numberSpin->setFixedWidth(66);
	numberSpin->setFixedHeight(22);
	QHBoxLayout *numLayout = new QHBoxLayout();
	numLayout->addWidget(numLabel);
	numLayout->setSpacing(5);
	numLayout->addWidget(numberSpin);
	numLayout->addStretch();
	
	//4���۸�
	priceLable = new QLabel("F3:�۸�");
	priceLable->setFixedWidth(50);
	priceLable->setObjectName("priceLable");
	priceSpin = new MyQDoubleSpinBox();
	priceSpin->setFixedWidth(66);
	priceSpin->setMinimumHeight(22);
	QHBoxLayout *price_left = new QHBoxLayout();
	price_left->addWidget(priceLable);
	price_left->setSpacing(5);
	price_left->addWidget(priceSpin);

	connect(priceSpin, SIGNAL(valueChanged(double)), this, SLOT(OnPriceValueChanged(double)));
	
	QVBoxLayout *price_right = new QVBoxLayout();
	askPriceLabel = new ClickableLabel(this);
	askPriceLabel->setObjectName("askPriceLabel");
	askPriceLabel->setFixedWidth(100);
	lastPriceLabel = new ClickableLabel(this);
	lastPriceLabel->setObjectName("lastPriceLabel");
	lastPriceLabel->setFixedWidth(100);
	bidPriceLabel = new ClickableLabel(this);
	bidPriceLabel->setObjectName("bidPriceLabel");
	bidPriceLabel->setFixedWidth(100);
	connect(askPriceLabel, SIGNAL(clicked(const QString& )), this, SLOT(setAskPrice(const QString& )));
	connect(lastPriceLabel, SIGNAL(clicked(const QString& )), this, SLOT(setLastPrice(const QString& )));
	connect(bidPriceLabel, SIGNAL(clicked(const QString& )), this, SLOT(setBidPrice(const QString& )));
	QFrame *line1 = new QFrame();
	line1->setFrameShape(QFrame::HLine);
	line1->setFrameShadow(QFrame::Sunken);
	line1->setFixedWidth(100);
	QFrame *line2 = new QFrame();
	line2->setFrameShape(QFrame::HLine);
	line2->setFrameShadow(QFrame::Sunken);
	line2->setFixedWidth(100);
	price_right->setSpacing(3);
	price_right->addWidget(askPriceLabel);
	price_right->addWidget(line1);
	price_right->addWidget(lastPriceLabel);
	price_right->addWidget(line2);
	price_right->addWidget(bidPriceLabel);
	updatePriceTimer = new QTimer(this);
	connect(updatePriceTimer, SIGNAL(timeout()), this, SLOT(updatePrice()));
	QHBoxLayout *priceLayout = new QHBoxLayout();
	priceLayout->addLayout(price_left);
	priceLayout->addSpacing(2);
	priceLayout->addLayout(price_right);
	priceLayout->addStretch();
	//������벿�ֲ���
	QVBoxLayout *tradeLeft = new QVBoxLayout();
	tradeLeft->setSpacing(0);
	tradeLeft->addLayout(insLayout);
	tradeLeft->addSpacing(14);
	tradeLeft->addLayout(radioLayout);
	tradeLeft->addSpacing(14);
	tradeLeft->addLayout(numLayout);
	tradeLeft->addSpacing(14);
	tradeLeft->addLayout(priceLayout);
	tradeLeft->addStretch();
	//�����Ұ벿�ֲ���
	//��ʼ�����ӡ����ð�ť
	settingButton = new QPushButton("����");
	settingButton->setObjectName("settingButton");
	settingButton->setFixedSize(75, 28);
	
	buyButton = new QPushButton(("B ����"));
	buyButton->setObjectName("buyButton");
	buyButton->setShortcut(tr("B"));
	buyButton->setFixedHeight(46);
	buyButton->setFixedWidth(76);
	
	sellButton = new QPushButton(("S ����"));
	sellButton->setObjectName("SellButton");
	sellButton->setShortcut(tr("S"));
	sellButton->setFixedHeight(46);
	sellButton->setFixedWidth(76);
	
	bsButtonGroup = new QButtonGroup();
	bsButtonGroup->addButton(buyButton, 1);
	bsButtonGroup->addButton(sellButton, 2);
	bsButtonGroup->setExclusive(true);
	
	//��ť���
	QHBoxLayout *csLayout = new QHBoxLayout();
	csLayout->addStretch();
	csLayout->addWidget(settingButton);
	
	QHBoxLayout *bsLayout = new QHBoxLayout();
	bsLayout->addWidget(buyButton);
	bsLayout->addWidget(sellButton);

	//F4:ƽ��ҵ�
	multiLable = new QLabel("F4:ƽ��ҵ�+");
	multiLable->setObjectName("multiLable");
	multiLable->setFixedWidth(100);
	multiSpin = new QSpinBox();
	multiSpin->setFixedWidth(50);
	multiSpin->setFixedHeight(22);
	QHBoxLayout *multiLayout = new QHBoxLayout();
	multiLayout->addWidget(multiLable);
	multiLayout->addWidget(multiSpin);
	//F5:ƽ�չҵ�
	emptyLable = new QLabel("F5:ƽ�չҵ�-");
	emptyLable->setObjectName("emptyLable");
	emptyLable->setFixedWidth(100);
	emptySpin = new QSpinBox();
	emptySpin->setFixedWidth(50);
	emptySpin->setFixedHeight(22);
	QHBoxLayout *emptyLayout = new QHBoxLayout();
	emptyLayout->addWidget(emptyLable);
	emptyLayout->addWidget(emptySpin);
	//F6:�ȴ���ȫ���ɽ�
	waitCheck = new QCheckBox();
	waitCheck->setFixedSize(14, 14);
	waitLable = new QLabel("F6:�ȴ���ȫ���ɽ�");
	waitLable->setObjectName("waitLable");
	waitLable->setFixedWidth(138);
	QHBoxLayout *waitLayout = new QHBoxLayout();
	waitLayout->addWidget(waitCheck);
	waitLayout->addWidget(waitLable);
	//F7:����ֹ��
	stopCheck = new QCheckBox();
	stopCheck->setFixedSize(14, 14);
	stopLable = new QLabel("F7:����ֹ��");
	stopLable->setObjectName("stopLable");
	stopLable->setFixedWidth(82);
	stopSpin = new QSpinBox();
	stopSpin->setFixedWidth(50);
	stopSpin->setFixedHeight(22);
	QHBoxLayout *stopLayout = new QHBoxLayout();
	stopLayout->addWidget(stopCheck);
	stopLayout->addWidget(stopLable);
	stopLayout->addWidget(stopSpin);
	//����
	QVBoxLayout *tradeRight = new QVBoxLayout();
	tradeRight->addLayout(csLayout);
	tradeRight->addLayout(multiLayout);
	tradeRight->addLayout(emptyLayout);
	tradeRight->addLayout(waitLayout);
	tradeRight->addLayout(stopLayout);
	tradeRight->addLayout(bsLayout);
	//���ײ���
	QHBoxLayout *tradeLayout = new QHBoxLayout();
	tradeLayout->addLayout(tradeLeft,3);
	tradeLayout->addSpacing(5);
	tradeLayout->addLayout(tradeRight,1);
	QVBoxLayout *left = new QVBoxLayout();
	left->addLayout(tradeLayout);
	left->addStretch(2);
	tradeBox->setLayout(left);
	tradeBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

/********************************************ί����ر�**********************************************/
	QGroupBox *responseBox = new QGroupBox("ί����ر�");
	orderButton = new QPushButton("ί����Ϣ");
	stopMsgButoon = new QPushButton("ֹ����Ϣ");
	tradeMsgButton = new QPushButton("�ɽ���Ϣ");
	positionButton = new QPushButton("�ֲ���Ϣ");
	accountButton = new QPushButton("�ʽ���Ϣ");
	orderButton->setObjectName("orderButton");
	stopMsgButoon->setObjectName("stopOrderButton");
	tradeMsgButton->setObjectName("tradeMsgButton");
	positionButton->setObjectName("positionButton");
	accountButton->setObjectName("accountButton");
	orderButton->setFixedSize(62, 18);
	stopMsgButoon->setFixedSize(62, 18);
	tradeMsgButton->setFixedSize(62, 18);
	positionButton->setFixedSize(62, 18);
	accountButton->setFixedSize(62, 18);
	orderButton->setCheckable(true);
	stopMsgButoon->setCheckable(true);
	tradeMsgButton->setCheckable(true);
	positionButton->setCheckable(true);
	accountButton->setCheckable(true);
	orderButton->setFlat(true);
	stopMsgButoon->setFlat(true);
	tradeMsgButton->setFlat(true);
	positionButton->setFlat(true);
	accountButton->setFlat(true);
	mainButtonGroup = new QButtonGroup();
	mainButtonGroup->addButton(orderButton, 1);
	mainButtonGroup->addButton(stopMsgButoon, 2);
	mainButtonGroup->addButton(tradeMsgButton, 3);
	mainButtonGroup->addButton(positionButton, 4);
	mainButtonGroup->addButton(accountButton, 5);
	mainButtonGroup->setExclusive(true);
	orderButton->setChecked(true);
	connect(mainButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonChange(int)));
	QHBoxLayout *rightUp = new QHBoxLayout();
	QFrame *rightLine1 = new QFrame();
	rightLine1->setFrameShape(QFrame::VLine);
	rightLine1->setFrameShadow(QFrame::Sunken);
	QFrame *rightLine2 = new QFrame();
	rightLine2->setFrameShape(QFrame::VLine);
	rightLine2->setFrameShadow(QFrame::Sunken);
	QFrame *rightLine3 = new QFrame();
	rightLine3->setFrameShape(QFrame::VLine);
	rightLine3->setFrameShadow(QFrame::Sunken);
	QFrame *rightLine4 = new QFrame();
	rightLine4->setFrameShape(QFrame::VLine);
	rightLine4->setFrameShadow(QFrame::Sunken);

	withdrawButton = new QPushButton("����");
	withdrawButton->setObjectName("withdrawButton");
	withdrawButton->setFixedSize(62, 18);
	rightUp->setSpacing(2);
	rightUp->addWidget(orderButton);
	rightUp->addWidget(rightLine4);
	rightUp->addWidget(stopMsgButoon);
	rightUp->addWidget(rightLine1);
	rightUp->addWidget(tradeMsgButton);
	rightUp->addWidget(rightLine2);
	rightUp->addWidget(positionButton);
	rightUp->addWidget(rightLine3);
	rightUp->addWidget(accountButton);
	rightUp->addStretch();
	rightUp->addWidget(withdrawButton);
	orderTable = new OrderTable();
	tradeTable = new SumTable();
	positionTable = new PositionTable();
	accountTable = new AccountTable();
	stopOrderTable = new StopOrderTable();

	stackWidget = new QStackedWidget();
	stackWidget->addWidget(orderTable);
	stackWidget->addWidget(stopOrderTable);
	stackWidget->addWidget(tradeTable);
	stackWidget->addWidget(positionTable);
	stackWidget->addWidget(accountTable);

	
	connect(positionTable, SIGNAL(positonClose(Positions*)), this, SLOT(setpositonClose(Positions*)));

	QVBoxLayout *right = new QVBoxLayout();
	right->setSpacing(5);
	right->addLayout(rightUp);
	right->addWidget(stackWidget, 0);
	right->addWidget(new OrderTable());
	responseBox->setLayout(right);
/**********************************************�ܲ���************************************************/
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	m_pTitleBar = new TitleBar(this);
	m_pTitleBar->setObjectName("titleBar");
	installEventFilter(m_pTitleBar);

	QHBoxLayout *mainLayout = new QHBoxLayout();
	mainLayout->addWidget(tradeBox,1);
	mainLayout->addWidget(responseBox,6);
	mainLayout->setMargin(2);
	mainLayout->setSpacing(2);

	QVBoxLayout *m_pLayout = new QVBoxLayout();
	m_pLayout->addWidget(m_pTitleBar);
	m_pLayout->addLayout(mainLayout);
	m_pLayout->setSpacing(0);
	m_pLayout->setContentsMargins(0, 0, 0, 0);

	QWidget *mainW = new QWidget();
	mainW->setLayout(m_pLayout);
	mainW->setLayout(mainLayout);
	
	setCentralWidget(mainW);
	createStatusBur();	//����״̬��
	initController();
	
	//���ô�������
	setWindowTitle("AceTrader");
	QIcon icon;
	icon.addFile(QStringLiteral("ico/coin.ico"), QSize(), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon);
}

/************************************˽�к���*******************************************************/

//��ʼ��������
void MainWindow::initController() {
	
	connectController = make_shared<ConnectController>();
	queryController= make_shared<QueryController>();
	subController= make_shared<SubscribeController>();
	tradeController = make_shared<TradeController>();
	//���Ӱ�ť�����ӿ���������
	//connect(connectButton, SIGNAL(clicked()), connectController.get(), SLOT(connectServer()));
	//connect(connectButton, SIGNAL(clicked()), this, SLOT(connectNoFocus()));
	connect(settingButton, SIGNAL(clicked()), this, SLOT(showSettingDialog()));
	//������ť
	connect(bsButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(tradeServer(int)));
	//������ť
	connect(withdrawButton, SIGNAL(clicked()), this, SLOT(cancelOrder()));

	/*connect(connectController.get(), SIGNAL(connecting()), this, SLOT(statusConnecting()));
	connect(connectController.get(), SIGNAL(tradeConnecting()), this, SLOT(tradeStatusConnecting()));
	connect(connectController.get(), SIGNAL(connectFailed()), this, SLOT(statusConnectFailed()));
	connect(connectController.get(), SIGNAL(tradeConnectFailed()), this, SLOT(tradeStatusConnectFailed()));
	connect(connectController.get(), SIGNAL(loginSuccess()), this, SLOT(statusConnectSuccess()));
	connect(connectController.get(), SIGNAL(loginSuccess()), connectController.get(), SLOT(tradeConnectServer()));
	connect(connectController.get(), SIGNAL(tradeLoginSuccess()), this, SLOT(tradeStatusConnectSuccess()));*/

	connect(connectController.get(), SIGNAL(connecting()), this, SIGNAL(connecting()));
	connect(connectController.get(), SIGNAL(connectFailed()), this, SIGNAL(connectFailed()));
	connect(connectController.get(), SIGNAL(loginSuccess()), this, SLOT(statusConnectSuccess()));
	connect(connectController.get(), SIGNAL(loginSuccess()), connectController.get(), SLOT(tradeConnectServer()));
	connect(connectController.get(), SIGNAL(tradeConnecting()), this, SIGNAL(tradeConnecting()));
	connect(connectController.get(), SIGNAL(tradeConnectFailed()), this, SIGNAL(tradeConnectFailed()));

	connect(connectController.get(), SIGNAL(loginFailed(QString)), this, SIGNAL(loginFailed(QString)));
	/************************************��ѯ����****************************************/
	//1�����׵�¼�󣬲�ѯ�Ƿ�ȷ����Ϣ
	connect(connectController.get(), SIGNAL(tradeLoginSuccess()), this, SLOT(tradeStatusConnectSuccess()));
	connect(connectController.get(), SIGNAL(tradeLoginSuccess()), queryController.get(), SLOT(querySettlementInfoConfirm()));
	//չʾȷ����Ϣ
	connect(queryController.get(), SIGNAL(querySettlementInfoSuccess()), this, SLOT(showConfirmDialog()));
	
	connect(queryController.get(), SIGNAL(queryOrderSuccess()), this, SIGNAL(allSuccess()));
	//���±��
	connect(queryController.get(), SIGNAL(queryOrderSuccess()), orderTable, SLOT(update()));
	connect(queryController.get(), SIGNAL(queryOrderSuccess()), stopOrderTable, SLOT(update()));
	connect(queryController.get(), SIGNAL(queryTradeSuccess()), tradeTable, SLOT(update()));
	connect(queryController.get(), SIGNAL(queryInvestorPositionSuccess()), subController.get(), SLOT(subscribePositionIns()));
	connect(queryController.get(), SIGNAL(queryInvestorPositionSuccess()), positionTable, SLOT(update()));
	connect(queryController.get(), SIGNAL(queryTradingAccountSuccess()), accountTable, SLOT(update()));
	connect(queryController.get(), SIGNAL(updateAccount()), accountTable, SLOT(update()));
	connect(queryController.get(), SIGNAL(updatePositon()), positionTable, SLOT(update()));
	
	connect(queryController.get(), SIGNAL(querySignal(QString)), this, SIGNAL(querySignal(QString)));
	
	connect(tradeController.get(), SIGNAL(updateOrder()), orderTable, SLOT(update()));
	connect(tradeController.get(), SIGNAL(updateOrder()), stopOrderTable, SLOT(update()));
	connect(tradeController.get(), SIGNAL(updateTrade()), tradeTable, SLOT(update()));
	
}

//����״̬��
void MainWindow::createStatusBur() {

	//��ʼ��״̬��ǩ
	mdstatusLabel = new QLabel(OFFLINE);
	mdstatusLabel->setObjectName("mdstatusLabel");
	mdstatusLabel->setFrameShape(QFrame::Panel); // ���ñ�ǩ��״
	mdstatusLabel->setFrameShadow(QFrame::Sunken); // ���ñ�ǩ��Ӱ
	tradestatusLabel = new QLabel(TRADE_OFFLINE);
	tradestatusLabel->setObjectName("tradestatusLabel");
	tradestatusLabel->setFrameShape(QFrame::Panel); // ���ñ�ǩ��״
	tradestatusLabel->setFrameShadow(QFrame::Sunken); // ���ñ�ǩ��Ӱ

	statusBar()->addPermanentWidget(mdstatusLabel);
	statusBar()->addPermanentWidget(tradestatusLabel);
}


/************************************�ۺ���*********************************************************/

//���¼۸�
void MainWindow::updatePrice() {
	
	QString code = instruCombo->currentText();
	Instrument* i = instruList[code];
	askPriceLabel->setText(" "+QString::number(i->askPrice,'f',2)+" "+QString::number(i->askVolumn));
	lastPriceLabel->setText(" "+QString::number(i->lastPrice, 'f', 2));
	bidPriceLabel->setText(" "+QString::number(i->bidPrice, 'f', 2)+" "+QString::number(i->bidVolumn));

	if (PriceFlag)
		priceSpin->mysetValue(QString::number(i->lastPrice, 'f', 2).toDouble());

}

void MainWindow::setAskPrice(const QString& text){
	priceSpin->clearFocus();
	PriceFlag = false;
	priceSpin->mysetValue(text.toDouble());
}

void MainWindow::setLastPrice(const QString& text) {
	priceSpin->clearFocus();
	PriceFlag = true;
	priceSpin->mysetValue(text.toDouble());
}

void MainWindow::setBidPrice(const QString& text) {
	priceSpin->clearFocus();
	PriceFlag = false;
	priceSpin->mysetValue(text.toDouble());
}


//���ӳɹ�
void MainWindow::statusConnectSuccess() {
	subController->setReceiver(connectController->getReceiver());
}

//�������ӳɹ�
void MainWindow::tradeStatusConnectSuccess() {

	mdstatusLabel->setText(ONLINE);
	tradestatusLabel->setText(TRADE_ONLINE);

	queryController->setTrader(connectController->getTrader());
	tradeController->setTrader(connectController->getTrader());
}


//չʾ���ý���
void MainWindow::showSettingDialog(){
	if (setDialog == nullptr) {
		setDialog = new SettingDialog();
		connect(setDialog, SIGNAL(startSubscribe()), this, SLOT(showInstru()));
	}
	setDialog->showDialog();
}
//չʾȷ����Ϣ
void MainWindow::showConfirmDialog(){
	if (confirmDialog == nullptr) {
		confirmDialog = new ConfirmDialog();
		connect(confirmDialog, SIGNAL(confirm()), queryController.get(), SLOT(settlementInfoConfirm()));
	}
	confirmDialog->showDialog();
}

void MainWindow::showInstru(){
	instruCombo->clear();
	for (auto iter = allInstruPara.begin(); iter != allInstruPara.end(); iter++) {
		instruCombo->addItem(iter->first);
	}
}


void MainWindow::keyPressEvent(QKeyEvent * k) {
	switch (k->key()) {
	case Qt::Key_F1:
		instruCombo->setFocus();
		instruCombo->showPopup();
		qDebug() << "F1������";
		break;
	case Qt::Key_F2:
		numberSpin->setFocus();
		numberSpin->selectAll();
		qDebug() << "F2������";
		break;
	case Qt::Key_F3:
		priceSpin->setFocus();
		priceSpin->selectAll();
		qDebug() << "F3������";
		break;
	case Qt::Key_F4:
		multiSpin->setFocus();
		multiSpin->selectAll();
		qDebug() << "F4������";
		break;
	case Qt::Key_F5:
		emptySpin->setFocus();
		emptySpin->selectAll();
		qDebug() << "F5������";
		break;
	case Qt::Key_F6:
		waitCheck->setFocus();
		if (waitCheck->isChecked())
			waitCheck->setChecked(false);
		else
			waitCheck->setChecked(true);
		qDebug() << "F6������";
		break;
	case Qt::Key_F7:
		if(stopCheck->isChecked())
			stopCheck->setChecked(false);
		else
			stopCheck->setChecked(true);
		stopSpin->setFocus();
		stopSpin->selectAll();
		qDebug() << "F7������";
		break;
	case Qt::Key_B:
		buyButton->clicked(true);
		break;

	}
}

void MainWindow::buttonChange(int buttonId){
	if (buttonId == 1) {
		stackWidget->setCurrentIndex(0);
		withdrawButton->setEnabled(true);
		buyButton->setEnabled(true);
		sellButton->setEnabled(true);
	}
	else if (buttonId == 2) {
		stackWidget->setCurrentIndex(1);
		withdrawButton->setEnabled(true);
		buyButton->setEnabled(true);
		sellButton->setEnabled(true);
	}
	else if (buttonId == 3) {
		stackWidget->setCurrentIndex(2);
		withdrawButton->setEnabled(false);
		buyButton->setEnabled(true);
		sellButton->setEnabled(true);
	}
	else if (buttonId == 4) {
		stackWidget->setCurrentIndex(3);
		withdrawButton->setEnabled(false);
		buyButton->setEnabled(true);
		sellButton->setEnabled(true);
	}

	else if (buttonId == 5) {
		stackWidget->setCurrentIndex(4);
		withdrawButton->setEnabled(false);
		buyButton->setEnabled(true);
		sellButton->setEnabled(true);
	}
}

void MainWindow::startConnect(){
	connectController->connectServer();
}

void MainWindow::startSub(int num){
	if (num == -1)
		return;
	PriceFlag = true;
	QString code = instruCombo->itemText(num);
	//���ò���
	InstruParameter *p = allInstruPara[code];
	multiSpin->setValue(p->MultiDefault);
	emptySpin->setValue(p->EmptyDefault);
	stopSpin->setValue(p->StopDefault);
	qDebug() << "���ò�����" << instruList[code]->PriceTick;
	numberSpin->setValue(DefaultVolume);
	priceSpin->setSingleStep(instruList[code]->PriceTick);
	qDebug() << "��ʼ���ģ�" << code;
	subController->subscribe(code);
	updatePriceTimer->start(500);
}

void MainWindow::connectNoFocus(){
	this->setFocus();
}

void MainWindow::tradeServer(int d){
	
	orderButton->setChecked(true);
	mainButtonGroup->buttonClicked(1);

	//���׺�Լ
	QString c = instruCombo->currentText();
	if (c == "")
		return;

	OrderParameter *op = new OrderParameter(c);
	double priceTick = instruList[c]->PriceTick;
	//����ƽ��
	if (openRadio->isChecked())
		op->offset_flag = THOST_FTDC_OF_Open;
	else if (closeRadio->isChecked())
		op->offset_flag = THOST_FTDC_OF_Close;
	else if (todayRadio->isCheckable())
		op->offset_flag = THOST_FTDC_OF_CloseToday;
	//����
	op->num = numberSpin->text().toInt();
	//�۸�
	op->price = priceSpin->text().toDouble();
	if (d == 1) {
		//��������
		op->direction = THOST_FTDC_D_Buy;                                              //�ͼ���
		//ƽ�ּ۸�
		op->close_price = priceSpin->text().toDouble() + (multiSpin->text().toDouble() * priceTick); //�߼���
		if (stopCheck->isChecked()) {
			//ֹ��۸�
			op->stop_price = priceSpin->text().toDouble() - (stopSpin->text().toDouble() * priceTick); //����ֹ���
			//ֹ���־
			op->condition = THOST_FTDC_CC_LastPriceLesserEqualStopPrice;
		}
	}
	else if (d == 2) {
		//��������
		op->direction = THOST_FTDC_D_Sell;
		//ƽ�ּ۸�
		op->close_price = priceSpin->text().toDouble() - (emptySpin->text().toDouble() * priceTick); //�ͼ���
		if (stopCheck->isChecked()) {
			//ֹ��۸�
			op->stop_price = priceSpin->text().toDouble() + (stopSpin->text().toDouble() * priceTick);
			//ֹ���־
			op->condition = THOST_FTDC_CC_LastPriceGreaterEqualStopPrice;
		}
	}
	if (waitCheck->isChecked())
		op->timeCondition = THOST_FTDC_TC_GFD;                  //��Ч������: ������Ч
	else
		op->timeCondition = THOST_FTDC_TC_IOC;                  //������ɣ�������

	tradeController->tradeServer(op);
}

void MainWindow::cancelOrder(){
	int row = -1;
	QString id;

	if (stackWidget->currentIndex() == 0) {
		row = orderTable->currentRow();
		if (row >= 0)
			id = orderTable->item(row, 0)->text();
		else
			return;
	}
	else {
		row = stopOrderTable->currentRow();
		if (row >= 0)
			id = stopOrderTable->item(row, 0)->text();
		else
			return;
	}
	
	tradeController->reqOrderAction(id);
}

void MainWindow::setpositonClose(Positions * p){
	buyButton->setEnabled(true);
	sellButton->setEnabled(true);
	
	int index = instruCombo->findText(p->InstrumentID);
	if (index < 0) {
		QMessageBox::information(this, "����","���ڽ�����������Ӻ�Լ����<"+ p->InstrumentID+">");
		return;
	}
	
	instruCombo->setCurrentIndex(index);
	
	Instrument* i = instruList[p->InstrumentID];

	if (p->TodayPosition > 0) {
		todayRadio->setChecked(true);
		numberSpin->setValue(p->TodayPosition);
	}
	else {
		closeRadio->setChecked(true);
		numberSpin->setValue(p->Position);
	}

	if (p->PosiDirection == '2') { //��
		buyButton->setEnabled(false);
		priceSpin->mysetValue(QString::number(i->bidPrice, 'f', 2).toDouble());
	}
	else {
		sellButton->setEnabled(false);
		priceSpin->mysetValue(QString::number(i->askPrice, 'f', 2).toDouble());
	}

}

void MainWindow::OnPriceValueChanged(double n){
	if (priceSpin->hasFocus()) {
		qDebug() << "�۸��Ϊ��" << n;
		PriceFlag = false;
	}
		
}
