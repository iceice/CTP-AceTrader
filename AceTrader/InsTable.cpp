#include "InsTable.h"
#include "GVAR.h"
#include <qdebug.h>
#include <qmessagebox.h>
#include <QString>
#include <QColor>
#include <QAbstractButton>
#include <QApplication>
#include <QStylePainter>
#include <QScrollBar>

using std::set;
using std::make_pair;

#if _MSC_VER >= 1700
#pragma execution_character_set("utf-8")
#endif

InsTable::InsTable() {
	this->setColumnCount(2);
	//设置表头内容 
	QStringList header;
	header << "合约代码" << "合约名称";
	this->setHorizontalHeaderLabels(header);
	
	//选中模式
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	//this->setFocusPolicy(Qt::NoFocus);
	//设置不可编辑
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);

	this->setStyleSheet("QTableView {selection-background-color: #B6CAEA; background-color: white; border: 1px solid #7F9DB9; gridline-color: lightgray;}");
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{ font-weight: bold; background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, stop : 0 #FFFFFF, stop: 1.0 #F0F0F0); border: 0px solid #E0DDDC; border-bottom: 1px solid #E0DDDC; border-right: 1px solid #E0DDDC; height: 21px; font-size: 12px;}");
	//this->verticalHeader()->setStyleSheet("QHeaderView{background-color: #FFFFFF;} QHeaderView::section{ font-weight: bold; background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, stop : 0 #FFFFFF, stop: 1.0 #F0F0F0); border: 0px solid #E0DDDC; border-bottom: 1px solid #787878; border-right: 1px solid #787878; width: 30px; font-size: 12px;}");
	this->verticalHeader()->setStyleSheet("QHeaderView::section{ font-weight: bold; background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, stop : 0 #FFFFFF, stop: 1.0 #F0F0F0); border: 0px solid #E0DDDC; border-bottom: 1px solid #787878; border-right: 1px solid #787878; width: 30px; font-size: 12px;}");
	this->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
	this->horizontalHeader()->setHighlightSections(false);
	this->verticalHeader()->setHighlightSections(false);

	this->horizontalScrollBar()->setStyleSheet("QScrollBar{height: 16px; }");
	this->verticalScrollBar()->setStyleSheet("QScrollBar{width: 16px; }");

	this->setColumnWidth(0, 65);
	this->setColumnWidth(1, 85);

	QAbstractButton* btn = findChild<QAbstractButton*>();
	if (btn) {
		btn->setText("序号");
		btn->installEventFilter(this);
		btn->setEnabled(false);
	}

	updateSHFE();
}


void InsTable::updateSHFE(){
	int row = 0;
	for (auto iter = SHFE_Instru.begin(); iter != SHFE_Instru.end(); iter++) {
		QTableWidgetItem *first = new QTableWidgetItem();
		first->setText(iter->first);
		first->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem *second = new QTableWidgetItem();
		second->setText(iter->second);
		second->setTextAlignment(Qt::AlignCenter);
		
		this->insertRow(row);
		this->setItem(row, 0, first);
		this->setItem(row, 1, second);
		this->setRowHeight(row, 21);
		row++;
	}
}

void InsTable::updateCZCE(){
	int row = 0;
	for (auto iter = CZCE_Instru.begin(); iter != CZCE_Instru.end(); iter++) {
		QTableWidgetItem *first = new QTableWidgetItem();
		first->setText(iter->first);
		first->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem *second = new QTableWidgetItem();
		second->setText(iter->second);
		second->setTextAlignment(Qt::AlignCenter);

		this->insertRow(row);
		this->setItem(row, 0, first);
		this->setItem(row, 1, second);
		this->setRowHeight(row, 21);
		row++;
	}
}

void InsTable::updateDCE(){
	int row = 0;
	for (auto iter = DCE_Instru.begin(); iter != DCE_Instru.end(); iter++) {
		QTableWidgetItem *first = new QTableWidgetItem();
		first->setText(iter->first);
		first->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem *second = new QTableWidgetItem();
		second->setText(iter->second);
		second->setTextAlignment(Qt::AlignCenter);

		this->insertRow(row);
		this->setItem(row, 0, first);
		this->setItem(row, 1, second);
		this->setRowHeight(row, 21);
		row++;
	}
}

void InsTable::updateCFFEX(){
	int row = 0;
	for (auto iter = CFFEX_Instru.begin(); iter != CFFEX_Instru.end(); iter++) {
		QTableWidgetItem *first = new QTableWidgetItem();
		first->setText(iter->first);
		first->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem *second = new QTableWidgetItem();
		second->setText(iter->second);
		second->setTextAlignment(Qt::AlignCenter);

		this->insertRow(row);
		this->setItem(row, 0, first);
		this->setItem(row, 1, second);
		this->setRowHeight(row, 21);
		row++;
	}
}

bool InsTable::eventFilter(QObject * o, QEvent * e){
	if (e->type() == QEvent::Paint)
	{
		QAbstractButton* btn = qobject_cast<QAbstractButton*>(o);
		if (btn) {
			QStyleOptionHeader opt;
			opt.init(btn);
			opt.textAlignment = Qt::AlignCenter;
			opt.rect = btn->rect();
			opt.text = btn->text(); // this line is the only difference to QTableCornerButton  
			opt.position = QStyleOptionHeader::OnlyOneSection;
			QStylePainter painter(btn);
			painter.drawControl(QStyle::CE_Header, opt);
			return true; // eat event  
		}
	}
	return false;
}

void InsTable::focusOutEvent(QFocusEvent * event)
{
	this->clearSelection();
}

/************************槽函数************************/
void InsTable::updateForAdd() {
	int row = this->currentIndex().row();
	if (row < 0)
		return;
	QTableWidgetItem *selected = this->item(row, 0);
	QString code(selected->text());
	qDebug() << ">>>>添加:" << code;
	if (allInstruPara.find(code) == allInstruPara.end()) {
		allInstruPara.insert(std::make_pair(code, new InstruParameter()));
		emit updateSub();
	}
}