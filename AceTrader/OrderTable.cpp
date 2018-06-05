#include "OrderTable.h"
#include <QStringList>
#include <QHeaderView>
#include "GVAR.h"
#include "ItemDelegate.h"
#include <QDebug>
#include <QTableView>
#include <QScrollBar>

#if _MSC_VER >= 1700
#pragma execution_character_set("utf-8")
#endif


OrderTable::OrderTable(){
	this->setColumnCount(12);
	QStringList header;
	header << "编号" << "合约代码" << "买卖" << "开平" << "委托数" << "委托价" << "成交数" << "挂单状态" << "报单时间" << "报单日期" << "详细状态" << "自编号";
	this->setHorizontalHeaderLabels(header);
	this->verticalHeader()->setDefaultSectionSize(18);
	this->verticalHeader()->setVisible(false);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setFocusPolicy(Qt::NoFocus);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setShowGrid(false);
	this->setStyleSheet(" QTableView {background-color: white; border: 1px solid #7F9DB9; }");
	this->horizontalHeader()->setStyleSheet(" QHeaderView::up-arrow { subcontrol-position: center right;} QHeaderView::down-arrow { subcontrol-position: center right;} QHeaderView::section{  background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, stop : 0 #FFFFFF, stop: 1.0 #F0F0F0); border: 0px solid #E0DDDC; border-bottom: 1px solid #787878; border-right: 1px solid #787878; height:17px; font-size: 12px;}");
	this->horizontalHeader()->setHighlightSections(false);

	this->horizontalScrollBar()->setStyleSheet("QScrollBar{height: 16px; }");
	this->verticalScrollBar()->setStyleSheet("QScrollBar{width: 16px; }");


	connect(this->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));

	this->setItemDelegate(new ItemDelegate());
	this->setColumnWidth(0, 62);
	this->setColumnWidth(1, 62);
	this->setColumnWidth(2, 40);
	this->setColumnWidth(3, 40);
	this->setColumnWidth(4, 45);
	this->setColumnWidth(5, 55);
	this->setColumnWidth(6, 45);
	this->setColumnWidth(7, 120);
	this->setColumnWidth(8, 96);
	this->setColumnWidth(9, 96);
	this->setColumnWidth(10, 120);
	this->setColumnWidth(11, 50);
}

OrderTable::~OrderTable(){}

void OrderTable::update(){
	this->clearContents();
	int rowCount = this->rowCount();
	for (; rowCount >= 0; rowCount--) {
		this->removeRow(rowCount);
	}

	int row = 0;
	for (auto iter = allOrder.rbegin(); iter != allOrder.rend(); iter++) {
		if (iter->first.at(0)=='T')
			continue;

		Order *i = allOrder[iter->first];
		QTableWidgetItem *first = new QTableWidgetItem();
		QTableWidgetItem *second = new QTableWidgetItem();
		QTableWidgetItem *third = new QTableWidgetItem();
		QTableWidgetItem *forth = new QTableWidgetItem();
		QTableWidgetItem *fifth = new QTableWidgetItem();
		QTableWidgetItem *sixth = new QTableWidgetItem();
		QTableWidgetItem *seventh = new QTableWidgetItem();
		QTableWidgetItem *eighth = new QTableWidgetItem();
		QTableWidgetItem *ninth = new QTableWidgetItem();
		QTableWidgetItem *tenth = new QTableWidgetItem();
		QTableWidgetItem *eleventh = new QTableWidgetItem();
		QTableWidgetItem *twelfth = new QTableWidgetItem();
		
		first->setData(Qt::DisplayRole, i->OrderSysID.toInt());
		
		first->setTextAlignment(Qt::AlignCenter);
		//买卖方向
		second->setText(i->InstrumentID);
		second->setTextAlignment(Qt::AlignCenter);
		if (i->Direction == '0') {
			third->setText("买");
			third->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			third->setTextColor(QColor(255, 0, 0));//红色
		}
		else {
			third->setText("卖");
			third->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
			third->setTextColor(QColor(0, 128, 0));//绿色
		}
		//组合开平标志
		if (i->CombOffsetFlag[0] == '0')
			forth->setText("开仓");
		else if (i->CombOffsetFlag[0] == '1')
			forth->setText("平仓");
		else if (i->CombOffsetFlag[0] == '2')
			forth->setText("强平");
		else if (i->CombOffsetFlag[0] == '3')
			forth->setText("平今");
		else if (i->CombOffsetFlag[0] == '4')
			forth->setText("平昨");
		else if (i->CombOffsetFlag[0] == '5')
			forth->setText("强减");
		else if (i->CombOffsetFlag[0] == '6')
			forth->setText("本地强平");
		forth->setTextColor(QColor(0, 0, 255)); //蓝色
		forth->setTextAlignment(Qt::AlignCenter);
		fifth->setText(QString::number(i->VolumeTotalOriginal));
		fifth->setTextAlignment(Qt::AlignCenter);
		sixth->setText(QString::number(i->LimitPrice));
		sixth->setTextAlignment(Qt::AlignCenter);
		seventh->setText(QString::number(i->VolumeTraded));
		seventh->setTextAlignment(Qt::AlignCenter);
		//挂单状态
		QString status("");
		if (i->OrderStatus == '0')
			status = "全部成交";
		else if (i->OrderStatus == '1')
			status = "部分成交还在队列中";
		else if (i->OrderStatus == '2')
			status = "部分成交不在队列中";
		else if (i->OrderStatus == '3')
			status = "未成交还在队列中";
		else if (i->OrderStatus == '4')
			status = "未成交不在队列中";
		else if (i->OrderStatus == '5')
			status = "已撤单";
		else if (i->OrderStatus == 'a')
			status = "未知";
		else if (i->OrderStatus == 'b')
			status = "尚未触发";
		else if (i->OrderStatus == 'c')
			status = "已触发";
		eighth->setText(status);
		eighth->setTextAlignment(Qt::AlignCenter);
		ninth->setText(i->InsertTime);
		ninth->setTextAlignment(Qt::AlignCenter);
		tenth->setText(i->InsertDate);
		tenth->setTextAlignment(Qt::AlignCenter);
		QString DetailStatus = status;
		if (i->OrderSubmitStatus == '0')
			DetailStatus = eighth->text() + "报单已提交";
		eleventh->setText(DetailStatus);
		eleventh->setTextAlignment(Qt::AlignCenter);
		twelfth->setText(i->OrderRef);
		twelfth->setTextAlignment(Qt::AlignCenter);


		this->insertRow(row);
		this->setItem(row, 0, first);
		this->setItem(row, 1, second);
		this->setItem(row, 2, third);
		this->setItem(row, 3, forth);
		this->setItem(row, 4, fifth);
		this->setItem(row, 5, sixth);
		this->setItem(row, 6, seventh);
		this->setItem(row, 7, eighth);
		this->setItem(row, 8, ninth);
		this->setItem(row, 9, tenth);
		this->setItem(row, 10, eleventh);
		this->setItem(row, 10, twelfth);
		row++;
	}
}
