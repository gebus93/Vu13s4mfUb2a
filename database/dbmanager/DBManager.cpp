/*
 * DBManager.cpp
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#include "DBManager.h"

void DBManager::add(string dbName) {
	const Database<People> db(dbName);
	databases.push_back(db);
	modified = true;
}

void DBManager::add(Database<People> database) {
	Database<People> copy(database.getFileName(), database.getRows());
	databases.push_back(copy);
	modified = true;
}

vector<Database<People> > DBManager::getAll() {
	vector<Database<People> > temp;

	for (int i = 0, j = databases.size(); i < j; i++)
		temp.push_back(get(i));

	return temp;
}

Database<People> DBManager::get(int index) {
	Database<People> temp = databases[index];
	Database<People> copy(temp.getFileName(), temp.getRows());

	return copy;
}

void DBManager::update(int index, Database<People> &database) {
	remove(index);
	string fileName = database.getFileName();
	vector<People> rows = database.getRows();
	Database<People> temp(fileName, rows);
	databases.insert(databases.begin() + index, temp);

	modified = true;
}

void DBManager::remove(int index) {
	databases.erase(databases.begin() + index);
	modified = true;
}

bool DBManager::isModified() {
	return modified;
}

void DBManager::saveAs(const string& dbname) {
	ofstream file(dbname.c_str(), ios::out | ofstream::binary);
	int dbSize = databases.size();
	file.write(reinterpret_cast<const char*>(&dbSize), sizeof(dbSize));
	for (int i = 0; i < dbSize; i++) {
		Database<People> currentDatabase = databases[i];
		const string fileName = currentDatabase.getFileName();
		int nameSize = fileName.size();
		file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
		file.write(fileName.c_str(), nameSize);
		int rowsCount = currentDatabase.getRowsCount();
		vector<People> temp = currentDatabase.getRows();
		file.write(reinterpret_cast<const char*>(&rowsCount), sizeof(rowsCount));
		file.write(reinterpret_cast<const char*>(&temp[0]), rowsCount * sizeof(People));
	}
	file.close();
	modified = false;
}

void DBManager::save() {
	saveAs("databases.data");
}

void DBManager::load(const string& dbname) {
	std::ifstream file(dbname.c_str(), std::ios::in | std::ifstream::binary);

	if (!file.is_open())
		return;

	databases.clear();

	int size;
	file.read(reinterpret_cast<char*>(&size), sizeof(size));
	for (int i = 0; i < size; i++) {
		int nameSize;
		file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
		string fileName(nameSize, '\0');
		file.read(&fileName[0], nameSize);
		int rowsCount;
		file.read(reinterpret_cast<char*>(&rowsCount), sizeof(rowsCount));
		vector<People> temp(rowsCount);
		file.read(reinterpret_cast<char*>(&temp[0]), rowsCount * sizeof(People));
		const Database<People> databasePeople = Database<People>(fileName, temp);
		databases.push_back(databasePeople);
	}
	file.close();
}

void DBManager::load() {
	load("databases.data");
}

DBManager::~DBManager() {
}

DBManager& DBManager::getInstance() {
	static DBManager instance;
	return instance;
}

DBManager::DBManager() {
	modified = false;
	load();
}
