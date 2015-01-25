/*
 * FilteredDatabaseActionListener.cpp
 *
 *  Created on: 25 sty 2015
 *      Author: admin
 */

#include "FilteredDatabaseActionListener.h"

#include <string>

#include "../../libraries/rlutil/rlutil.h"
#include "../../util/utils.h"
#include "../single_entity/SingleEntityActionListener.h"

using namespace rlutil;

void FilteredDatabaseActionListener::invoke(std::vector<People> rows) {
	char action = 0;
	FilteredDatabaseActionListener listener(rows);

	do {
		action = getkey();
		listener.listen(action);
	} while (listener.isRunning());
}

FilteredDatabaseActionListener::FilteredDatabaseActionListener(
		std::vector<People> rows) {
	running = true;
	currentEntity = 0;
	this->rows = rows;

	view.setCurrentEntity(currentEntity);
	view.setRows(rows);
	view.showMainView();

}

void FilteredDatabaseActionListener::downArrowAction() {
	if (currentEntity + 1 < (int) rows.size()) {
		currentEntity++;
		view.setCurrentEntity(currentEntity);
	}

	log.print("currentEntity = " + numberToString(currentEntity));
}

void FilteredDatabaseActionListener::upArrowAction() {
	if (currentEntity - 1 >= 0) {
		currentEntity--;
		view.setCurrentEntity(currentEntity);
	}

	log.print("currentEntity = " + numberToString(currentEntity));
}

void FilteredDatabaseActionListener::escapeAction() {
	running = false;
}

void FilteredDatabaseActionListener::openInSingleView() {
	SingleEntityActionListener::invoke(rows, currentEntity);
	view.showMainView();
}

void FilteredDatabaseActionListener::listen(char action) {
	switch (action) {
	case KEY_ESCAPE:
		log.print("Wybrana akcja = filteredDB.escapeAction()");
		escapeAction();
		return;

	case KEY_ENTER:
		log.print("Wybrana akcja = filteredDB.openInSingleView()");
		openInSingleView();
		return;

	case KEY_UP:
		log.print("Wybrana akcja = filteredDB.upArrowAction()");
		upArrowAction();
		return;

	case KEY_DOWN:
		log.print("Wybrana akcja = filteredDB.downArrowAction()");
		downArrowAction();
		return;
	}
}
