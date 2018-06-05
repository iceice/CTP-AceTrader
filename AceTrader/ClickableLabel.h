#pragma once

#include <QLabel>

class ClickableLabel : public QLabel{
	Q_OBJECT
public:
	explicit ClickableLabel(QWidget *parent = 0);
	explicit ClickableLabel(const QString &text = "", QWidget *parent = 0);
	~ClickableLabel();
signals:
	void clicked(const QString&);
protected:
	void mousePressEvent(QMouseEvent *event);
};
