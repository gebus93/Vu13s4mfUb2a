/*
 * DBManager.h
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#ifndef DATABASE_DBMANAGER_DBMANAGER_H_
#define DATABASE_DBMANAGER_DBMANAGER_H_

#include <string>
#include <vector>
#include <fstream>

#include "../../util/logger/Logger.h"
#include "../database/Database.cpp"
#include "../entity/Entity.cpp"

using namespace std;

class DBManager {
public:
	DBManager();
	static DBManager * getInstance();
	void add(string);
	void add(Database<People>);
	vector<Database<People> > getAll();
	Database<People> get(int);
	void update(int index, Database<People> &database);
	void remove(int index);
	bool isModified();
	void save();
	void saveAs(const string& dbname);
	void load();
	void load(const string& dbname);
	int count();
	virtual ~DBManager();
	static DBManager* INSTANCE;

private:

	static vector<Database<People> > databases;

	string readNextString(ifstream &file);
	void saveNextString(ofstream &file, const string& s);

	int readNextInt(ifstream &file);
	void saveNextInt(ofstream &file, int& i);

	People readNextEntity(ifstream &file);
	void saveNextEntity(ofstream &file, const People& p);
	void saveNextInt64(ofstream& file, unsigned long long int number);
	unsigned long long int readNextInt64(std::ifstream& file);

	bool modified;
	Logger logger;
};

#endif /* DATABASE_DBMANAGER_DBMANAGER_H_ */
