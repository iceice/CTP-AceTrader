#pragma once

#include <Qobject>
#include <Qstring>
#include <QLineEdit>
#include <memory>
#include "Receiver.h"

class SubscribeController :public QObject {
	Q_OBJECT
public:
	SubscribeController();
	//设置接收器
	void setReceiver(std::shared_ptr<Receiver> r);
	//恢复初始状态
	void reset();
	//订阅指定合约
	void subscribe(QString code);
	public slots:
	void subscribePositionIns();
private:
	std::shared_ptr<Receiver> receiver;
};
