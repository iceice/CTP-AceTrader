#pragma once

#include <QDoubleSpinBox>
#include <QString>
#include <QObject>

class MyQDoubleSpinBox : public QDoubleSpinBox{
	Q_OBJECT
public:
	MyQDoubleSpinBox();
	~MyQDoubleSpinBox();
	QString textFromValue(double val) const;
	void mysetValue(double val);
};
