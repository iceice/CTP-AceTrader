#include "AccountTable.h"
#include "GVAR.h"
#include "Account.h"
#include <QHeaderView>
#include <QScrollBar>

#if _MSC_VER >= 1700
#pragma execution_character_set("utf-8")
#endif

AccountTable::AccountTable(){
	this->setColumnCount(4);
	this->verticalHeader()->setVisible(false);
	this->horizontalHeader()->setVisible(false);
	this->setSelectionMode(QAbstractItemView::NoSelection);
	//this->setFocusPolicy(Qt::NoFocus);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setAlternatingRowColors(true);
	this->setStyleSheet("QTableView { alternate-background-color: #FFFFE1; background-color: white; border: 1px solid #7F9DB9; }");
	this->verticalHeader()->setDefaultSectionSize(20);

	this->horizontalScrollBar()->setStyleSheet("QScrollBar{height: 16px; }");
	this->verticalScrollBar()->setStyleSheet("QScrollBar{width: 16px; }");

	this->setColumnWidth(0, 150);
	this->setColumnWidth(1, 150);
	this->setColumnWidth(2, 150);
	this->setColumnWidth(3, 150);
	update();
}

AccountTable::~AccountTable(){}

void AccountTable::focusOutEvent(QFocusEvent * event)
{
	this->clearSelection();
}

void AccountTable::update(){
	
	this->clearContents();
	int rowCount = this->rowCount();
	for (; rowCount >= 0; rowCount--) {
		this->removeRow(rowCount);
	}

	this->insertRow(0);
	this->setItem(0, 0, new QTableWidgetItem("��̬Ȩ��"));
	this->setItem(0, 1, new QTableWidgetItem(QString::number(ACCOUNT->StaticInterest, 'f', 2)));
	this->setItem(0, 2, new QTableWidgetItem("��̬Ȩ��"));
	this->setItem(0, 3, new QTableWidgetItem(QString::number(ACCOUNT->DynamicInterest, 'f', 2)));
	this->insertRow(1);
	this->setItem(1, 0, new QTableWidgetItem("�����ʽ�"));
	this->setItem(1, 1, new QTableWidgetItem(QString::number(ACCOUNT->Available, 'f', 2)));
	this->setItem(1, 2, new QTableWidgetItem("��ȡ�ʽ�"));
	this->setItem(1, 3, new QTableWidgetItem(QString::number(ACCOUNT->WithdrawQuota, 'f', 2)));
	this->insertRow(2);
	this->setItem(2, 0, new QTableWidgetItem("���ᱣ֤��"));
	this->setItem(2, 1, new QTableWidgetItem(QString::number(ACCOUNT->FrozenMargin, 'f', 2)));
	this->setItem(2, 2, new QTableWidgetItem("�ֲ�ӯ��"));
	this->setItem(2, 3, new QTableWidgetItem(QString::number(ACCOUNT->PositionProfit, 'f', 2)));
	this->insertRow(3);
	this->setItem(3, 0, new QTableWidgetItem("����������"));
	this->setItem(3, 1, new QTableWidgetItem(QString::number(ACCOUNT->FrozenCommission, 'f', 2)));
	this->setItem(3, 2, new QTableWidgetItem("ƽ��ӯ��"));
	this->setItem(3, 3, new QTableWidgetItem(QString::number(ACCOUNT->CloseProfit, 'f', 2)));
	this->insertRow(4);
	this->setItem(4, 0, new QTableWidgetItem("������"));
	this->setItem(4, 1, new QTableWidgetItem(QString::number(ACCOUNT->Commission, 'f', 2)));
	this->setItem(4, 2, new QTableWidgetItem("���ն�"));
	this->setItem(4, 3, new QTableWidgetItem(QString::number(ACCOUNT->Risk, 'f', 2) + "%"));
	this->insertRow(5);
	this->setItem(5, 0, new QTableWidgetItem("ռ�ñ�֤��"));
	this->setItem(5, 1, new QTableWidgetItem(QString::number(ACCOUNT->CurrMargin, 'f', 2)));
	this->setItem(5, 2, new QTableWidgetItem("���֤��"));
	this->setItem(5, 3, new QTableWidgetItem(QString::number(ACCOUNT->DeliveryMargin, 'f', 2)));
	this->insertRow(6);
	this->setItem(6, 0, new QTableWidgetItem("�ϴν���׼����"));
	this->setItem(6, 1, new QTableWidgetItem(QString::number(ACCOUNT->PreBalance, 'f', 2)));
	this->setItem(6, 2, new QTableWidgetItem("�ʽ���"));
	this->setItem(6, 3, new QTableWidgetItem(QString::number(ACCOUNT->CashIn, 'f', 2)));
	this->insertRow(7);
	this->setItem(7, 0, new QTableWidgetItem("�ϴ����ö��"));
	this->setItem(7, 1, new QTableWidgetItem(QString::number(ACCOUNT->PreCredit, 'f', 2)));
	this->setItem(7, 2, new QTableWidgetItem("���ý��"));
	this->setItem(7, 3, new QTableWidgetItem(QString::number(ACCOUNT->Credit, 'f', 2)));
	this->insertRow(8);
	this->setItem(8, 0, new QTableWidgetItem("�ϴ���Ѻ���"));
	this->setItem(8, 1, new QTableWidgetItem(QString::number(ACCOUNT->PreMortgage, 'f', 2)));
	this->setItem(8, 2, new QTableWidgetItem("��Ѻ���"));
	this->setItem(8, 3, new QTableWidgetItem(QString::number(ACCOUNT->Mortgage, 'f', 2)));
	this->insertRow(9);
	this->setItem(9, 0, new QTableWidgetItem("�������"));
	this->setItem(9, 1, new QTableWidgetItem(QString::number(ACCOUNT->Deposit, 'f', 2)));
	this->setItem(9, 2, new QTableWidgetItem("���ճ���"));
	this->setItem(9, 3, new QTableWidgetItem(QString::number(ACCOUNT->Withdraw, 'f', 2)));

}