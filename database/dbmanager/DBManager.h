/*
 * DBManager.h
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#ifndef DATABASE_DBMANAGER_DBMANAGER_H_
#define DATABASE_DBMANAGER_DBMANAGER_H_

#include <vector>

#include <algorithm>
#include <fstream>
#include <string>

#include "../database/Database.cpp"
#include "../entity/Entity.cpp"

using namespace std;

class DBManager {
public:
	static DBManager& getInstance();
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

private:
	vector<Database<People> > databases;
	bool modified;
	DBManager();
};

#endif /* DATABASE_DBMANAGER_DBMANAGER_H_ */
