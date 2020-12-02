#pragma once
#include <qabstractitemmodel.h>
#include "Repository.h"

class MembersTableModel : public QAbstractTableModel
{
private:
	shared_ptr<Repository>& repository;

public:
	MembersTableModel(shared_ptr<Repository>& _repository) : repository(_repository) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex& index) const;

};

