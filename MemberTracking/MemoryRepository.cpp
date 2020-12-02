#include "MemoryRepository.h"


void MemoryRepository::addMember(const Member& newMember)
{
	for (auto member : allMembers)
		if (member.getName() == newMember.getName())
			throw RepositoryException("Duplicate Member!\n");
	allMembers.push_back(newMember);
}

Member MemoryRepository::updateMember(const Member& updatedMember)
{
	for (auto member = allMembers.begin(); member != allMembers.end(); ++member)
		if (member->getName() == updatedMember.getName())
		{
			Member beforeUpdate = *member;
			allMembers[std::distance(allMembers.begin(), member)] = updatedMember;
			return beforeUpdate;
		}
	throw RepositoryException("Not existing member!\n");
}

Member MemoryRepository::deleteMember(const string& name)
{
	for (auto member = allMembers.begin(); member != allMembers.end(); ++member)
	{
		if (member->getName() == name)
		{
			Member deletedMember = *member;
			allMembers.erase(member);
			return deletedMember;
		}
	}
	throw RepositoryException("Not existing member!\n");
}

Member MemoryRepository::getMember(const string& name) const
{
	for (auto member : allMembers)
		if (member.getName() == name)
			return member;
	return Member();
}

vector<Member> MemoryRepository::getAllMembers() const
{
	return this->allMembers;
}
