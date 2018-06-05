#include "PositionTable.h"
#include <QStringList>
#include <QHeaderView>
#include "GVAR.h"
#include "ItemDelegate.h"
#include <QDebug>
#include <QScrollBar>

#if _MSC_VER >= 1700
#pragma execution_character_set("utf-8")
#endif

PositionTable::PositionTable(){
	this->setColumnCount(11);
	QStringList header;
	header << "合约代码" << "买卖" << "总多仓" << "今多仓" << "总空仓" << "今空仓" << "开仓均价" << "持仓均价" << "最新价" << "开仓盈亏" << "持仓盈亏";
	this->setHorizontalHeaderLabels(header);
	this->verticalHeader()->setVisible(false);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setFocusPolicy(Qt::NoFocus);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setShowGrid(false);
	this->setStyleSheet("QTableView {background-color: white; border: 1px solid #7F9DB9; }");
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{ font-weight: bold; color: #000080; background-color: #FFFFE1 ; border: 0px solid #E0DDDC; border-bottom: 1px solid #7F7F70; border-right: 1px solid #7F7F70; height:17px; font-size: 12px;}");
	this->verticalHeader()->setDefaultSectionSize(18);
	this->horizontalHeader()->setHighlightSections(false);

	this->horizontalScrollBar()->setStyleSheet("QScrollBar{height: 16px; }");
	this->verticalScrollBar()->setStyleSheet("QScrollBar{width: 16px; }");

	this->setItemDelegate(new ItemDelegate());
	this->setColumnWidth(0, 80);
	this->setColumnWidth(1, 40);
	this->setColumnWidth(2, 56);
	this->setColumnWidth(3, 56);
	this->setColumnWidth(4, 56);
	this->setColumnWidth(5, 56);
	this->setColumnWidth(6, 60);
	this->setColumnWidth(7, 60);
	this->setColumnWidth(8, 60);
	this->setColumnWidth(9, 71);
	this->setColumnWidth(10, 71);

	updateTimer = new QTimer(this);
	connect(updateTimer, SIGNAL(timeout()), this, SLOT(updatePrice()));

	connect(this, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(tableItemClicked(int, int)));
}

PositionTable::~PositionTable(){}

void PositionTable::update() {
	this->clearContents();
	int rowCount = this->rowCount();
	if (rowCount > 0)
		updateTimer->stop();
	for (; rowCount >= 0; rowCount--) {
		this->removeRow(rowCount);
	}

	int row = 0;
	for (auto iter = allPositions.rbegin(); iter != allPositions.rend(); iter++) {
		Positions *i = *iter;
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
		first->setTextAlignment(Qt::AlignCenter);
		third->setTextAlignment(Qt::AlignCenter);
		forth->setTextAlignment(Qt::AlignCenter);
		fifth->setTextAlignment(Qt::AlignCenter);
		sixth->setTextAlignment(Qt::AlignCenter);
		seventh->setTextAlignment(Qt::AlignCenter);
		eighth->setTextAlignment(Qt::AlignCenter);
		ninth->setTextAlignment(Qt::AlignCenter);
		tenth->setTextAlignment(Qt::AlignCenter);
		eleventh->setTextAlignment(Qt::AlignCenter);

		first->setText(i->InstrumentID);
		if (i->PosiDirection == '2') {//多头
			second->setText("买");
			second->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			second->setTextColor(QColor(255, 0, 0));
			third->setText(QString::number(i->Position));
			forth->setText(QString::number(i->TodayPosition));
		}
		else if (i->PosiDirection == '3') {
			second->setText("卖");
			second->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
			second->setTextColor(QColor(0, 128, 0));
			fifth->setText(QString::number(i->Position));
			sixth->setText(QString::number(i->TodayPosition));
		}
		seventh->setText(QString::number(i->OpenAverage, 'f', 2));
		eighth->setText(QString::number(i->PreSettlementPrice));
		
		double lastPrice = instruList[i->InstrumentID]->lastPrice;
		double openProfit;
		ninth->setText(QString::number(lastPrice));
		if (i->PosiDirection == '2') { //买
			openProfit = (lastPrice - i->OpenAverage)*i->Position*i->VolumeMultiple;
		}
		else if (i->PosiDirection == '3') {
			openProfit = (i->OpenAverage - lastPrice)*i->Position*i->VolumeMultiple;
		}
		tenth->setText(QString::number(openProfit, 'f', 2));
		if (openProfit >= 0)
			tenth->setTextColor(QColor(255, 0, 0));
		else
			tenth->setTextColor(QColor(0, 128, 0));

		eleventh->setText(QString::number(i->PositionProfit));
		if (i->PositionProfit >= 0) {
			eleventh->setTextColor(QColor(255, 0, 0));
		}
		else {
			eleventh->setTextColor(QColor(0, 128, 0));
		}
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
		row++;
	}
	updateTimer->start(500);
}

void PositionTable::updatePrice() {
	int row = 0;
	for (auto iter = allPositions.rbegin(); iter != allPositions.rend(); iter++) {
		Positions *i = *iter;
		QTableWidgetItem *ninth = new QTableWidgetItem();
		QTableWidgetItem *tenth = new QTableWidgetItem();
		ninth->setTextAlignment(Qt::AlignCenter);
		tenth->setTextAlignment(Qt::AlignCenter);
		double lastPrice = instruList[i->InstrumentID]->lastPrice;
		double openProfit;
		ninth->setText(QString::number(lastPrice));
		if (i->PosiDirection == '2') { //买
			openProfit = (lastPrice - i->OpenAverage)*i->Position*i->VolumeMultiple;
		}
		else if (i->PosiDirection == '3') {
			openProfit = (i->OpenAverage - lastPrice)*i->Position*i->VolumeMultiple;
		}
		tenth->setText(QString::number(openProfit, 'f', 2));
		if (openProfit >= 0)
			tenth->setTextColor(QColor(255, 0, 0));
		else
			tenth->setTextColor(QColor(0, 128, 0));
		this->setItem(row, 8, ninth);
		this->setItem(row, 9, tenth);
		row++;
	}
}

void PositionTable::tableItemClicked(int r, int c){

	Positions *p = new Positions();
	p->InstrumentID = this->item(r, 0)->text();
	QString direction = this->item(r, 1)->text();
	
	if (direction == "买") {
		p->PosiDirection = '2';
		p->Position = (this->item(r, 2)->text()).toInt();
		p->TodayPosition = (this->item(r, 3)->text()).toInt();
	}
	else {
		p->PosiDirection = '3';
		p->Position = (this->item(r, 4)->text()).toInt();
		p->TodayPosition = (this->item(r, 5)->text()).toInt();
	}

	emit positonClose(p);
}
