/*
 * SelectedDatabaseActionListener.h
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#ifndef ACTIONLISTENER_DATABASE_SELECTEDDATABASEACTIONLISTENER_H_
#define ACTIONLISTENER_DATABASE_SELECTEDDATABASEACTIONLISTENER_H_

#include "../../database/dbmanager/DBManager.h"
#include "../../util/logger/Logger.h"

class DBManager;

class SelectedDatabaseActionListener {
public:
	SelectedDatabaseActionListener(int currentDB);
	virtual ~SelectedDatabaseActionListener();
	static void invoke();

private:
	DBManager* dbManager;
	Logger log;
	int currentDB;

	void listen(char action);
	void upArrowAction();
	void downArrowAction();
	void deleteEntityAction();
	void createEntityAction();
	void saveAction();
	void saveAsAction();
	void escapeAction();
	void openEntityInSingleView();
};

#endif /* ACTIONLISTENER_DATABASE_SELECTEDDATABASEACTIONLISTENER_H_ */
