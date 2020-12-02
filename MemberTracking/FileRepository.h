#pragma once
#include "Domain.h"
#include "Repository.h"
#include <fstream>
#include <sstream>


class RepositoryException : public exception
{
	private:
		string errorMessage;

	public:
		RepositoryException(string);
		const char* what();
};

class FileRepository : public Repository
{
	private:
		string fileLocation = "repo.txt";

	public:
		void setFileLocation(const string&) override;
		void addMember(const Member&) override;
		Member updateMember(const Member&) override;
		Member deleteMember(const string&) override;
		void writeToFile(vector<Member>) const override;
		void openSavedList() const override {}
		Member getMember(const string&) const override;
		vector<Member> getAllMembers() const override;

		~FileRepository() = default;
};
