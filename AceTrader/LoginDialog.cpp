#include "LoginDialog.h"

#include <QBoxLayout>
#include <GVAR.h>
#include <Qdebug>
#include <QStyledItemDelegate>
#include <QStatusBar>
#include <QMessageBox>
#include <QApplication>

using std::shared_ptr;
using std::make_shared;
using std::make_pair;

LoginDialog::LoginDialog(){
	this->resize(360,200);
	mw = new MainWindow();
	mw->setObjectName("MainWindow");
	mw->resize(1100, 200);
	mw->setFocus();

	company = new QLabel("经纪公司");
	server = new QLabel("服务器");
	username = new QLabel("用户名");
	psw = new QLabel("密	码");
	company->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	server->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	username->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	psw->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	companyCombo = new QComboBox();

	connect(companyCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(changeCompany(int)));
	
	serverCombo = new QComboBox();
	nameLine = new QLineEdit();
	pswLine = new QLineEdit();

	nameLine->setObjectName("nameLine");
	nameLine->setAttribute(Qt::WA_InputMethodEnabled, false);
	nameLine->setStyleSheet("QLineEdit {  border: 1px inset #AAAAAA; height: 20px; font-size: 14px;}");
	
	pswLine->setObjectName("pswLine");
	pswLine->setEchoMode(QLineEdit::Password);
	pswLine->setAttribute(Qt::WA_InputMethodEnabled, false);
	pswLine->setStyleSheet("QLineEdit {  border: 1px inset #AAAAAA; height: 20px; lineedit-password-character: 42;}");

	QStyledItemDelegate *itemDelegate = new QStyledItemDelegate();
	companyCombo->setItemDelegate(itemDelegate);
	serverCombo->setItemDelegate(itemDelegate);

	loginButton = new QPushButton("登录");
	loginButton->setFixedSize(75, 23);
	cancelButoon = new QPushButton("取消");
	cancelButoon->setFixedSize(75, 23);
	connect(loginButton, SIGNAL(clicked()), this, SLOT(startConnect()));
	connect(pswLine, SIGNAL(returnPressed()), loginButton, SIGNAL(clicked()), Qt::UniqueConnection);

	connect(mw, SIGNAL(connecting()), this, SLOT(statusConnecting()));
	connect(mw, SIGNAL(connectFailed()), this, SLOT(statusConnectFailed()));
	connect(mw, SIGNAL(tradeConnecting()), this, SLOT(tradeStatusConnecting()));
	connect(mw, SIGNAL(tradeConnectFailed()), this, SLOT(tradeStatusConnectFailed()));
	connect(mw, SIGNAL(querySignal(QString)), this, SLOT(statusQuery(QString)));
	connect(mw, SIGNAL(allSuccess()), this, SLOT(showMainWindow()));
	connect(mw, SIGNAL(loginFailed(QString)), this, SLOT(statusLoginFailed(QString)));

	connect(cancelButoon, SIGNAL(clicked()), this, SLOT(close()));

	setWindowTitle("AceTrader");

	QIcon icon;
	icon.addFile(QStringLiteral("ico/coin.ico"), QSize(), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon);
	setModal(true);

	QHBoxLayout *first = new QHBoxLayout();
	QHBoxLayout *second = new QHBoxLayout();
	QHBoxLayout *third = new QHBoxLayout();
	QHBoxLayout *fourth = new QHBoxLayout();
	QHBoxLayout *fifth = new QHBoxLayout();

	first->addSpacing(30);
	first->addWidget(company,1);
	first->addWidget(companyCombo,3);
	first->addSpacing(50);
	second->addSpacing(30);
	second->addWidget(server,1);
	second->addWidget(serverCombo,3);
	second->addSpacing(50);
	third->addSpacing(30);
	third->addWidget(username,1);
	third->addWidget(nameLine,3);
	third->addSpacing(50);
	fourth->addSpacing(30);
	fourth->addWidget(psw,1);
	fourth->addWidget(pswLine,3);
	fourth->addSpacing(50);
	
	fifth->addStretch();
	fifth->addWidget(loginButton);
	fifth->addSpacing(37);
	fifth->addWidget(cancelButoon);
	fifth->addStretch();

	statusLabel = new QLabel("");
	statusLabel->setObjectName("statusLabel");
	statusLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addSpacing(8);
	mainLayout->addLayout(first);
	mainLayout->addSpacing(6);
	mainLayout->addLayout(second);
	mainLayout->addSpacing(6);
	mainLayout->addLayout(third);
	mainLayout->addSpacing(6);
	mainLayout->addLayout(fourth);
	mainLayout->addSpacing(6);
	mainLayout->addLayout(fifth);
	mainLayout->addWidget(statusLabel);
	mainLayout->setContentsMargins(10, 10, 10, 0);

	setLayout(mainLayout);

	for (auto iter = loginPar.begin(); iter != loginPar.end(); iter++) {
		companyCombo->addItem((*iter)->BrokerName);
	}

	nameLine->setText(loginPar.at(0)->UserID);
}
void LoginDialog::showMainWindow() {
	hide();
	mw->show();
}
void LoginDialog::startConnect() {
	//传递参数
	int index = companyCombo->currentIndex();
	LoginParameter *lp = loginPar.at(index);
	QString severName = serverCombo->currentText();
	Address *address = (lp->Server).at(severName);
	TD_FRONT_ADDRESS = "tcp://" + address->TradingAddress;
	MD_FRONT_ADDRESS = "tcp://" + address->MDAddress;
	BROKER = lp->BrokerID;
	USER_NAME = nameLine->text();
	PASSWORD = pswLine->text();

	/*qDebug() << TD_FRONT_ADDRESS;
	qDebug() << MD_FRONT_ADDRESS;
	qDebug() << BROKER;
	qDebug() << USER_NAME;
	qDebug() << PASSWORD;*/

	//开始登陆
	mw->startConnect();
}

void LoginDialog::changeCompany(int d){
	serverCombo->clear();
	for (auto iter = loginPar.at(d)->Server.begin(); iter != loginPar.at(d)->Server.end(); iter++) {
		serverCombo->addItem((*iter).first);
	}
	nameLine->setText(loginPar.at(d)->UserID);
}

//状态变更为正在连接,连接按钮不可用
void LoginDialog::statusConnecting() {
	statusLabel->setText("登录行情服务器...");
}

//连接失败
void LoginDialog::statusConnectFailed() {
	QMessageBox::information(this, "连接失败", "请查看（行情）前置机地址是否正确");
}

void LoginDialog::tradeStatusConnecting() {
	statusLabel->setText("登录交易服务器...");
}

void LoginDialog::tradeStatusConnectFailed() {
	QMessageBox::information(this, "连接失败", "请查看（交易）前置机地址是否正确");
}

void LoginDialog::statusQuery(QString msg){
	QApplication::beep();
	statusLabel->setText(msg);
}

void LoginDialog::statusLoginFailed(QString msg){
	QApplication::beep();
	statusLabel->setText(msg);
}
