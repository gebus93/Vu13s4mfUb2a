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
	log = &Logger::getInstance();
	this->currentDB = currentDB;
	this->currentEntity = 0;

	dbManager = &DBManager::getInstance();
	database = dbManager->get(currentDB);

	view.setDbName(database.getFileName());
	view.setRows(database.getRows());
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
		log->print("Wybrana akcja = db.escapeAction()");
		escapeAction();
		return;

	case KEY_UP:
		log->print("Wybrana akcja = db.upArrowAction()");
		upArrowAction();
		return;

	case KEY_DOWN:
		log->print("Wybrana akcja = db.downArrowAction()");
		downArrowAction();
		return;

	case KEY_DELETE:
		log->print("Wybrana akcja = db.deleteEntityAction()");
		deleteEntityAction();
		return;

	case 'n':
		log->print("Wybrana akcja = db.createEntityAction()");
		createEntityAction();
		return;

	case 's':
		log->print("Wybrana akcja = db.saveAction()");
		saveAction();
		return;

	case KEY_F2:
		log->print("Wybrana akcja = db.saveAsAction()");
		saveAsAction();
		return;
	}
}

void SelectedDatabaseActionListener::upArrowAction() {
	if (currentEntity - 1 >= 0) {
		currentEntity--;
		view.setCurrentEntity(currentEntity);
	}

	log->print("currentEntity = " + numberToString(currentEntity));
}

void SelectedDatabaseActionListener::downArrowAction() {
	if (currentEntity + 1 < database.getRowsCount()) {
		currentEntity++;
		view.setCurrentEntity(currentEntity);
	}

	log->print("currentEntity = " + numberToString(currentEntity));
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
	People person = view.showCreateEntityView();

	if (!person.isEmpty())
	{
		database.addRow(person);

		view.setRows(database.getRows());

		log->print("Encja nie jest pusta");
		log->print("Aktualny rozmiar bazy danych: " + numberToString(database.getRowsCount()));
	}
	else
		log->print("Encja jest pusta");

	view.showMainView();

}

void SelectedDatabaseActionListener::saveAction() {
	bool confirmed = view.showSaveView();
	if (confirmed) {
		dbManager->update(currentDB, database);
		database.setModified(false);
		dbManager->save();
	}

	view.showMainView();
}

void SelectedDatabaseActionListener::saveAsAction() {
	string dbName = view.showSaveAsView();
	if (dbName.length() > 0) {
		database.setFileName(dbName);
		dbManager->add(database);
		dbManager->save();
		database.setModified(false);
		view.setDbName(dbName);

		currentDB = dbManager->count() - 1;
	}
	getkey();
	view.showMainView();
}

void SelectedDatabaseActionListener::escapeAction() {
	bool confirmed = view.showExitView();

	if (!confirmed) {
		view.showMainView();
		return;
	}

	if (database.isModified() && view.showSaveView()) {
		dbManager->update(currentDB, database);
		database.setModified(false);
		dbManager->save();
	}

	running = false;
}
