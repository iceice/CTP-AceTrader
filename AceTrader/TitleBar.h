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

	// ˫�����������н�������/��ԭ
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

	// �����������϶�
	virtual void mousePressEvent(QMouseEvent *event);

	// ���ý��������ͼ��
	virtual bool eventFilter(QObject *obj, QEvent *event);

	private slots:

	// ������С�������/��ԭ���رղ���
	void onClicked();

private:

	// ���/��ԭ
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
