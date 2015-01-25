/*
 * dbgenerator.cpp
 *
 *  Created on: 24 sty 2015
 *      Author: Łukasz
 */

#include <cstdio>
#include <string>
#include <vector>
#include "windows.h"

#include "database/database/Database.cpp"
#include "database/dbmanager/DBManager.h"
#include "database/entity/Entity.cpp"

void readDatabase(FILE* input) {
	char dbname[100];
	fscanf(input, "%s", dbname);

	int rowsCount;
	fscanf(input, "%d\n", &rowsCount);

	std::vector<People> rows;

	while (rowsCount--)
	{
		Sleep(100);

		char name[100];
		char surname[100];
		int age, height, weight;
		fscanf(input, "%99[^,],%99[^,],%d,%d,%d\n", name, surname, &age, &height, &weight);

		People person;
		person.setName(string(name));
		person.setSurname(string(surname));
		person.setAge(age);
		person.setHeight(height);
		person.setWeight(weight);

		rows.push_back(person);
	}

	Database<People> db(string(dbname), rows);

	DBManager::getInstance()->add(db);

}

void generateDatabase() {
	FILE* input = fopen("../dane.txt", "r");

	if (input == NULL)
		return;

	int databaseCount;

	fscanf(input, "%d", &databaseCount);

	while (databaseCount--)
		readDatabase(input);

	fclose(input);
	DBManager::getInstance()->save();
}

