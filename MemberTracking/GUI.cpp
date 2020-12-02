#include "GUI.h"
#include <qmessagebox.h>
#include <qshortcut.h>


GUI::GUI(Service& _service, SavedMembersWidget* _table, QWidget *parent)
    : QMainWindow(parent), table(_table), service(_service)
{
    ui.setupUi(this);
    this->fillMembersList();
    this->connectSignals();
}

void GUI::fillMembersList()
{
    this->ui.membersListWidget->clear();
    vector<Member> members = service.getAllMembers();
    for (auto member : members)
        ui.membersListWidget->addItem(QString::fromStdString(member.getName() + " " + member.getProfession() + " " +
            to_string(member.getAge()) + " " + member.getPhotograph()));
}

void GUI::connectSignals()
{
	//mode A
    QObject::connect(ui.membersListWidget, &QListWidget::itemSelectionChanged, this, &GUI::selectElementFromListAction);
    QObject::connect(ui.addButton, &QPushButton::clicked, this, &GUI::addMember);
    QObject::connect(ui.deleteButton, &QPushButton::clicked, this, &GUI::deleteMember);
    QObject::connect(ui.updateButton, &QPushButton::clicked, this, &GUI::updateMember);
    QObject::connect(ui.undoButton, &QPushButton::clicked, this, &GUI::undoModeA);
	QShortcut* shortcutUndo = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QObject::connect(shortcutUndo, &QShortcut::activated, this, &GUI::undoModeA);
    QObject::connect(ui.redoButton, &QPushButton::clicked, this, &GUI::redoModeA);
	QShortcut* shortcutRedo = new QShortcut(QKeySequence("Ctrl+Y"), this);
	QObject::connect(shortcutRedo, &QShortcut::activated, this, &GUI::redoModeA);
	//mode B
	QObject::connect(ui.nextButton, &QPushButton::clicked, this, &GUI::next);
	QObject::connect(ui.saveButton, &QPushButton::clicked, this, &GUI::saveMember);
	QObject::connect(ui.filterButton, &QPushButton::clicked, this, &GUI::filterAgeProfession);
	QObject::connect(ui.undoBButton, &QPushButton::clicked, this, &GUI::undoModeB);
	QShortcut* shortcutUndoB = new QShortcut(QKeySequence("Ctrl+U"), this);
	QObject::connect(shortcutUndoB, &QShortcut::activated, this, &GUI::undoModeB);
	QObject::connect(ui.redoBButton, &QPushButton::clicked, this, &GUI::redoModeB);
	QShortcut* shortcutRedoB = new QShortcut(QKeySequence("Ctrl+R"), this);
	QObject::connect(shortcutRedoB, &QShortcut::activated, this, &GUI::redoModeB);
	QObject::connect(ui.openMylistButton, &QPushButton::clicked, this, &GUI::openMylistTable);
	QObject::connect(ui.openFileButton, &QPushButton::clicked, this, &GUI::openFile);
}

void GUI::addMember()
{
	string name = ui.nameLineEdit->text().toStdString();
	string profession = ui.professionLineEdit->text().toStdString();
	string age = ui.ageLineEdit->text().toStdString();
	string photograph = ui.photographLineEdit->text().toStdString();
	try {
		service.addMember(name, profession, age, photograph);
	}
	catch (RepositoryException& error) {
		int selectedIndex = getSelectedIndex();
		QMessageBox::warning(this, "Repository Error!", error.what());
		ui.membersListWidget->setCurrentRow(selectedIndex);
		return;
	}
	catch (ValidationException& error)
	{
		int selectedIndex = getSelectedIndex();
		QMessageBox::warning(this, "Validation Error!", error.what());
		ui.membersListWidget->setCurrentRow(selectedIndex);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(this, "Validation Error!", "Unexpected error!");
		return;
	}
	fillMembersList();
	int lastIndex = service.getAllMembers().size() - 1;
	ui.membersListWidget->setCurrentRow(lastIndex);
}

