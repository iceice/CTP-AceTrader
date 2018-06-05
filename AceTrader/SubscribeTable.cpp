#include <SubscribeTable.h>
#include "GVAR.h"
#include <QHeaderView>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QLinearGradient>
#include <QAbstractButton>
#include <QApplication>
#include <QStylePainter>
#include <QScrollBar>

SubscribeTable::SubscribeTable() {
	this->setColumnCount(4);
	//设置表头内容 
	QStringList header;
	header << "合约代码" << "平多默认" << "平空默认" << "止损默认";
	this->setHorizontalHeaderLabels(header);
	//设置不可编辑
	this->setStyleSheet("QTableView {selection-background-color: #B6CAEA; background-color: white; border: 1px solid #7F9DB9; gridline-color: lightgray;}");
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{ font-weight: bold; background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, stop : 0 #FFFFFF, stop: 1.0 #F0F0F0); border: 0px solid #E0DDDC; border-bottom: 1px solid #787878; border-right: 1px solid #787878; height: 21px; font-size: 12px;}");
	this->verticalHeader()->setStyleSheet("QHeaderView{background-color: #FFFFFF;} QHeaderView::section{ font-weight: bold; background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, stop : 0 #FFFFFF, stop: 1.0 #F0F0F0); border: 0px solid #E0DDDC; border-bottom: 1px solid #787878; border-right: 1px solid #787878; width: 30px; font-size: 12px;}");
	this->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
	this->horizontalHeader()->setHighlightSections(false);
	this->verticalHeader()->setHighlightSections(false);

	this->horizontalScrollBar()->setStyleSheet("QScrollBar{height: 16px; }");
	this->verticalScrollBar()->setStyleSheet("QScrollBar{width: 16px; }");

	this->setColumnWidth(0, 86);
	this->setColumnWidth(1, 92);
	this->setColumnWidth(2, 92);
	this->setColumnWidth(3, 92);

	QAbstractButton* btn = findChild<QAbstractButton*>();
	if (btn) {
		btn->setText("序号");
		btn->installEventFilter(this);
		btn->setEnabled(false);
	}

	connect(this, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(change(QTableWidgetItem *)));

	updateTable();
}

void SubscribeTable::updateTable() {
	int row = 0;
	for (auto iter = allInstruPara.begin(); iter != allInstruPara.end(); iter++) {
		InstruParameter *i = allInstruPara[iter->first];

		QTableWidgetItem *first = new QTableWidgetItem();
		QTableWidgetItem *second = new QTableWidgetItem();
		QTableWidgetItem *third = new QTableWidgetItem();
		QTableWidgetItem *forth = new QTableWidgetItem();

		first->setTextAlignment(Qt::AlignCenter);
		second->setTextAlignment(Qt::AlignCenter);
		third->setTextAlignment(Qt::AlignCenter);
		forth->setTextAlignment(Qt::AlignCenter);


		first->setText(iter->first);
		first->setFlags(first->flags() & ~Qt::ItemIsEditable);
		first->setFlags(first->flags() & ~Qt::ItemIsSelectable);
		second->setText(QString::number(i->MultiDefault));
		third->setText(QString::number(i->EmptyDefault));
		forth->setText(QString::number(i->StopDefault));

		this->insertRow(row);
		this->setItem(row, 0, first);
		this->setItem(row, 1, second);
		this->setItem(row, 2, third);
		this->setItem(row, 3, forth);
		this->setRowHeight(row, 21);
		row++;
	}
}

void SubscribeTable::updateForDel() {
	int row = this->currentIndex().row();
	if (row < 0)
		return;
	QTableWidgetItem *selected = this->item(row, 0);
	QString code = selected->text();
	for (auto iter = allInstruPara.begin(); iter != allInstruPara.end(); iter++) {
		if (iter->first == code) {
			allInstruPara.erase(iter);
			break;
		}
	}

	//更新显示的表格
	this->clearContents();
	int rowCount = this->rowCount();
	for (; rowCount >= 0; rowCount--) {
		this->removeRow(rowCount);
	}

	updateTable();
}

bool SubscribeTable::eventFilter(QObject * o, QEvent * e) {
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


/***********************槽函数*********************/
void SubscribeTable::updateForAdd() {
	//更新显示的表格
	this->clearContents();
	int rowCount = this->rowCount();
	for (; rowCount >= 0; rowCount--) {
		this->removeRow(rowCount);
	}
	updateTable();
}

void SubscribeTable::updateForCancel() {
	//更新显示的表格
	allInstruPara = temp;
	temp.clear();
	this->clearContents();
	int rowCount = this->rowCount();
	for (; rowCount >= 0; rowCount--) {
		this->removeRow(rowCount);
	}
	updateTable();
}

void SubscribeTable::change(QTableWidgetItem * item) {
	int row = item->row();
	int col = item->column();
	QString code = this->item(row, 0)->text();
	double num = item->text().toDouble();
	if (col == 0)
		return;
	for (auto iter = allInstruPara.begin(); iter != allInstruPara.end(); iter++) {
		if (iter->first == code) {
			InstruParameter *p = iter->second;
			if (col == 1)
				p->MultiDefault = num;
			else if (col == 2)
				p->EmptyDefault = num;
			else
				p->StopDefault = num;
			break;
		}
	}
}
