#include "Domain.h"
#include <sstream>

Member::Member(const string& name, const string& profession, const int& age, const string& photograph)
{
	this->name = name;
	this->profession = profession;
	this->age = age;
	this->photograph = photograph;
}

Member::Member() : name(""), profession(""), age(0), photograph("") {}
/*Member::Member()
{
	this->name = "";
	this->profession = "";
	this->age = 0;
	this->photograph = "";
}*/

string Member::formatPrinting()
{
	return "Name: " + this->name + ", Profession: " + this->profession + ", Age: " + to_string(age) + \
		", Photograph: " + this->photograph;
}

istream& operator >> (istream& input, Member& member)
{
	string line;
	getline(input, line);
	stringstream separator(line);
	vector<string> elements;
	while (separator.good())
	{
		string element;
		getline(separator, element, ',');
		elements.push_back(element);
	}
	if (elements.size() != 4)
		return input;
	member.name = elements[0];
	member.profession = elements[1];
	member.age = stoi(elements[2]);
	member.photograph = elements[3];
	return input;
}

ostream& operator << (ostream& output, const Member& member)
{
	output << member.name << "," << member.profession << "," << member.age << "," << member.photograph;
	return output;
}
