#pragma once

#include <QObject>
#include <QTableWidget>


class AccountTable : public QTableWidget{
	Q_OBJECT
public:
	AccountTable();
	~AccountTable();
	public slots:
	void update();
};
