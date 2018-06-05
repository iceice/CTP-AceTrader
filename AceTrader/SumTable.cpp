#include "SumTable.h"
#include <QTableView>
#include <QHeaderView>
#include <QLayout>
#include <QScrollBar>
#include <QDebug>
#include "ItemDelegate.h"
#include "GVAR.h"
#include "Trade.h"

#if _MSC_VER >= 1700
#pragma execution_character_set("utf-8")
#endif

using std::make_pair;

SumTable::SumTable(){


	report = new QTableWidget(this);
	report->setObjectName("ReportBody");
	report->setSelectionMode(QAbstractItemView::ExtendedSelection);
	report->setSelectionBehavior(QAbstractItemView::SelectRows);
	report->setFocusPolicy(Qt::NoFocus);
	report->setShowGrid(false);
	report->setEditTriggers(QAbstractItemView::NoEditTriggers);
	report->verticalHeader()->setVisible(false);
	report->verticalHeader()->setDefaultSectionSize(18);
	report->horizontalHeader()->setHighlightSections(false);
	report->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	report->setItemDelegate(new ItemDelegate());
	report->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);    //列表不能移动

	report->setStyleSheet("QTableView {background-color: white; border: 0px solid #7F9DB9; border-left: 1px solid #7F9DB9; border-right: 1px solid #7F9DB9; border-top: 1px solid #7F9DB9;  }");
	report->horizontalHeader()->setStyleSheet("QHeaderView::section{ background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, stop : 0 #FFFFFF, stop: 1.0 #F0F0F0); border: 0px solid #E0DDDC; border-bottom: 1px solid #787878; border-right: 1px solid #787878; height:17px; font-size: 12px;}");
	
	connect(report->horizontalHeader(), SIGNAL(sectionClicked(int)), report, SLOT(sortByColumn(int)));
	//connect(report->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(OncurrentRowChanged(QModelIndex, QModelIndex)));	
	connect(report->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(OncurrentRowChanged(QItemSelection, QItemSelection)));

	report->setColumnCount(8);
	QStringList header;
	header << "报单编号" << "合约代码" << "买卖" << "开平" << "价格" << "数量" << "成交时间" << "成交日期";
	report->setHorizontalHeaderLabels(header);
	report->setColumnWidth(0, 90);
	report->setColumnWidth(1, 90);
	report->setColumnWidth(2, 45);
	report->setColumnWidth(3, 65);
	report->setColumnWidth(4, 80);
	report->setColumnWidth(5, 80);
	report->setColumnWidth(6, 110);
	report->setColumnWidth(7, 110);
	
	

	summary = new QTableWidget(this);
	summary->setObjectName("ReportSummary");
	summary->setEditTriggers(QAbstractItemView::NoEditTriggers);
	summary->setFixedHeight(19);
	summary->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	summary->verticalHeader()->setVisible(false);

	summary->horizontalHeader()->setHighlightSections(false);
	summary->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	summary->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	summary->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);    //列表不能移动

	summary->setStyleSheet("QTableView {background-color: white; border: 0px solid #7F9DB9; border-left: 1px solid #7F9DB9; border-right: 1px solid #7F9DB9; border-top: 1px solid #C0C0C0; border-bottom: 1px solid #7F9DB9; }");
	summary->horizontalHeader()->setStyleSheet("QHeaderView::section{ font-weight: bold; color: #000080; background-color: #C0DCC0; border: 0px solid #E0DDDC; border-top: 1px solid #FFFFFF; border-left: 2px solid #FFFFFF; border-right: 1px solid #7F7F70; height:16px; font-size: 12px;}");

	summary->setColumnCount(8);
	QStringList sum_header;
	sum_header << "合计" << "" << "" << "" << "" << "" << "" << "";
	summary->setHorizontalHeaderLabels(sum_header);
	summary->setColumnWidth(0, 90);
	summary->setColumnWidth(1, 90);
	summary->setColumnWidth(2, 45);
	summary->setColumnWidth(3, 65);
	summary->setColumnWidth(4, 80);
	summary->setColumnWidth(5, 80);
	summary->setColumnWidth(6, 110);
	summary->setColumnWidth(7, 110);
	

	QVBoxLayout *lay = new QVBoxLayout();
	lay->addWidget(report, 1);
	lay->addWidget(summary);
	lay->setSpacing(0);
	lay->setMargin(0);
	delete layout();
	setLayout(lay);

}

