#include "ItemDelegate.h"

ItemDelegate::ItemDelegate()
{
}

ItemDelegate::~ItemDelegate()
{
}

void ItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const{
	QStyleOptionViewItem  viewOption(option);
	//高亮显示与普通显示时的前景色一致（即选中行和未选中时候的文字颜色一样）   
	viewOption.palette.setColor(QPalette::HighlightedText, index.data(Qt::ForegroundRole).value<QColor>());
	viewOption.palette.setColor(QPalette::Highlight, QColor(182, 202, 234));
	//viewOption.palette.setColor(QPalette::Highlight, QColor(250, 247, 192));
	
	QItemDelegate::paint(painter, viewOption, index);
}