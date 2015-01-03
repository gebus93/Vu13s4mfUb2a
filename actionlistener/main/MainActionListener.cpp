/*
 * MainActionListener.cpp
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#include "MainActionListener.h"

#include <string>

#include "../../libraries/rlutil/rlutil.h"
#include "../../util/utils.h"
#include "../database/SelectedDatabaseActionListener.h"

using namespace rlutil;

MainActionListener::MainActionListener()
{
	dbManager = &DBManager::getInstance();
	currentDB = 0;
	running = true;

	view.setDatabaseList(dbManager->getAll());
	view.showMainView();
}

MainActionListener::~MainActionListener()
{
}

void MainActionListener::invoke()
{
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

void MainActionListener::upArrowAction()
{
	if (currentDB - 1 >= 0) {
		currentDB--;
		view.setCurrentDb(currentDB);
	}

	log.print("currentDB = " + numberToString(currentDB));
}

void MainActionListener::downArrowAction()
{
	if (currentDB + 1 < dbManager->count()) {
		currentDB++;
		view.setCurrentDb(currentDB);
	}

	log.print("currentDB = " + numberToString(currentDB));
}

void MainActionListener::deleteDBAction()
{
}

void MainActionListener::saveAction()
{
}

void MainActionListener::createDBAction()
{
}

void MainActionListener::openDBAction()
{
	SelectedDatabaseActionListener::invoke();
// TODO AFTER_INVOKE showMainView();
}

void MainActionListener::exitAction()
{
	// TODO showConfirmationView();
	running = false;
}

bool MainActionListener::isRunning() const
{
	return running;
}
