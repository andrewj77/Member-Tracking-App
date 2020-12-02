#include "FileRepository.h"

RepositoryException::RepositoryException(string errorMessage)
{
	this->errorMessage = errorMessage;
}

const char* RepositoryException::what()
{
	return this->errorMessage.c_str();
}

void FileRepository::setFileLocation(const string& path)
{
	this->fileLocation = path;
	if (ifstream(path).is_open() == false)
		ofstream file(path);
}

void FileRepository::addMember(const Member& newMember)
{
	vector<Member> members = this->getAllMembers();
	for (auto member : members)
		if (member.getName() == newMember.getName())
			throw RepositoryException("Duplicate Member!\n");
	members.push_back(newMember);
	this->writeToFile(members);
}

Member FileRepository::updateMember(const Member& updatedMember)
{
	vector<Member> members = this->getAllMembers();
	for (auto member = members.begin(); member != members.end(); ++member)
		if (member->getName() == updatedMember.getName())
		{
			Member beforeUpdate = *member;
			members[distance(members.begin(), member)] = updatedMember; //setElement(i, updatedMember);
			this->writeToFile(members);
			return beforeUpdate;
		}
	throw RepositoryException("Not existing member!\n");
}

Member FileRepository::deleteMember(const string& name)
{
	vector<Member> members = this->getAllMembers();
	for (auto member = members.begin(); member != members.end(); ++member)
	{
		if (member->getName() == name)
		{
			Member deletedMember = *member;
			members.erase(member);
			this->writeToFile(members);
			return deletedMember;
		}
	}
	throw RepositoryException("Not existing member!\n");
}

void FileRepository::writeToFile(vector<Member> members) const
{
	ofstream outFile(this->fileLocation);
	for (auto member : members)
		outFile << member << "\n";
	outFile.close();
}

Member FileRepository::getMember(const string& name) const
{
	vector<Member> members = this->getAllMembers();
	for (auto member : members)
		if (member.getName() == name)
			return member;
	return Member();
}

vector<Member> FileRepository::getAllMembers() const
{
	ifstream inFile(this->fileLocation);
	vector<Member> allMembers;
	Member member;
	while (inFile >> member)
		allMembers.push_back(member);
	inFile.close();
	return allMembers;
}