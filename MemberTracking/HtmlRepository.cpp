#include "HtmlRepository.h"
#include <fstream>

void HtmlRepository::setFileLocation(const string& path)
{
	this->mylistLocation = path;
	if (ifstream(path).is_open() == false)
		ofstream file(path);
}

void HtmlRepository::addMember(const Member& newMember)
{
	vector<Member> members = this->getAllMembers();
	for (auto member : members)
		if (member.getName() == newMember.getName())
			throw RepositoryException("Duplicate member!");
	members.push_back(newMember);
	this->writeToFile(members);
}

Member HtmlRepository::deleteMember(const string& name)
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

void HtmlRepository::writeToFile(vector<Member> savedMembers) const
{
	ofstream outFile(this->mylistLocation);
	outFile << "<!DOCTYPE html> <html><head><title>SavedMembers</title></head><body><table border=\"1\">";
	outFile << "<tr><td>Name</td><td>Profession</td><td>Age</td><td>Photograph</td></tr>\n";
	for (auto member : savedMembers)
	{
		outFile << "<tr>\n";
		outFile << "<td>" << member.getName() << "</td>\n";
		outFile << "<td>" << member.getProfession() << "</td>\n";
		outFile << "<td>" << member.getAge() << "</td>\n";
		outFile << "<td>" << member.getPhotograph() << "</td>\n";
		outFile << "</tr>\n";
	}
	outFile << "</table></body></html>";
	outFile.close();
}

vector<Member> HtmlRepository::getAllMembers() const
{
	ifstream inFile(this->mylistLocation);
	vector<Member> savedMembers;
	Member member;
	string line;
	getline(inFile, line);
	if (line == "")
		return {};
	getline(inFile, line);
	while (line.substr(0, 8) != "</table>")
	{
		for (int i = 0; i < 6; ++i)
		{
			if (i >= 1 && i <= 4)
			{
				string currentColumnData = line.substr(4);
				currentColumnData.resize(currentColumnData.size() - 5);
				if (i == 1) member.setName(currentColumnData);
				else if (i == 2) member.setProfession(currentColumnData);
				else if (i == 3) member.setAge(stoi(currentColumnData));
				else if (i == 4) member.setPhotograph(currentColumnData);
			}
			getline(inFile, line);
		}
		savedMembers.push_back(member);
	}
	inFile.close();
	return savedMembers;
}

Member HtmlRepository::getMember(const string& name) const
{
	vector<Member> allMembers = this->getAllMembers();
	for (auto member : allMembers)
		if (member.getName() == name)
			return member;
	return Member();
}

void HtmlRepository::openSavedList() const
{
	const char* application = this->mylistLocation.c_str();
	system(application);
}