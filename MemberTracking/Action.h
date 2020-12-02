#pragma once
#include "Repository.h"

class Action
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
};

class ActionAdd : public Action
{
private:
	Member addedMember;
	shared_ptr<Repository>& repository;

public:
	ActionAdd(Member _member, shared_ptr<Repository>& _repository) :
		addedMember(_member), repository(_repository) {}
	void executeUndo() override;
	void executeRedo() override;
};

class ActionUpdate : public Action
{
private:
	Member updatedMember;
	Member afterUpdate;
	shared_ptr<Repository>& repository;

public:
	ActionUpdate(Member _member, Member __member, shared_ptr<Repository>& _repository) :
		updatedMember(_member), afterUpdate(__member), repository(_repository) {}
	void executeUndo() override;
	void executeRedo() override;
};

class ActionDelete : public Action
{
private:
	Member deletedMember;
	shared_ptr<Repository>& repository;

public:
	ActionDelete(Member _member, shared_ptr<Repository>& _repository) :
		deletedMember(_member), repository(_repository) {}
	void executeUndo() override;
	void executeRedo() override;
};