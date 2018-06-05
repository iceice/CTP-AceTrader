#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QTimer>

class TitleBar : public QFrame
{
	Q_OBJECT

public:
	explicit TitleBar(QWidget *parent = 0);
	~TitleBar();

protected:

	// 双击标题栏进行界面的最大化/还原
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

	// 进行鼠界面的拖动
	virtual void mousePressEvent(QMouseEvent *event);

	// 设置界面标题与图标
	virtual bool eventFilter(QObject *obj, QEvent *event);

	private slots:

	// 进行最小化、最大化/还原、关闭操作
	void onClicked();

private:

	// 最大化/还原
	void updateMaximize();

private:
	QLabel * m_pIconLabel;
	QLabel *m_pTitleLabel;
	QToolButton  *m_pMinimizeButton;
	QToolButton  *m_pMaximizeButton;
	QToolButton  *m_pCloseButton;
	QLabel *textLabel;
	QTimer *updateTextTimer;

	private slots:
	void updateText();
};
