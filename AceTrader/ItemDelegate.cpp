#include "ItemDelegate.h"

ItemDelegate::ItemDelegate()
{
}

ItemDelegate::~ItemDelegate()
{
}

void ItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const{
	QStyleOptionViewItem  viewOption(option);
	//������ʾ����ͨ��ʾʱ��ǰ��ɫһ�£���ѡ���к�δѡ��ʱ���������ɫһ����   
	viewOption.palette.setColor(QPalette::HighlightedText, index.data(Qt::ForegroundRole).value<QColor>());
	viewOption.palette.setColor(QPalette::Highlight, QColor(182, 202, 234));
	//viewOption.palette.setColor(QPalette::Highlight, QColor(250, 247, 192));
	
	QItemDelegate::paint(painter, viewOption, index);
}