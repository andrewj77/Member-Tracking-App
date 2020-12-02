#pragma once
#include "Domain.h"
#include "FileRepository.h"

class HtmlRepository : public Repository
{
	private:
		string mylistLocation = "repo.html";

	public:
		void setFileLocation(const string&) override;
		void addMember(const Member&) override;
		Member deleteMember(const string&) override;
		Member updateMember(const Member&) override { return Member(); }
		void writeToFile(vector<Member>) const override;
		vector<Member> getAllMembers() const;
		Member getMember(const string&) const override;
		void openSavedList() const override;

		~HtmlRepository() = default;
};
