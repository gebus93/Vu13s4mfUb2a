/*
 * SingleEntityActionListener.cpp
 *
 *  Created on: 25 sty 2015
 *      Author: admin
 */

#include "SingleEntityActionListener.h"

void SingleEntityActionListener::invoke(std::vector<People> rows) {
	if (rows.size() == 0)
		return;

	char action = 0;
	FilteredDatabaseActionListener listener(rows);

	do {
		action = getkey();
		listener.listen(action);
	} while (listener.isRunning());
}

SingleEntityActionListener::SingleEntityActionListener(std::vector<People> rows, int currentEntity) {
	running = true;
	this->currentEntity = currentEntity;
	this->rows = rows;

	view.setRows(rows);
	view.setCurrentEntity(currentEntity);
	view.showMainView();
}

SingleEntityActionListener::SingleEntityActionListener(std::vector<People> rows) {
	running = true;
	currentEntity = 0;
	this->rows = rows;

	view.setRows(rows);
	view.showMainView();
}

void SingleEntityActionListener::listen(char action) {
	switch (action) {
	case KEY_ESCAPE:
		log.print("Wybrana akcja = singleEntity.escapeAction()");
		escapeAction();
		return;

	case KEY_LEFT:
		log.print("Wybrana akcja = singleEntity.leftArrowAction()");
		leftArrowAction();
		return;

	case KEY_RIGHT:
		log.print("Wybrana akcja = singleEntity.rightArrowAction()");
		rightArrowAction();
		return;
	}
}

void SingleEntityActionListener::leftArrowAction() {
	if (currentEntity - 1 >= 0) {
		currentEntity--;
		view.setCurrentEntity(currentEntity);
	}

	log.print("currentEntity = " + numberToString(currentEntity));
}

void SingleEntityActionListener::rightArrowAction() {
	if (currentEntity + 1 < (int) rows.size()) {
		currentEntity++;
		view.setCurrentEntity(currentEntity);
	}

	log.print("currentEntity = " + numberToString(currentEntity));
}

void SingleEntityActionListener::escapeAction() {
	running = false;
}
