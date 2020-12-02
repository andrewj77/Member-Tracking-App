#pragma once
#include "Domain.h"
#include "FileRepository.h"

class CsvRepository : public Repository
{
	private:
		string mylistLocation = "repo.csv";

	public:
		void setFileLocation(const string&) override;
		void addMember(const Member&) override;
		Member updateMember(const Member&) override { return Member(); }
		Member deleteMember(const string&) override;
		void writeToFile(vector<Member>) const override;
		vector<Member> getAllMembers() const;
		Member getMember(const string&) const override;
		void openSavedList() const override;

		~CsvRepository() = default;
};