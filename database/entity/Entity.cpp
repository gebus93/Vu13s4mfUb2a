#ifndef PEOPLE_ENTITY_INCLUDED
#define PEOPLE_ENTITY_INCLUDED

#include <string>
#include <ctime>

using namespace std;

class People {
public:
	int getAge() const {
		return age;
	}

	void setAge(int age) {
		this->age = age;
		empty = false;
	}

	int getHeight() const {
		return height;
	}

	void setHeight(int height) {
		this->height = height;
		empty = false;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
		empty = false;
	}

	const string& getSurname() const {
		return surname;
	}

	void setSurname(const string& surname) {
		this->surname = surname;
		empty = false;
	}

	int getWeight() const {
		return weight;
	}

	void setWeight(int weight) {
		this->weight = weight;
		empty = false;
	}

	People() {
		empty = true;
		createDate = time(0);
		age = 0;
		height = 0;
		weight = 0;

	}

	unsigned long long int getCreateDate() const {
		return createDate;
	}

	bool operator==(const People& other) {
		return name == other.getName()
				&& surname == other.getSurname()
				&& age == other.getAge()
				&& weight == other.getWeight()
				&& height == other.getHeight();
	}

	bool operator!=(const People& other) {
		return !(*this == other);
	}

	bool isEmpty() const
	{
		return empty;
	}

private:
	string name;
	string surname;
	int age;
	int height;
	int weight;
	unsigned long long int createDate;
	bool empty;
};

#endif
