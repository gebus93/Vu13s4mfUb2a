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
	}

	int getHeight() const {
		return height;
	}

	void setHeight(int height) {
		this->height = height;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

	const string& getSurname() const {
		return surname;
	}

	void setSurname(const string& surname) {
		this->surname = surname;
	}

	int getWeight() const {
		return weight;
	}

	void setWeight(int weight) {
		this->weight = weight;
	}

	People() {
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

private:
	string name;
	string surname;
	int age;
	int height;
	int weight;
	unsigned long long int createDate;
};

#endif
