
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include "TitleBar.h"
#include <QIcon>
#include <Qstyle>
#include "GVAR.h"

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

#if _MSC_VER >= 1700
#pragma execution_character_set("utf-8")
#endif

TitleBar::TitleBar(QWidget *parent): QFrame(parent){
	setFixedHeight(30);
	m_pIconLabel = new QLabel(this);
	m_pTitleLabel = new QLabel(this);
	m_pMinimizeButton = new QToolButton(this);
	m_pMaximizeButton = new QToolButton(this);
	m_pCloseButton = new QToolButton(this);
	m_pMinimizeButton->setIcon(style()->standardPixmap(QStyle::SP_TitleBarMinButton));
	m_pMaximizeButton->setIcon(style()->standardPixmap(QStyle::SP_TitleBarMaxButton));
	m_pCloseButton->setIcon(style()->standardPixmap(QStyle::SP_TitleBarCloseButton));

	m_pIconLabel->setFixedSize(16, 16);
	m_pIconLabel->setScaledContents(true);

	m_pTitleLabel->setFixedWidth(62);

	m_pTitleLabel->setObjectName("whiteLabel");
	m_pMinimizeButton->setObjectName("minimizeButton");
	m_pMaximizeButton->setObjectName("maximizeButton");
	m_pCloseButton->setObjectName("closeButton");

	textLabel = new QLabel(this);
	textLabel->setText("占用保证金：0.00   动态权益：0.00   可用资金：0.00");
	textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	textLabel->setObjectName("textLabel");

	QHBoxLayout *pLayout = new QHBoxLayout(this);
	pLayout->setSpacing(0);
	pLayout->addWidget(m_pIconLabel);
	pLayout->addSpacing(10);
	pLayout->addWidget(m_pTitleLabel);
	pLayout->addSpacing(10);
	pLayout->addWidget(textLabel);
	pLayout->addWidget(m_pMinimizeButton);
	pLayout->addWidget(m_pMaximizeButton);
	pLayout->addWidget(m_pCloseButton);
	pLayout->setContentsMargins(5, 0, 5, 0);
	setLayout(pLayout);
	updateTextTimer = new QTimer(this);
	updateTextTimer->start(1000);
	connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(updateTextTimer, SIGNAL(timeout()), this, SLOT(updateText()));
}

TitleBar::~TitleBar(){}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event){
	Q_UNUSED(event);
	emit m_pMaximizeButton->clicked();
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
	if (ReleaseCapture())
	{
		QWidget *pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
	event->ignore();
#else
#endif
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type())
	{
	case QEvent::WindowTitleChange:
	{
		QWidget *pWidget = qobject_cast<QWidget *>(obj);
		if (pWidget)
		{
			m_pTitleLabel->setText(pWidget->windowTitle());
			return true;
		}
	}
	case QEvent::WindowIconChange:
	{
		QWidget *pWidget = qobject_cast<QWidget *>(obj);
		if (pWidget)
		{
			QIcon icon = pWidget->windowIcon();
			m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
			return true;
		}
	}
	case QEvent::WindowStateChange:
	case QEvent::Resize:
		updateMaximize();
		return true;
	}
	return QWidget::eventFilter(obj, event);
}

void TitleBar::onClicked()
{
	QToolButton *pButton = qobject_cast<QToolButton *>(sender());
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		if (pButton == m_pMinimizeButton)
		{
			pWindow->showMinimized();
		}
		else if (pButton == m_pMaximizeButton)
		{
			pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
		}
		else if (pButton == m_pCloseButton)
		{
			pWindow->close();
		}
	}
}

void TitleBar::updateMaximize()
{
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		bool bMaximize = pWindow->isMaximized();
		if (bMaximize)
		{
			m_pMaximizeButton->setToolTip(tr("Restore"));
			m_pMaximizeButton->setProperty("maximizeProperty", "restore");
		}
		else
		{
			m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
			m_pMaximizeButton->setToolTip(tr("Maximize"));
		}

		m_pMaximizeButton->setStyle(QApplication::style());
	}
}

void TitleBar::updateText() {
	textLabel->setText("占用保证金：" + QString::number(ACCOUNT->CurrMargin, 'f', 2) + "   动态权益：" + QString::number(ACCOUNT->DynamicInterest, 'f', 2) + "   可用资金：" + QString::number(ACCOUNT->Available, 'f', 2));
}