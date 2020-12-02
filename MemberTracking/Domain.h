#pragma once
#include <string>
#include <iostream>
#include "Constants.h"
#include <vector>

using namespace std;


class Member
{
private:
	string name;
	string profession;
	int age;
	string photograph;

public:
	Member();
	Member(const string&, const string&, const int&, const string&);

	string getName() const { return name; }
	string getProfession() const { return profession; }
	int getAge() const { return age; }
	string getPhotograph() const { return photograph; }

	void setName(const string value) { this->name = value;  }
	void setProfession(const string value) { this->profession = value; }
	void setAge(const int value) { this->age = value; }
	void setPhotograph(const string value) { this->photograph = value; }

	friend istream & operator >> (istream&, Member&);
	friend ostream & operator << (ostream&, const Member&);

	string formatPrinting();
};

/*
template<typename TElement>
class DynamicVector
{
private:
	int size;
	int capacity;
	TElement* elements;

	void resize();

public:
	DynamicVector(int capacity = 10);
	DynamicVector(const DynamicVector&);
	~DynamicVector();
	DynamicVector& operator = (const DynamicVector&);

	int getSize() const { return this->size; }
	void addElement(const TElement&);
	TElement getElement(const int& position) const { return this->elements[position]; }
	void removeElement(const int& position);
	void setElement(const int& position, TElement newMember) { this->elements[position] = newMember; }
};

template<typename TElement>
DynamicVector<TElement>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new TElement[capacity];
}

template<typename TElement>
DynamicVector<TElement>::DynamicVector(const DynamicVector& other)
{
	this->size = other.size;
	this->capacity = other.capacity;
	this->elements = new TElement[this->capacity];
	for (int i = 0; i < this->size; ++i)
		this->elements[i] = other.elements[i];
}

template<typename TElement>
DynamicVector<TElement>::~DynamicVector()
{
	delete[] this->elements;
}

template<typename TElement>
DynamicVector<TElement>& DynamicVector<TElement>::operator = (const DynamicVector& other)
{
	if (this != &other)
	{
		TElement* newElements = new TElement[other.capacity];
		for (int i = 0; i < this->size; ++i)
			newElements[i] = other.elements[i];

		delete[] this->elements;

		this->elements = newElements;
		this->size = other.size;
		this->capacity = other.capacity;
	}
	return *this;
}

template<typename TElement>
void DynamicVector<TElement>::addElement(const TElement& element)
{
	if (this->size == this->capacity)
		this->resize();
	this->elements[this->size] = element;
	this->size++;
}

template<typename TElement>
void DynamicVector<TElement>::removeElement(const int& position)
{
	this->size--;
	for (int i = position; i < this->size; ++i)
		this->elements[i] = this->elements[i + 1];
}

template<typename TElement>
void DynamicVector<TElement>::resize()
{
	this->capacity *= 2;
	TElement* newElements = new TElement[this->capacity];
	for (int i = 0; i < this->size; ++i)
		newElements[i] = this->elements[i];

	delete[] this->elements;

	this->elements = newElements;
}
*/


