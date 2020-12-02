#pragma once
#include "Domain.h"

class Repository
{
public:
	virtual void setFileLocation(const string&) {}
	virtual void addMember(const Member&) = 0;
	virtual Member updateMember(const Member&) = 0;
	virtual Member deleteMember(const string&) = 0;
	virtual vector<Member> getAllMembers() const = 0;
	virtual void writeToFile(vector<Member>) const {}
	virtual void openSavedList() const {}
	virtual Member getMember(const string&) const = 0;

	virtual ~Repository() = default;
};

