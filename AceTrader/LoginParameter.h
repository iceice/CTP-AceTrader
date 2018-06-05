#pragma once
#include <QString>
#include <map>

struct Address{
	QString TradingAddress;
	QString MDAddress;
};

class LoginParameter{
public:
	LoginParameter();

	QString BrokerName;
	QString BrokerID;
	QString UserID;
	std::map<QString, Address*> Server;
};

