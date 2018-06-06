#pragma once

#include <QWidget>
#include <QTableWidget>

class SumTable : public QWidget{
	Q_OBJECT
public:
	SumTable();
	void focusOutEvent(QFocusEvent * event);
	
	public slots:
	void update();
	void OncurrentRowChanged(QItemSelection, QItemSelection);

private:
	QTableWidget *report;
	QTableWidget *summary;

};
