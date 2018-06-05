//初始化程序中的各种变量
#include "GVAR.h"
#include "initialize.h"
#include <qdebug.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qsettings.h>
#include <qmessagebox.h>
#include <map>
#include <QtXML\QDomDocument>
#include <QString>

using std::make_pair;


//读取文件初始化一键订阅的合约
void iniComboShow() {
	QFile iniFile("ini/parameter.ini");
	if (!iniFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::information(0, "错误", "找不到parameter.ini文件");
		abort();
	}
	QTextStream in(&iniFile);
	QString line;
	if (!in.atEnd()) {
		line = in.readLine();
		DefaultVolume = line.toInt();
	}
	while (!in.atEnd()) {
		line = in.readLine();
		QStringList list = line.split(" ");
		InstruParameter *ip = new InstruParameter();
		QString code = list.at(0).trimmed();
		ip->MultiDefault = list.at(1).trimmed().toDouble();
		ip->EmptyDefault = list.at(2).trimmed().toDouble();
		ip->StopDefault = list.at(3).trimmed().toDouble();
		allInstruPara.insert(std::make_pair(code, ip));
	}
	iniFile.close();
}

void iniLogin(){
	QDomDocument doc;
	QFile file("ini/config.xml");
	int errorLine, errorColumn;
	QString errorMsg;
	
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "错误", "找不到config.xml文件");
		abort();
	}

	if (!doc.setContent(&file, &errorMsg, &errorLine, &errorColumn)){
		QString error("Syntax error line %1, column %2:\n%3");
		error = error.arg(errorLine).arg(errorColumn).arg(errorMsg);
		qDebug() << error;
		return;
	}
	file.close();

	QDomElement docElem = doc.documentElement();  //返回根元素
	QDomNode n = docElem.firstChild();   //返回根节点的第一个子节点
	while (!n.isNull())
	{
		if (n.isElement())
		{
			QDomElement e = n.toElement();

			LoginParameter *lp = new LoginParameter();
			lp->BrokerName = e.attribute("BrokerName");
			lp->BrokerID = e.attribute("BrokerID");
			lp->UserID = e.attribute("UserID");

			// 获得元素e的所有子节点的列表
			QDomNodeList list = e.childNodes();
			// 遍历该列表
			for (int i = 0; i < list.count(); i++)
			{
				QDomNode node = list.at(i);
				if (node.isElement()) 
				{
					QDomElement ne = node.toElement();
					Address *address = new Address();
					address->TradingAddress = ne.attribute("TradingAddress");
					address->MDAddress = ne.attribute("MDAddress");
					lp->Server.insert(make_pair(ne.attribute("Name"), address));
					/*qDebug() << "   " << qUtf8Printable(ne.attribute("Name"))
						<< lp->Server[ne.attribute("Name")]->MDAddress
						<< lp->Server[ne.attribute("Name")]->TradingAddress;*/
				}
			}
			loginPar.push_back(lp);
		}
		n = n.nextSibling();  //下一个兄弟节点
	}

}
