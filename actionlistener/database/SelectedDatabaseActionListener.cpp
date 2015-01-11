/*
 * SelectedDatabaseActionListener.cpp
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#include "SelectedDatabaseActionListener.h"

#include <string>
#include <vector>

#include "../../libraries/rlutil/rlutil.h"
#include "../../util/utils.h"

using namespace rlutil;

SelectedDatabaseActionListener::SelectedDatabaseActionListener(int currentDB) {
	this->currentDB = currentDB;
	this->currentEntity = 0;

	dbManager = &DBManager::getInstance();
	database = dbManager->get(currentDB);

	view.setDbName(database.getFileName());
	view.setRows(database.getRows());
	cls();
	view.showMainView();
}

SelectedDatabaseActionListener::~SelectedDatabaseActionListener() {
}

void SelectedDatabaseActionListener::invoke(int currentDB) {
	char action = 0;
	SelectedDatabaseActionListener listener(currentDB);

	do {
		action = getkey();
		listener.listen(action);
	} while (listener.isRunning());
}

void SelectedDatabaseActionListener::listen(char action) {
	switch (action) {
	case KEY_ESCAPE:
		log.print("Wybrana akcja = db.escapeAction()");
		escapeAction();
		return;

	case KEY_UP:
		log.print("Wybrana akcja = db.upArrowAction()");
		upArrowAction();
		return;

	case KEY_DOWN:
		log.print("Wybrana akcja = db.downArrowAction()");
		downArrowAction();
		return;

	case KEY_DELETE:
		log.print("Wybrana akcja = db.deleteEntityAction()");
		deleteEntityAction();
		return;
	}
}

void SelectedDatabaseActionListener::upArrowAction() {
	if (currentEntity - 1 >= 0) {
		currentEntity--;
		view.setCurrentEntity(currentEntity);
	}

	log.print("currentEntity = " + numberToString(currentEntity));
}

void SelectedDatabaseActionListener::downArrowAction() {
	if (currentEntity + 1 < database.getRowsCount()) {
		currentEntity++;
		view.setCurrentEntity(currentEntity);
	}

	log.print("currentEntity = " + numberToString(currentEntity));
}

void SelectedDatabaseActionListener::deleteEntityAction() {
	if (database.getRowsCount() == 0)
		return;

	bool confirmed = view.confirmDeleteView();

	if (confirmed) {
		database.remove(currentEntity);
		view.setRows(database.getRows());
	}

	view.showMainView();

	if (currentEntity == database.getRowsCount())
		view.setCurrentEntity(--currentEntity);
}

void SelectedDatabaseActionListener::createEntityAction() {
}

void SelectedDatabaseActionListener::saveAction() {
}

void SelectedDatabaseActionListener::saveAsAction() {
}

void SelectedDatabaseActionListener::escapeAction() {
	running = false;
}

//void SelectedDatabaseActionListener::openEntityInSingleView()
//{
//	SingleEntityActionListener::invoke(currentDB);
//	// TODO AFTER_INVOKE showDBView();
//}
