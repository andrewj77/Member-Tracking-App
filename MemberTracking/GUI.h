#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include "SavedMembersWidget.h"
#include "Service.h"


class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(Service&, SavedMembersWidget* table, QWidget *parent = Q_NULLPTR);

private:
    Ui::GUIClass ui;
    Service& service;
    SavedMembersWidget* table;
    //mode A 
    void fillMembersList();
    void connectSignals();
    void addMember();
    void deleteMember();
    void updateMember();
    void undoModeA();
    void redoModeA();
    void selectElementFromListAction();
    int getSelectedIndex();
    //mode B
    void next();
    void saveMember();
    void filterAgeProfession();
    void undoModeB();
    void redoModeB();
    void openMylistTable();
    void openFile();
};
