#include "SettingDialog.h"
#include <QBoxLayout>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

SettingDialog::SettingDialog(){
	insTable = new InsTable();
	insTable->setObjectName("insTable");
	subTable = new SubscribeTable();
	subTable->setObjectName("subTable");
	connect(insTable, SIGNAL(updateSub()), subTable, SLOT(updateForAdd()));
	
	//按钮
	okButton = new QPushButton("确定");
	okButton->setFixedSize(75, 23);
	cancelButton = new QPushButton("取消");
	cancelButton->setFixedSize(75, 23);
	connect(okButton, SIGNAL(clicked()), this, SLOT(updateIni()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(hide()));
	connect(cancelButton, SIGNAL(clicked()), subTable, SLOT(updateForCancel()));
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);
	SHFE_Button = new QPushButton("上海期货");
	DCE_Button = new QPushButton("大连商品");
	CZCE_Button = new QPushButton("郑州商品");
	CFFEX_Button = new QPushButton("中国金融");
	SHFE_Button->setCheckable(true);
	DCE_Button->setCheckable(true);
	CZCE_Button->setCheckable(true);
	CFFEX_Button->setCheckable(true);
	SHFE_Button->setFixedSize(96, 23);
	DCE_Button->setFixedSize(96, 23);
	CZCE_Button->setFixedSize(96, 23);
	CFFEX_Button->setFixedSize(96, 23);

	buttonGroup = new QButtonGroup();
	buttonGroup->addButton(SHFE_Button, 1);
	buttonGroup->addButton(DCE_Button, 2);
	buttonGroup->addButton(CZCE_Button, 3);
	buttonGroup->addButton(CFFEX_Button, 4);
	buttonGroup->setExclusive(true);
	connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonJudge(int)));
	QHBoxLayout *buttonUp = new QHBoxLayout();
	buttonUp->addWidget(SHFE_Button);
	buttonUp->addWidget(DCE_Button);
	QHBoxLayout *buttonDown = new QHBoxLayout();
	buttonDown->addWidget(CZCE_Button);
	buttonDown->addWidget(CFFEX_Button);

	QHBoxLayout *add = new QHBoxLayout();
	add_Button = new QPushButton("添加合约");
	add_Button->setFixedSize(75, 23);
	connect(add_Button, SIGNAL(clicked()), insTable, SLOT(updateForAdd()));
	add->addWidget(add_Button);
	add->addStretch();
	QHBoxLayout *del = new QHBoxLayout();
	delete_Button = new QPushButton("删除合约");
	delete_Button->setFixedSize(75, 23);
	connect(delete_Button, SIGNAL(clicked()), subTable, SLOT(updateForDel()));
	del->addWidget(delete_Button);
	del->addStretch();

	defaultNumLabel = new QLabel("默认交易数量：");
	defaultNumLabel->setObjectName("defaultNumLabel");
	defaultNumLabel->setFixedWidth(85);
	defaultNumLabel->setFixedHeight(22);
	defaultNumSpin = new QSpinBox();
	defaultNumSpin->setFixedWidth(66);
	defaultNumSpin->setFixedHeight(22);
	defaultNumSpin->setValue(DefaultVolume);

	QHBoxLayout *dnLayout = new QHBoxLayout();
	dnLayout->addWidget(defaultNumLabel);
	dnLayout->addWidget(defaultNumSpin);
	dnLayout->addStretch();

	QVBoxLayout *left = new QVBoxLayout();
	left->addLayout(dnLayout);
	left->addWidget(subTable);
	left->addLayout(del);
	QVBoxLayout *right = new QVBoxLayout();
	right->addLayout(buttonUp);
	right->addLayout(buttonDown);
	right->addWidget(insTable);
	right->addLayout(add);
	//整体布局
	QHBoxLayout *up = new QHBoxLayout();
	up->addLayout(left,3);
	up->addLayout(right,1);
	QFrame *line = new QFrame();
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(up);
	mainLayout->addWidget(line);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
	//设置
	setWindowTitle("交易合约设置");
	QIcon icon;
	icon.addFile(QStringLiteral("ico/coin.ico"), QSize(), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon);
	setModal(true);
	resize(620, 380);

	hide();
}

void SettingDialog::showDialog(){
	SHFE_Button->setChecked(true);
	temp = allInstruPara;
	show();
}

/*******************************槽函数**************************************/
void SettingDialog::buttonJudge(int buttonId) {
	if (buttonId == 1) {
		insTable->updateSHFE();
	}
	else if (buttonId == 2){
		insTable->updateDCE();
	}
	else if (buttonId == 3) {
		insTable->updateCZCE();
	}
	else if (buttonId == 4) {
		insTable->updateCFFEX();
	}
}

void SettingDialog::updateIni(){
	QFile iniFile("ini/parameter.ini");
	if (!iniFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QMessageBox::information(this, "错误", "打开parameter.ini发生错误");
		abort();
	}
	QTextStream out(&iniFile);
	out << defaultNumSpin->text() << endl;

	DefaultVolume = defaultNumSpin->text().toInt();

	for (auto iter = allInstruPara.begin(); iter != allInstruPara.end(); iter++) {
		InstruParameter *ip = iter->second;
		out << iter->first << " " << ip->MultiDefault << " " << ip->EmptyDefault << " " << ip->StopDefault << endl;
	}
	out.flush();
	iniFile.close();
	emit startSubscribe();
	hide();
}
