/*
 * SelectedDatabaseActionListener.cpp
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#include "SelectedDatabaseActionListener.h"

#include <vector>

#include "../../libraries/rlutil/rlutil.h"
#include "../singleentity/SingleEntityActionListener.h"

using namespace rlutil;

SelectedDatabaseActionListener::SelectedDatabaseActionListener(int currentDB) {
	this->currentDB = currentDB;
	dbManager = &DBManager::getInstance();
	database = dbManager->get(currentDB);
}

SelectedDatabaseActionListener::~SelectedDatabaseActionListener()
{
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
		escapeAction();
	}
}

void SelectedDatabaseActionListener::upArrowAction()
{
}

void SelectedDatabaseActionListener::downArrowAction()
{
}

void SelectedDatabaseActionListener::deleteEntityAction()
{
}

void SelectedDatabaseActionListener::createEntityAction()
{
}

void SelectedDatabaseActionListener::saveAction()
{
}

void SelectedDatabaseActionListener::saveAsAction()
{
}

void SelectedDatabaseActionListener::escapeAction()
{
	running = false;
}

void SelectedDatabaseActionListener::openEntityInSingleView()
{
	SingleEntityActionListener::invoke(currentDB);
	// TODO AFTER_INVOKE showDBView();
}
