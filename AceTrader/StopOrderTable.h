#pragma once
#include <QObject>
#include <QTableWidget>

class StopOrderTable : public QTableWidget
{
	Q_OBJECT
public:
	StopOrderTable();
	~StopOrderTable();
	void focusOutEvent(QFocusEvent *event);
	public slots:
	void update();
};
