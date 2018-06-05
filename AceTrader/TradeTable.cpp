#include "TradeTable.h"
#include <QStringList>
#include <QHeaderView>
#include "GVAR.h"
#include "ItemDelegate.h"
#include <QScrollBar>

#if _MSC_VER >= 1700
#pragma execution_character_set("utf-8")
#endif

TradeTable::TradeTable(){
	this->setColumnCount(10);
	QStringList header;
	header << "�������" << "��Լ����" << "����" << "��ƽ" << "���ּ۸�" << "�ɽ��۸�" << "���" << "����" << "�ɽ�ʱ��" << "�ɽ�����";
	this->setHorizontalHeaderLabels(header);
	
	this->verticalHeader()->setVisible(false);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setFocusPolicy(Qt::NoFocus);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setShowGrid(false);
	this->setStyleSheet("QTableView {background-color: white; border: 1px solid #7F9DB9; }");
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{ background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, stop : 0 #FFFFFF, stop: 1.0 #F0F0F0); border: 0px solid #E0DDDC; border-bottom: 1px solid #787878; border-right: 1px solid #787878; height:17px; font-size: 12px;}");
	this->verticalHeader()->setDefaultSectionSize(18);
	this->horizontalHeader()->setHighlightSections(false);

	this->horizontalScrollBar()->setStyleSheet("QScrollBar{height: 16px; }");
	this->verticalScrollBar()->setStyleSheet("QScrollBar{width: 16px; }");

	connect(this->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));

	this->setItemDelegate(new ItemDelegate());
	this->setColumnWidth(0, 70);
	this->setColumnWidth(1, 70);
	this->setColumnWidth(2, 45);
	this->setColumnWidth(3, 65);
	this->setColumnWidth(4, 80);
	this->setColumnWidth(5, 80);
	this->setColumnWidth(6, 80);
	this->setColumnWidth(7, 80);
	this->setColumnWidth(8, 110);
	this->setColumnWidth(9, 110);
	
	//this->horizontalHeader()->setStretchLastSection(true);
}

TradeTable::~TradeTable(){

}

void TradeTable::update() {
	//���
	this->clearContents();
	int rowCount = this->rowCount();
	for (; rowCount >= 0; rowCount--) {
		this->removeRow(rowCount);
	}

	int row = 0;
	for (auto iter = allTrade.rbegin(); iter != allTrade.rend(); iter++) {
		Trade *i = allTrade[iter->first];
		Order *order = allOrder[iter->first];

		QTableWidgetItem *first = new QTableWidgetItem();
		QTableWidgetItem *second = new QTableWidgetItem();
		QTableWidgetItem *third = new QTableWidgetItem();
		QTableWidgetItem *forth = new QTableWidgetItem();
		QTableWidgetItem *fifth = new QTableWidgetItem();
		QTableWidgetItem *sixth = new QTableWidgetItem();
		QTableWidgetItem *seventh = new QTableWidgetItem();
		QTableWidgetItem *eighth = new QTableWidgetItem();
		first->setData(Qt::DisplayRole, i->OrderSysID.toInt());
		first->setTextAlignment(Qt::AlignCenter);
		second->setText(i->InstrumentID);
		second->setTextAlignment(Qt::AlignCenter);
		//��������
		if (i->Direction == '0') {
			third->setText("��");
			third->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			third->setTextColor(QColor(255, 0, 0));//��ɫ
		}
		else {
			third->setText("��");
			third->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
			third->setTextColor(QColor(0, 128, 0));//��ɫ
		}
		//��Ͽ�ƽ��־
		if (i->OffsetFlag == '0')
			forth->setText("����");
		else if (i->OffsetFlag == '1')
			forth->setText("ƽ��");
		else if (i->OffsetFlag == '2')
			forth->setText("ǿƽ");
		else if (i->OffsetFlag == '3')
			forth->setText("ƽ��");
		else if (i->OffsetFlag == '4')
			forth->setText("ƽ��");
		else if (i->OffsetFlag == '5')
			forth->setText("ǿ��");
		else if (i->OffsetFlag == '6')
			forth->setText("����ǿƽ");
		forth->setTextColor(QColor(0, 0, 255)); //��ɫ
		forth->setTextAlignment(Qt::AlignCenter);
		fifth->setText(QString::number(i->Price));
		fifth->setTextAlignment(Qt::AlignCenter);
		sixth->setText(QString::number(i->Volume));
		sixth->setTextAlignment(Qt::AlignCenter);
		seventh->setText(i->TradeTime);
		seventh->setTextAlignment(Qt::AlignCenter);
		eighth->setText(i->TradeDate);
		eighth->setTextAlignment(Qt::AlignCenter);
		this->insertRow(row);
		this->setItem(row, 0, first);
		this->setItem(row, 1, second);
		this->setItem(row, 2, third);
		this->setItem(row, 3, forth);
		this->setItem(row, 4, fifth);
		this->setItem(row, 5, sixth);
		this->setItem(row, 6, seventh);
		this->setItem(row, 7, eighth);
		row++;
	}
	//this->sortByColumn(6, Qt::DescendingOrder);
}
