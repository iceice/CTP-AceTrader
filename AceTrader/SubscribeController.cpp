#include "SubscribeController.h"
#include <QStringList>
#include <QDebug>
#include <vector>
#include <GVAR.h>
#include <QMessageBox>

using std::vector;
using std::shared_ptr;

SubscribeController::SubscribeController() = default;

void SubscribeController::setReceiver(shared_ptr<Receiver> r) {
	receiver = r;
}

void SubscribeController::reset() {
	receiver = nullptr;
}

void SubscribeController::subscribe(QString code) {
	char **ppInstrumentID = new char *[1];
	ppInstrumentID[0] = new char[7];
	strcpy(ppInstrumentID[0], code.toStdString().c_str());
	receiver->subscribeData(ppInstrumentID, 1);
}

void SubscribeController::subscribePositionIns() {
	int count = positionInstru.size();
	char **ppInstrumentID = new char *[count];
	int i = 0;
	for (auto iter = positionInstru.begin(); iter != positionInstru.end(); iter++) {
		ppInstrumentID[i] = new char[7];
		strcpy(ppInstrumentID[i], (*iter).toStdString().c_str());
		i++;
	}
	receiver->subscribeData(ppInstrumentID, count);
}