/*
 * SelectedDatabaseActionListener.h
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#ifndef ACTIONLISTENER_DATABASE_SELECTEDDATABASEACTIONLISTENER_H_
#define ACTIONLISTENER_DATABASE_SELECTEDDATABASEACTIONLISTENER_H_

#include "../../database/database/Database.cpp"
#include "../../database/entity/Entity.cpp"
#include "../../util/logger/Logger.h"
#include "../../view/database/DatabaseView.h"
#include "../ActionListener.h"

#include "../../database/dbmanager/DBManager.h"

class SelectedDatabaseActionListener: ActionListener {
public:
	SelectedDatabaseActionListener(int currentDB);
	virtual ~SelectedDatabaseActionListener();
	static void invoke(int currentDB);

private:
	DBManager* dbManager;
	Logger log;
	int currentDB;
	int currentEntity;
	DatabaseView view;
	Database<People> database;

	void listen(char action);
	void upArrowAction();
	void downArrowAction();
	void deleteEntityAction();
	void createEntityAction();
	void saveAction();
	void saveAsAction();
	void escapeAction();
	void sortByDefaultOrder();
	void sortByAge();
	void sortBySurname();
	void findBySurname();
	void openInSingleView();
};

#endif /* ACTIONLISTENER_DATABASE_SELECTEDDATABASEACTIONLISTENER_H_ */
