#pragma once

#include <QObject>
#include <QTableWidget>
#include <QTableView>
#include <QEvent>

class SubscribeTable : public QTableWidget {
	Q_OBJECT
public:
	SubscribeTable();
	void updateTable();
	bool eventFilter(QObject* o, QEvent* e);
private:
	private slots :
	void updateForAdd();
	void updateForDel();
	void updateForCancel();
	void change(QTableWidgetItem * item);
};
