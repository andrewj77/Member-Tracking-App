#include "CsvRepository.h"
#include <fstream>

void CsvRepository::setFileLocation(const string& path)
{
	mylistLocation = path;
	if (ifstream(path).is_open() == false)
		ofstream file(path);
}

void CsvRepository::addMember(const Member& newMember)
{
	vector<Member> members = this->getAllMembers();
	for (auto member : members)
		if (member.getName() == newMember.getName())
			throw RepositoryException("Duplicate member!");
	members.push_back(newMember);
	this->writeToFile(members);
}


Member CsvRepository::deleteMember(const string& name)
{
	vector<Member> members = this->getAllMembers();
	for (auto member = members.begin(); member != members.end(); ++member)
		if (member->getName() == name)
		{
			Member deletedMember = *member;
			members.erase(member);
			this->writeToFile(members);
			return deletedMember;
		}
}

void CsvRepository::writeToFile(vector<Member> savedMembers) const
{
	ofstream outFile(this->mylistLocation);
	for (auto member : savedMembers)
		outFile << member << "\n";
	outFile.close();
}

vector<Member> CsvRepository::getAllMembers() const
{
	ifstream inFile(this->mylistLocation);
	vector<Member> savedMembers;
	Member member;
	while (inFile >> member)
		savedMembers.push_back(member);
	inFile.close();
	return savedMembers;
}

Member CsvRepository::getMember(const string& name) const
{
	vector<Member> allMembers = this->getAllMembers();
	for (auto member : allMembers)
		if (member.getName() == name)
			return member;
	return Member();
}

void CsvRepository::openSavedList() const
{
	const char* application = this->mylistLocation.c_str();
	system(application);
}