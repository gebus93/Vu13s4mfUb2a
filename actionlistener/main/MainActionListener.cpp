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
	log.print("Wybrana akcja = " + numberToString(action));

	switch (action) {
	case KEY_UP:
		upArrowAction();
		return;

	case KEY_DOWN:
		downArrowAction();
		return;

	case KEY_DELETE:
		deleteDBAction();

	case KEY_ENTER:
		deleteDBAction();

	case 's':
		saveAction();
		return;

	case 'n':
		createDBAction();
		return;

	case 'q':
		exitAction();
		return;
	}
}

void MainActionListener::upArrowAction()
{
}

void MainActionListener::downArrowAction()
{
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
