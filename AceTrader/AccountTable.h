#pragma once

#include <QObject>
#include <QTableWidget>


class AccountTable : public QTableWidget{
	Q_OBJECT
public:
	AccountTable();
	~AccountTable();
	void focusOutEvent(QFocusEvent *event);
	public slots:
	void update();
};