void SumTable::update() {
	//清除
	report->clearContents();
	int rowCount = report->rowCount();
	for (; rowCount >= 0; rowCount--) {
		report->removeRow(rowCount);
	}

	int row = 0;
	int sum = 0;
	for (auto iter = allTrade.rbegin(); iter != allTrade.rend(); iter++) {
		Trade *i = allTrade[iter->first];
		QTableWidgetItem *first = new QTableWidgetItem();
		QTableWidgetItem *second = new QTableWidgetItem();
		QTableWidgetItem *third = new QTableWidgetItem();
		QTableWidgetItem *forth = new QTableWidgetItem();
		QTableWidgetItem *fifth = new QTableWidgetItem();
		QTableWidgetItem *sixth = new QTableWidgetItem();
		QTableWidgetItem *seventh = new QTableWidgetItem();
		QTableWidgetItem *eighth = new QTableWidgetItem();
		first->setText(i->OrderSysID);
		first->setTextAlignment(Qt::AlignCenter);
		second->setText(i->InstrumentID);
		second->setTextAlignment(Qt::AlignCenter);
		//买卖方向
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
		if (i->OffsetFlag == '0')
			forth->setText("开仓");
		else if (i->OffsetFlag == '1')
			forth->setText("平仓");
		else if (i->OffsetFlag == '2')
			forth->setText("强平");
		else if (i->OffsetFlag == '3')
			forth->setText("平今");
		else if (i->OffsetFlag == '4')
			forth->setText("平昨");
		else if (i->OffsetFlag == '5')
			forth->setText("强减");
		else if (i->OffsetFlag == '6')
			forth->setText("本地强平");
		forth->setTextColor(QColor(0, 0, 255)); //蓝色
		forth->setTextAlignment(Qt::AlignCenter);
		fifth->setText(QString::number(i->Price));
		fifth->setTextAlignment(Qt::AlignCenter);
		sixth->setText(QString::number(i->Volume));
		sum += i->Volume;
		sixth->setTextAlignment(Qt::AlignCenter);
		seventh->setText(i->TradeTime);
		seventh->setTextAlignment(Qt::AlignCenter);
		eighth->setText(i->TradeDate);
		eighth->setTextAlignment(Qt::AlignCenter);
		report->insertRow(row);
		report->setItem(row, 0, first);
		report->setItem(row, 1, second);
		report->setItem(row, 2, third);
		report->setItem(row, 3, forth);
		report->setItem(row, 4, fifth);
		report->setItem(row, 5, sixth);
		report->setItem(row, 6, seventh);
		report->setItem(row, 7, eighth);
		row++;
	}

	QStringList sum_header;
	sum_header << "合计" << "" << "" << "" << "" << QString::number(sum) << "" << "";
	summary->setHorizontalHeaderLabels(sum_header);

}

void SumTable::OncurrentRowChanged(QItemSelection, QItemSelection){

	int sum = 0;
	
	std::vector<int> vecItemIndex;//保存选中行的索引 
	QItemSelectionModel *selections = report->selectionModel(); //返回当前的选择模式    
	QModelIndexList selectedsList = selections->selectedIndexes(); //返回所有选定的模型项目索引列表

	for (int i = 0; i < selectedsList.count(); i++) {
		vecItemIndex.push_back(selectedsList.at(i).row());
	}

	std::sort(vecItemIndex.begin(), vecItemIndex.end());
	vecItemIndex.erase(std::unique(vecItemIndex.begin(), vecItemIndex.end()), vecItemIndex.end());

	if (vecItemIndex.size() == 1) 
	{
		for (int i = 0; i < report->rowCount(); i++) 
		{
			sum += (report->item(i, 5)->text()).toInt();
		}
	}
	else
	{
		for (int i = 0; i < vecItemIndex.size(); i++) {
			sum += (report->item(vecItemIndex[i], 5)->text()).toInt();
		}
	}

	QStringList sum_header;
	sum_header << "合计" << "" << "" << "" << "" << QString::number(sum) << "" << "";
	summary->setHorizontalHeaderLabels(sum_header);
}
