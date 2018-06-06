#pragma once

#include <QTableWidget>
#include <QObject>
#include <QTimer>
#include "Positions.h"

class PositionTable : public QTableWidget{
	Q_OBJECT
public:
	PositionTable();
	~PositionTable();
	void focusOutEvent(QFocusEvent *event);
	public slots:
	void update();
	void updatePrice();
	void tableItemClicked(int r,int c);
private:
	QTimer * updateTimer;			//�Զ�ˢ�¼�ʱ��

signals:
	void positonClose(Positions*);
};
