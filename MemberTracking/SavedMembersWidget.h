#pragma once

#include <QWidget>
#include "ui_SavedMembersWidget.h"
#include "MembersTableModel.h"
#include "Service.h"

class SavedMembersWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	SavedMembersWidget(MembersTableModel*, QWidget *parent = Q_NULLPTR);
	~SavedMembersWidget();

private:
	Ui::SavedMembersWidget ui;
	MembersTableModel* model;
	void update() override;
};
