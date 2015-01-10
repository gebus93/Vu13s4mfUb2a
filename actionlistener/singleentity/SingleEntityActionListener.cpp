/*
 * SingleEntityActionListener.cpp
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#include "SingleEntityActionListener.h"

#include "../../database/dbmanager/DBManager.h"
#include "../../libraries/rlutil/rlutil.h"
#include "../../util/utils.h"

using namespace rlutil;

SingleEntityActionListener::SingleEntityActionListener(int currentDB) {
	dbManager = &DBManager::getInstance();
	this->database = database;
	this->currentDB = currentDB;

}

SingleEntityActionListener::~SingleEntityActionListener()
{
	// TODO Auto-generated destructor stub
}

void SingleEntityActionListener::invoke(int currentDB) {
	// TODO Zaprzyjaźnic z klasą SelectedDatabaseActionListener aby uzyskac dostęp do bazy danych;
	char action = 0;
	SingleEntityActionListener listener(currentDB);
	do {
		action = getkey();
		listener.listen(action);
	} while (listener.isRunning());
}

void SingleEntityActionListener::listen(char action) {
}

void SingleEntityActionListener::leftArrowAction()
{
}

void SingleEntityActionListener::rightArrowAction()
{
}

void SingleEntityActionListener::entityEntityAction()
{
}

void SingleEntityActionListener::escapeAction()
{
}
