#ifndef PEOPLE_ENTITY_INCLUDED
#define PEOPLE_ENTITY_INCLUDED

#include <string>
#include <string.h>
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

	const string getName() const {
		string s(this->name);
		return s;
	}

	void setName(const string& name) {
		strcpy(this->name, name.c_str());
		this->name[name.size()] = '\0';

		empty = false;
	}

	const string getSurname() const {
		string s(this->surname);
		return s;
	}

	void setSurname(const string& surname) {
		strcpy(this->surname, surname.c_str());
		this->surname[surname.size()] = '\0';
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
	char name[100];
	char surname[100];
	int age;
	int height;
	int weight;
	unsigned long long int createDate;
	bool empty;
};

#endif
