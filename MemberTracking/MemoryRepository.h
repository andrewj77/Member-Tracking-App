#pragma once
#include "Domain.h"
#include "FileRepository.h"

class MemoryRepository : public Repository
{

private:
	vector<Member> allMembers;

public:
	void addMember(const Member&) override;
	Member updateMember(const Member&) override;
	Member deleteMember(const string&) override;
	Member getMember(const string&) const override;
	vector<Member> getAllMembers() const override;

	~MemoryRepository() = default;
};

