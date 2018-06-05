#pragma once

#include <QObject>
#include <QTableWidget>

class TradeTable : public QTableWidget{
	Q_OBJECT
public:
	TradeTable();
	~TradeTable();
	public slots:
	void update();
};
