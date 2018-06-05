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
	QPushButton *SHFE_Button;  //�Ϻ�������
	QPushButton *CZCE_Button;  //֣�ݽ�����
	QPushButton *DCE_Button;   //����������
	QPushButton *CFFEX_Button; //�й����ڽ�����
	QButtonGroup *buttonGroup;
	
	
	private slots:
	void buttonJudge(int buttonId);
	void updateIni();
	
signals:
	void startSubscribe();
};
