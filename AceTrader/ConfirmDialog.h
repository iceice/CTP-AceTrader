#pragma once

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>

class ConfirmDialog : public QDialog{
	Q_OBJECT
public:
	ConfirmDialog();
	void showDialog();
private:
	QTextEdit * text;
	QPushButton *okButton;
	QPushButton *cancelButton;
signals:
	void confirm();
};
