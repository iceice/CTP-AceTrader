#pragma once

#include <QDialog>
#include <QPushButton>
#include <QButtonGroup>
#include "InsTable.h"
#include "SubscribeTable.h"
#include <GVAR.h>
#include <QLabel>
#include <QSpinBox>

class SettingDialog : public QDialog{
	Q_OBJECT
public:
	SettingDialog();
	void showDialog();
private:
	QLabel * defaultNumLabel;
	QSpinBox *defaultNumSpin;
	InsTable * insTable;
	SubscribeTable *subTable;
	QPushButton *okButton;
	QPushButton *cancelButton;
	QPushButton *add_Button;
	QPushButton *delete_Button;
	QPushButton *SHFE_Button;  //上海交易所
	QPushButton *CZCE_Button;  //郑州交易所
	QPushButton *DCE_Button;   //大连交易所
	QPushButton *CFFEX_Button; //中国金融交易所
	QButtonGroup *buttonGroup;
	
	
	private slots:
	void buttonJudge(int buttonId);
	void updateIni();
	
signals:
	void startSubscribe();
};
