/*
 * MainActionListener.cpp
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#include "MainActionListener.h"

#include <string>

#include "../../database/dbmanager/dbManager.h"
#include "../../libraries/rlutil/rlutil.h"
#include "../../util/utils.h"
#include "../database/SelectedDatabaseActionListener.h"

using namespace rlutil;

MainActionListener::MainActionListener() {
	dbManager = DBManager::getInstance();
	currentDB = 0;
	running = true;

	view.setDatabaseList(dbManager->getAll());
	view.setCurrentDb(currentDB);
	view.showMainView();
}

MainActionListener::~MainActionListener() {
	if (!dbManager)
		delete dbManager;
}

void MainActionListener::invoke() {
	char action = 0;
	MainActionListener listener;
	do {
		action = getkey();
		listener.listen(action);
	} while (listener.isRunning());
}

void MainActionListener::listen(char action) {
	switch (action) {
	case KEY_UP:
		log.print("Wybrana akcja = upArrowAction()");
		upArrowAction();
		return;

	case KEY_DOWN:
		log.print("Wybrana akcja = downArrowAction()");
		downArrowAction();
		return;

	case KEY_DELETE:
		log.print("Wybrana akcja = deleteDBAction()");
		deleteDBAction();
		return;

	case KEY_ENTER:
		log.print("Wybrana akcja = openDBAction()");
		openDBAction();
		return;

	case 's':
		log.print("Wybrana akcja = saveAction()");
		saveAction();
		return;

	case 'n':
		log.print("Wybrana akcja = createDBAction()");
		createDBAction();
		return;

	case 'q':
		log.print("Wybrana akcja = exitAction()");
		exitAction();
		return;
	}
}

void MainActionListener::upArrowAction() {
	if (currentDB - 1 >= 0) {
		currentDB--;
		view.setCurrentDb(currentDB);
	}

	log.print("currentDB = " + numberToString(currentDB));
}

void MainActionListener::downArrowAction() {
	if (currentDB + 1 < dbManager->count()) {
		currentDB++;
		view.setCurrentDb(currentDB);
	}

	log.print("currentDB = " + numberToString(currentDB));
}

void MainActionListener::deleteDBAction() {
	if (dbManager->count() == 0)
		return;

	bool confirmed = view.confirmDeleteView();
	if (confirmed) {
		dbManager->remove(currentDB);
		view.setDatabaseList(dbManager->getAll());
	}

	view.showMainView();

	if (currentDB == dbManager->count())
		view.setCurrentDb(--currentDB);
}

void MainActionListener::saveAction() {
	bool confirmed = view.showSaveView();
	if (confirmed)
		dbManager->save();

	view.showMainView();
}

void MainActionListener::createDBAction() {
	std::string dbName = view.showCreateView();
	if (dbName.length() > 0) {
		dbManager->add(dbName);
		view.setDatabaseList(dbManager->getAll());
	}
	getkey();
	view.showMainView();
}

void MainActionListener::openDBAction() {

	if (currentDB == 0 && dbManager->count() == 0)
		return;

	SelectedDatabaseActionListener::invoke(currentDB);
	view.setDatabaseList(dbManager->getAll());

	log.print("Rozmiar modyfikowanej tabeli: " + numberToString((int) dbManager->get(currentDB).getRowsCount()));

	view.showMainView();
}

void MainActionListener::exitAction() {
	bool confirmed = view.showExitView();

	if (!confirmed) {
		view.showMainView();
		return;
	}

	if (dbManager->isModified())
		saveAction();

	running = false;
}
