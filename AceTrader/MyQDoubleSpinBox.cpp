#include "MyQDoubleSpinBox.h"
#include <sstream>
#include <string>

MyQDoubleSpinBox::MyQDoubleSpinBox(){
	this->setMaximum(9999999);
	this->setDecimals(3);
}

MyQDoubleSpinBox::~MyQDoubleSpinBox(){}

QString MyQDoubleSpinBox::textFromValue(double val) const{
	std::ostringstream oss;
	oss << val;
	return QString::fromStdString(oss.str());
}

void MyQDoubleSpinBox::mysetValue(double val){
	this->setValue(val);
}
