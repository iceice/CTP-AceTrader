#pragma once

#include <QObject>
#include <QTableWidget>

class OrderTable : public QTableWidget{
	Q_OBJECT
public:
	OrderTable();
	~OrderTable();
	public slots:
	void update();
};
