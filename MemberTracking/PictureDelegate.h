#pragma once
#include <qstyleditemdelegate.h>


class PictureDelegate : public QStyledItemDelegate
{
public:
	PictureDelegate(QWidget* parent = 0);

	bool static photoInDatabase(std::string);
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

