#pragma once

#include <QItemDelegate>

class ItemDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	ItemDelegate();
	~ItemDelegate();
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
};
