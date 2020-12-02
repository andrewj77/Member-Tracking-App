#pragma once
#include "FileRepository.h"
#include "CsvRepository.h"
#include "HtmlRepository.h"
#include "MemoryRepository.h"
#include "Repository.h"
#include "Validator.h"
#include "Action.h"
#include "Observer.h"

class Service : public Observable
{
	private:
		Validator validator;
		shared_ptr<Repository> repository;
		shared_ptr<Repository> fileRepository;
		vector<shared_ptr<Action>> undoStackModeA;
		vector<shared_ptr<Action>> redoStackModeA;
		vector<shared_ptr<Action>> undoStackModeB;
		vector<shared_ptr<Action>> redoStackModeB;
		int currentMember = -1;
		int fileType = CSV;

	public:
		Service(const Validator&, shared_ptr<Repository>, shared_ptr<Repository>);

		void addMember(const string&, const string&, const string&, const string&);
		void updateMember(const string&, const string&, const string&, const string&);
		void deleteMember(const string&);

		Member getNextMember();
		vector<Member> getAllMembers() const { return this->repository->getAllMembers(); }
		vector<Member> getSavedMembers() const { return this->fileRepository->getAllMembers(); }
		void saveMember(string);
		vector<Member> getCustomMembers(const string&, const string&) const;
		void setFileLocation(string);
		void setMylistLocation(string);
		void undoModeA();
		void redoModeA();
		void undoModeB();
		void redoModeB();

		void openSavedList() const;
};