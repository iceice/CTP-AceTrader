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
	//���ý�����
	void setReceiver(std::shared_ptr<Receiver> r);
	//�ָ���ʼ״̬
	void reset();
	//����ָ����Լ
	void subscribe(QString code);
	public slots:
	void subscribePositionIns();
private:
	std::shared_ptr<Receiver> receiver;
};
