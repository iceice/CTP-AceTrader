#include "Receiver.h"
#include <qdebug.h>
using std::shared_ptr;
using std::make_shared;
using std::set;


Receiver::Receiver() {
	api = make_shared<CTPMdApi>();
	spi = make_shared<CTPMdSpi>(api);
	api->registerSpi(spi);
	//api���ú�����,spi��������źţ�Receiver�����źŸ�������
	connect(spi.get(), SIGNAL(loginSuccess()), this, SIGNAL(loginSuccess()));

	//�������ӳ�ʱ��ʱ��
	connectOverTimer = new QTimer(this);
	connect(connectOverTimer, SIGNAL(timeout()), this, SLOT(detectOvertime()));
	connectOverTimer->setSingleShot(true);
}

Receiver::~Receiver() {
	//����api��Spi������
	api->registerSpi(NULL);
	spi->release();
	qDebug() << "~Receiver";
}

//��api��������
void Receiver::connectServer() {
	api->connectServer();
	connectOverTimer->start(3 * 1000);
}

//��������
int Receiver::subscribeData(char *ppInstrumentID[], int nCount) {
	return api->subscribeData(ppInstrumentID, nCount);
}

//�˶�����
int Receiver::unsubscribeData(char *ppInstrumentID[], int nCount) {
	return api->unsubscribeData(ppInstrumentID, nCount);
}


//������ӳ�ʱ��ʱ������Ƿ����ӳ�ʱ
void Receiver::detectOvertime() {
	bool isCon = api->isConnect();
	if (isCon == false) {
		emit connectFailed();
	}
}
