#pragma once

#include <QObject>
#include <QTableWidget>

class OrderTable : public QTableWidget{
	Q_OBJECT
public:
	OrderTable();
	~OrderTable();
	void focusOutEvent(QFocusEvent *event);
	public slots:
	void update();
	void updatePart();
	void tableItemClicked(int r, int c);
};
