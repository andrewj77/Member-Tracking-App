#include "Service.h"


Service::Service(const Validator& _validator, shared_ptr<Repository> _repository, shared_ptr<Repository> _fileRepository)
	: validator{ _validator }, repository{ _repository }, fileRepository{ _fileRepository } {}

void Service::addMember(const string& name, const string& profession, const string& age, const string& photograph)
{
	validator.validateAge(age);
	validator.validateStrings(name, profession, photograph);
	Member member{ name, profession, stoi(age), photograph };
	repository->addMember(member);
	undoStackModeA.push_back(make_shared<ActionAdd>(member, repository));
}

void Service::updateMember(const string& name, const string& newProfession, const string& newAge, const string& newPhotograph)
{
	validator.validateAge(newAge);
	validator.validateStrings(name, newProfession, newPhotograph);
	Member memberToUpdate{ name, newProfession, stoi(newAge), newPhotograph };
	Member updatedMember = repository->updateMember(memberToUpdate);
	undoStackModeA.push_back(make_shared<ActionUpdate>(updatedMember, memberToUpdate, repository));
}

void Service::deleteMember(const string& name)
{
	validator.validateString(name);
	Member deletedMember = repository->deleteMember(name);
	undoStackModeA.push_back(make_shared<ActionDelete>(deletedMember, repository));
}

Member Service::getNextMember()
{
	vector<Member> members = repository->getAllMembers();
	if (members.size() == 0)
		throw exception();
	this->currentMember++;
	if (this->currentMember == members.size())
		this->currentMember = 0;
	return members[currentMember];
}

void Service::undoModeA()
{
	if (undoStackModeA.size() == 0)
		throw exception("Nothing more to undo!\n");
	shared_ptr<Action> action = undoStackModeA.back();
	undoStackModeA.pop_back();
	action->executeUndo();
	redoStackModeA.push_back(action);
}

void Service::redoModeA()
{
	if (redoStackModeA.size() == 0)
		throw exception("Nothing more to redo!\n");
	shared_ptr<Action> action = redoStackModeA.back();
	redoStackModeA.pop_back();
	action->executeRedo();
	undoStackModeA.push_back(action);
}

void Service::saveMember(string name) 
{
	Member member = repository->getMember(name);
	if (member.getName() == "")
		throw exception("Member does not exist in the main list!");
	fileRepository->addMember(member);
	undoStackModeB.push_back(make_shared<ActionAdd>(member, fileRepository));
	this->notify();
}


vector<Member> Service::getCustomMembers(const string& profession, const string& age) const
{
	validator.validateAge(age);
	int ageLimit = stoi(age);
	vector<Member> customMembers;
	vector<Member> allMembers = fileRepository->getAllMembers();
	for (auto member : allMembers)
	{
		if ((profession == "" || member.getProfession() == profession) && member.getAge() < ageLimit)
			customMembers.push_back(member);
	}
	return customMembers;
}

void Service::undoModeB()
{
	if (undoStackModeB.size() == 0)
		throw exception("Nothing more to undo!\n");
	shared_ptr<Action> action = undoStackModeB.back();
	undoStackModeB.pop_back();
	action->executeUndo();
	this->notify();
	redoStackModeB.push_back(action);
}

void Service::redoModeB()
{
	if (redoStackModeB.size() == 0)
		throw exception("Nothing more to redo!\n");
	shared_ptr<Action> action = redoStackModeB.back();
	redoStackModeB.pop_back();
	action->executeRedo();
	this->notify();
	undoStackModeB.push_back(action);
}

void Service::setFileLocation(string path)
{
	this->repository->setFileLocation(path);
}

void Service::setMylistLocation(string path)
{
	if (path.back() == 'v' || path.back() == 't')
		this->fileType = CSV;
	else if (path.back() == 'l')
		this->fileType = HTML;
}

void Service::openSavedList() const
{
	fileRepository->openSavedList();
}
