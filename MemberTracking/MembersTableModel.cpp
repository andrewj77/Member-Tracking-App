#include "MembersTableModel.h"

int MembersTableModel::rowCount(const QModelIndex& parent) const
{
	return repository->getAllMembers().size();
}

int MembersTableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant MembersTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();
	Member member = repository->getAllMembers()[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		if (column == 0)
			return QString::fromStdString(member.getName());
		else if (column == 1)
			return QString::fromStdString(member.getProfession());
		else if (column == 2)
			return QString::fromStdString(to_string(member.getAge()));
		else if (column == 3)
			return QString::fromStdString(member.getPhotograph());
	}
	return QVariant();
}

QVariant MembersTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
		if (orientation == Qt::Horizontal)
		{
			if (section == 0)
				return QString("Name");
			else if (section == 1)
				return QString("Profession");
			else if (section == 2)
				return QString("Age");
			else if (section == 3)
				return QString("Photograph");
		}
	return QVariant();
}

bool MembersTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	return false; 
}

Qt::ItemFlags MembersTableModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

