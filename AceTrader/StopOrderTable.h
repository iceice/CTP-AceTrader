#pragma once
#include <QObject>
#include <QTableWidget>

class StopOrderTable : public QTableWidget
{
	Q_OBJECT
public:
	StopOrderTable();
	~StopOrderTable();
	public slots:
	void update();
};
