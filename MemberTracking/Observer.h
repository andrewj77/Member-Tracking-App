#pragma once
#include <vector>


class Observer
{
public:
	virtual void update() = 0;
	virtual ~Observer() {}
};

class Observable
{
private:
	std::vector<Observer*> observers;

public:
	void addObserver(Observer* observer)
	{
		observers.push_back(observer);
	}

	void removeObserver(Observer* observer)
	{
		auto observerElement = std::find(observers.begin(), observers.end(), observer);
		if (observerElement != observers.end())
			observers.erase(observerElement);
	}

	void notify()
	{
		for (auto observer : observers)
			observer->update();
	}
};