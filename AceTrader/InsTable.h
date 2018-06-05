#pragma once

#include <QObject>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QTimer>
#include <vector>
#include <map>
#include <set>
#include <qstring.h>
#include <ItemDelegate.h>
#define MAX 100000000
class InsTable :public QTableWidget {
	Q_OBJECT
public:
	InsTable();
	void updateSHFE();
	void updateCZCE();
	void updateDCE();
	void updateCFFEX();
	bool eventFilter(QObject* o, QEvent* e);
private:
	private slots :
	void updateForAdd();
signals:
	void updateSub();
};