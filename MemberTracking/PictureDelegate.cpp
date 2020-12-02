#include "PictureDelegate.h"
#include <qpainter>
#include <qpixmap>
#include <qdebug.h>
#include <fstream>


PictureDelegate::PictureDelegate(QWidget* parent)
{
}

bool PictureDelegate::photoInDatabase(std::string photo)
{
	std::ifstream file("photos.txt");
	std::string line;
	while (getline(file, line))
	{
		if (photo == line)
			return true;
	}
	return false;
}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() != 3)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}
	QString photograph = index.model()->data(index, Qt::EditRole).toString();
	if (photoInDatabase(photograph.toStdString()))
	{
		QPixmap pixMap(photograph);
		painter->drawPixmap(option.rect, pixMap);
	}
	else
	{
		QPixmap pixMap("nophoto.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() == 3)
		return QSize(200, 100);
	return QSize();
}
