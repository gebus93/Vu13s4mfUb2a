/*
 * DBManager_test.cpp
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#include "DBManager.h"

#include <cstdio>
#include <cstdlib>
#include <string>

#include "../../util/logger/Logger.h"

using namespace std;

class DBManager_test {
public:
	int start();

private:
	Logger logger;
	bool thatCanGetInstance();
	bool thatCanCreateDatabase();
	bool thatCanRemoveDatabase();
	bool thatCanUpdateDatabase();
	bool thatCanPersistDatabase();
	People createExamplePerson();

};

inline int DBManager_test::start() {
	if (!thatCanGetInstance())
		exit(0);

	if (!thatCanCreateDatabase())
		exit(0);

	if (!thatCanRemoveDatabase())
		exit(0);

	if (!thatCanUpdateDatabase())
		exit(0);

	if (!thatCanPersistDatabase())
		exit(0);

	logger.print("DBManager_test finished correctly.");

	return 0;
}

inline bool DBManager_test::thatCanGetInstance() {

	try {
		DBManager dbManager = DBManager::getInstance();

		logger.print("DBManager_test.thatCanGetInstance() finished correctly.");
		return true;
	} catch (int e) {
		logger.printErr("DBManager_test.thatCanGetInstance() failed.");
		return false;
	}

}

inline bool DBManager_test::thatCanCreateDatabase() {

	try {
		DBManager dbManager = DBManager::getInstance();

		string dbname = "baza danych";
		dbManager.add(dbname);
		vector<Database<People> > all = dbManager.getAll();

		if (all.size() != 1) {
			logger.printErr("DBManager_test.thatCanCreateDatabase() failed. Size is not equal 1.");
			return false;
		}

		if (all[0].getFileName() != dbname) {
			logger.printErr("DBManager_test.thatCanCreateDatabase() failed. Database name is incorrect.");
			return false;
		}

		logger.print("DBManager_test.thatCanCreateDatabase() finished correctly.");
		return true;
	} catch (int e) {
		logger.printErr("DBManager_test.thatCanCreateDatabase() failed.");
		return false;
	}

}

inline bool DBManager_test::thatCanRemoveDatabase() {
	try {
		DBManager dbManager = DBManager::getInstance();

		string dbname = "baza danych";
		dbManager.add(dbname);

		if (dbManager.getAll().size() != 1) {
			logger.printErr("DBManager_test.thatCanRemoveDatabase() failed. Size is not equal 1.");
			return false;
		}

		dbManager.remove(0);

		if (dbManager.getAll().size() != 0) {
			logger.printErr("DBManager_test.thatCanRemoveDatabase() failed. Size is not equal 0.");
			return false;
		}

		logger.print("DBManager_test.thatCanRemoveDatabase() finished correctly.");
		return true;
	} catch (int e) {
		logger.printErr("DBManager_test.thatCanRemoveDatabase() failed.");
		return false;
	}
}

inline bool DBManager_test::thatCanUpdateDatabase() {
	try {
		DBManager dbManager = DBManager::getInstance();

		string dbname = "baza danych";
		dbManager.add(dbname);
		Database<People> db = dbManager.get(0);
		db.addRow(createExamplePerson());
		dbManager.update(0, db);

		if (dbManager.isModified() == false) {
			logger.printErr("DBManager_test.thatCanUpdateDatabase() failed. DBManager should be in modified state.");
			return false;
		}

		logger.print("DBManager_test.thatCanUpdateDatabase() finished correctly.");
		return true;
	} catch (int e) {
		logger.printErr("DBManager_test.thatCanUpdateDatabase() failed.");
		return false;
	}
}

inline People DBManager_test::createExamplePerson() {
	People janKowalski;
	janKowalski.setName("Jan");
	janKowalski.setSurname("Kowalski");
	janKowalski.setAge(21);
	janKowalski.setHeight(173);
	janKowalski.setWeight(73);
	return janKowalski;
}

inline bool DBManager_test::thatCanPersistDatabase() {
	try {
		DBManager dbManager = DBManager::getInstance();

		string dbname = "baza danych";
		dbManager.add(dbname);
		Database<People> db = dbManager.get(0);
		db.addRow(createExamplePerson());
		dbManager.update(0, db);

		vector<Database<People> > beforeSave = dbManager.getAll();

		dbManager.saveAs("test.tmp");
		dbManager.load("test.tmp");
		vector<Database<People> > afterLoad = dbManager.getAll();
		int beforeSaveSize = beforeSave.size();
		int AfterLoadSize = afterLoad.size();

		if (beforeSaveSize != AfterLoadSize) {
			logger.printErr("DBManager_test.thatCanPersistDatabase() failed. DBManager after load is incorrect.");
			return false;
		}

		for (int i = 0, j = beforeSave.size(); i < j; i++)
			if (beforeSave[i] != afterLoad[i])
				return false;

		logger.print("DBManager_test.thatCanPersistDatabase() finished correctly.");
		return true;
	} catch (int e) {
		logger.printErr("DBManager_test.thatCanPersistDatabase() failed.");
		return false;
	}
}