void GUI::deleteMember()
{
	int selectedIndex = getSelectedIndex();
	if (selectedIndex < 0)
	{
		QMessageBox::critical(this, "Error", "Nothing is selected!");
		return;
	}
	Member member = service.getAllMembers()[selectedIndex];
	service.deleteMember(member.getName());
	fillMembersList();
}

void GUI::updateMember()
{
	int selectedIndex = getSelectedIndex();
	if (selectedIndex < 0)
	{
		QMessageBox::warning(this, "Error", "Nothing is selected!");
		return;
	}
	Member member = service.getAllMembers()[selectedIndex];
	string newProfession = ui.professionLineEdit->text().toStdString();
	string newAge = ui.ageLineEdit->text().toStdString();
	string newPhotograph = ui.photographLineEdit->text().toStdString();
	service.updateMember(member.getName(), newProfession, newAge, newPhotograph);
	fillMembersList();
	ui.membersListWidget->setCurrentRow(selectedIndex);
}

void GUI::undoModeA()
{
	try {
		service.undoModeA();	
	}
	catch (exception) {
		QMessageBox::warning(this, "Undo Error!", "Nothing more to undo!");
		return;
	}
	fillMembersList();
}

void GUI::redoModeA()
{
	try {
		service.redoModeA();
	}
	catch (exception) {
		QMessageBox::warning(this, "Redo Error!", "Nothing more to redo!");
		return;
	}
	fillMembersList();
}

void GUI::selectElementFromListAction()
{
	int selectedIndex = getSelectedIndex();
	if (selectedIndex < 0)
		return;
	Member member = service.getAllMembers()[selectedIndex];
	ui.nameLineEdit->setText(QString::fromStdString(member.getName()));
	ui.professionLineEdit->setText(QString::fromStdString(member.getProfession()));
	ui.ageLineEdit->setText(QString::fromStdString(to_string(member.getAge())));
	ui.photographLineEdit->setText(QString::fromStdString(member.getPhotograph()));
}

int GUI::getSelectedIndex()
{
	QModelIndexList selectedIndexes = ui.membersListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		ui.nameLineEdit->clear();
		ui.professionLineEdit->clear();
		ui.ageLineEdit->clear();
		ui.photographLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void GUI::next()
{
	try {
		Member member = service.getNextMember();
		ui.nextLineEdit->setText(QString::fromStdString(member.getName() + ", " + member.getProfession() + ", "
			+ to_string(member.getAge()) + ", " + member.getPhotograph()));
	}
	catch (exception) {
		QMessageBox::warning(this, "Next error!", "The members list is empty!");
		return;
	}
}

void GUI::saveMember()
{
	string name = ui.saveLineEdit->text().toStdString();
	try {
		service.saveMember(name);
	}
	catch (RepositoryException& e) {
		QMessageBox::warning(this, "Save Error!", e.what());
		return;
	}
	catch (exception& e) {
		QMessageBox::warning(this, "Save Error!", e.what());
		return;
	}
}

void GUI::filterAgeProfession()
{
	string age = ui.ageLineEdit_2->text().toStdString();
	string profession = ui.professionLineEdit_2->text().toStdString();
	try {
		vector<Member> filteredMembers = service.getCustomMembers(profession, age);
		ui.filteredListWidget->clear();
		for (auto member : filteredMembers)
			ui.filteredListWidget->addItem(QString::fromStdString(member.getName() + " " + member.getProfession() + " " +
				to_string(member.getAge()) + " " + member.getPhotograph()));
	}
	catch (exception) {
		QMessageBox::warning(this, "Filter error!", "Invalid age!");
		return;
	}
}

void GUI::undoModeB()
{
	try {
		service.undoModeB();
	}
	catch (exception) {
		QMessageBox::warning(this, "Redo Error!", "Nothing more to redo!");
		return;
	}
	fillMembersList();
}

void GUI::redoModeB()
{
	try {
		service.redoModeB();
	}
	catch (exception) {
		QMessageBox::warning(this, "Redo Error!", "Nothing more to redo!");
		return;
	}
	fillMembersList();
}

void GUI::openMylistTable()
{
	table->show();
}

void GUI::openFile()
{
	service.openSavedList();
}
