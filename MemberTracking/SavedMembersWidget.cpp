#include "SavedMembersWidget.h"
#include "PictureDelegate.h"
#include <qdebug.h>

SavedMembersWidget::SavedMembersWidget(MembersTableModel* _model, QWidget *parent)
	: QWidget(parent), model(_model)
{
	ui.setupUi(this);
	ui.membersTableView->setModel(model);
	ui.membersTableView->setItemDelegate(new PictureDelegate{});
	ui.membersTableView->resizeColumnToContents(3);
	ui.membersTableView->resizeRowsToContents();
}

SavedMembersWidget::~SavedMembersWidget()
{
}

void SavedMembersWidget::update()
{
	model->emit layoutChanged();
	ui.membersTableView->resizeColumnToContents(3);
	ui.membersTableView->resizeRowsToContents();
}
