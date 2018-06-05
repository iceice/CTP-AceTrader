#include "ClickableLabel.h"
#include <QStringList>
#include <QDebug>

ClickableLabel::ClickableLabel(QWidget *parent): QLabel(parent){}

ClickableLabel::ClickableLabel(const QString &text, QWidget *parent) : QLabel(parent){
	this->setText(text);
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent * event){
	QStringList list = this->text().split(" ");
	emit clicked(list.at(1));
}
