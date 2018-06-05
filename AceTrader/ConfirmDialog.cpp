#include "ConfirmDialog.h"
#include <QBoxLayout>
#include <GVAR.h>

ConfirmDialog::ConfirmDialog(){
	resize(650, 400);

	text = new QTextEdit();
	text->setText(COMFIRM_MESSAGE);
	text->setWordWrapMode(QTextOption::NoWrap);
	okButton = new QPushButton("确定");
	okButton->setFixedSize(75, 23);
	cancelButton = new QPushButton("取消");
	cancelButton->setFixedSize(75, 23);
	connect(okButton, SIGNAL(clicked()), this, SIGNAL(confirm()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(hide()));
	
	
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(okButton);
	buttonLayout->addSpacing(20);
	buttonLayout->addWidget(cancelButton);
	buttonLayout->addStretch();
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(text);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(buttonLayout);

	setLayout(mainLayout);
	//设置
	setWindowTitle("交易信息确认");
	QIcon icon;
	icon.addFile(QStringLiteral("ico/coin.ico"), QSize(), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon);

	setModal(true);
	hide();
}

void ConfirmDialog::showDialog() {
	show();
}
