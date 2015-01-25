/*
 * DBManager.cpp
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#include "DBManager.h"
#include "../../util/utils.h"
#include <algorithm>

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

vector<Database<People> > DBManager::databases;

vector<Database<People> > DBManager::getAll() {
	vector<Database<People> > temp;

	for (int i = 0, j = databases.size(); i < j; i++)
		temp.push_back(get(i));

	return temp;
}

Database<People> DBManager::get(int index) {
	if (index >= (int) databases.size()) {
		logger.printErr(
				"Baza danych wskazana do skopiowania ma index wiekszy niz ilosc baz danych. DBManager::get(int)");
		exit(0);
	}

	return databases[index];
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

void DBManager::saveNextInt64(ofstream& file, unsigned long long int number) {
	file.write(reinterpret_cast<const char*>(&number),
			sizeof(unsigned long long int));
}

void DBManager::saveAs(const string& dbname) {
	ofstream file(dbname.c_str(), ios::out | ofstream::binary);

	saveNextInt64(file, Database<People>::next_id);

	int dbSize = databases.size();
	saveNextInt(file, dbSize);

	for (int i = 0; i < dbSize; i++) {
		Database<People> currentDatabase = databases[i];

		saveNextString(file, currentDatabase.getFileName());

		int rowsCount = currentDatabase.getRowsCount();
		saveNextInt(file, rowsCount);

		vector<People> temp = currentDatabase.getRows();

		for (int entityIndex = 0; entityIndex < rowsCount; ++entityIndex)
			saveNextEntity(file, temp[entityIndex]);

	}
	file.close();
	modified = false;
}

void DBManager::save() {
	saveAs("databases.data");
}

unsigned long long int DBManager::readNextInt64(std::ifstream& file) {
	unsigned long long int number;
	file.read(reinterpret_cast<char*>(&number), sizeof(unsigned long long int));
	return number;
}

void DBManager::load(const string& dbname) {
	std::ifstream file(dbname.c_str(), std::ios::in | std::ifstream::binary);

	if (!file.is_open()) {
		logger.printErr(
				"Nie udalo sie otworzyc pliku z baza danych - " + dbname);
		return;
	}

	logger.print("Udalo sie otworzyc plik z baza danych: " + dbname);

	databases.clear();

	logger.print("Udalo sie wyczyscic dotychczasowa liste baz danych.");

	Database<People>::next_id = readNextInt64(file);

	logger.print(" >> Wczytywanie ilosci baz danych");
	int size = readNextInt(file);
	for (int i = 0; i < size; i++) {

		logger.print(
				" >> Wczytywanie nazwy bazy danych o numerze "
						+ numberToString(i));
		string fileName = readNextString(file);

		logger.print(
				" >> Wczytywanie ilosci wpisow w bazie danych o numerze "
						+ numberToString(i));
		int rowsCount = readNextInt(file);

		vector<People> temp;

		while (rowsCount--)
			temp.push_back(readNextEntity(file));

		const Database<People> databasePeople = Database<People>(fileName,
				temp);
		databases.push_back(databasePeople);
	}

	logger.print("Udalo sie wczytac liste baz danych.");

	file.close();

	logger.print("Udalo sie zamknac plik z baza danych.");
}

void DBManager::load() {
	load("databases.data");
}

DBManager::~DBManager() {
	INSTANCE = NULL;
}

DBManager* DBManager::INSTANCE = NULL;

DBManager* DBManager::getInstance() {
	if (!DBManager::INSTANCE)
		DBManager::INSTANCE = new DBManager();

	return DBManager::INSTANCE;
}

DBManager::DBManager() {
	INSTANCE = NULL;
	modified = false;
	load();
}

int DBManager::count() {
	return (int) databases.size();
}

string DBManager::readNextString(ifstream& file) {
	int length = readNextInt(file);
	logger.print("Dlugosc napisu: " + numberToString(length));

	string text(length, '\0');
	file.read(&text[0], length);

	logger.print("Wczytano napis: " + text);

	return text;
}

int DBManager::readNextInt(ifstream& file) {
	int number;
	file.read(reinterpret_cast<char*>(&number), sizeof(int));

	logger.print("Wczytano liczbe: " + numberToString(number));

	return number;
}

void DBManager::saveNextString(ofstream& file, const string& s) {
	int length = s.size();
	file.write(reinterpret_cast<const char*>(&length), sizeof(length));
	file.write(s.c_str(), length);
}

void DBManager::saveNextInt(ofstream& file, int& i) {
	file.write(reinterpret_cast<const char*>(&i), sizeof(int));
}

People DBManager::readNextEntity(ifstream& file) {
	People person;
	file.read(reinterpret_cast<char*>(&person), sizeof(People));

	logger.print(
			"Wczytano osobe: " + person.getName() + " " + person.getSurname()
					+ " " + numberToString(person.getAge()) + " "
					+ numberToString(person.getHeight()) + " "
					+ numberToString(person.getWeight()));

	return person;
}

void DBManager::saveNextEntity(ofstream& file, const People& person) {
	file.write(reinterpret_cast<const char*>(&person), sizeof(People));
}
