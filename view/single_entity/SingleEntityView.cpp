/*
 * SingleEntityView.cpp
 *
 *  Created on: 25 sty 2015
 *      Author: admin
 */

#include "SingleEntityView.h"

#include "../../libraries/rlutil/rlutil.h"
#include "../../util/colors.h"
#include "../../util/utils.h"

#include <vector>

SingleEntityView::SingleEntityView() {
	currentEntity = 0;
}

void SingleEntityView::printLabelAndStringValue(int line, const char* label,const std::string& value) {
	locate(3, line);
	printf("%10s: %s", label, value.c_str());
}

void SingleEntityView::printLabelAndIntValue(int line, const char* label,
		int value) {
	locate(3, line);
	printf("%10s: %d", label, value);
}

void SingleEntityView::showMainView() {
	cls();
	showMainMenu();
	showSubMenu();

	locate(3, 5);
	printf("Osoba %d z %d", (currentEntity + 1), rows.size());

	int line = 7;

	printLabelAndStringValue(line, "Imie", rows[currentEntity].getName());
	printLabelAndStringValue(++line, "Nazwisko",rows[currentEntity].getSurname());
	printLabelAndIntValue(++line, "Wiek", rows[currentEntity].getAge());
	printLabelAndIntValue(++line, "Wzrost", rows[currentEntity].getHeight());
	printLabelAndIntValue(++line, "Waga", rows[currentEntity].getWeight());
}

void SingleEntityView::setRows(const vector<People>& rows) {
	this->rows = rows;
}

void SingleEntityView::setCurrentEntity(int currentEntity) {
	this->currentEntity = currentEntity;
	showMainView();
}

void SingleEntityView::showMainMenu() {
	std::vector<std::string> menuItems;
	menuItems.push_back("Powrot [Esc]");
	locate(1, 1);
	setColors(FONT_COLOR_LIGHT_GRAY, BACKGROUND_COLOR_LIGHT_BLUE);
	fillLine(' ');
	printMenu(menuItems);
	fillLine(' ');
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
}

void SingleEntityView::showSubMenu() {
	std::vector<std::string> menuItems;
	menuItems.push_back("Poprzedni [Strzalka w lewo]");
	menuItems.push_back("Nastepny [Strzalka w prawo]");
	locate(1, trows());
	setColors(FONT_COLOR_WHITE, BACKGROUND_COLOR_GRAY);
	printMenu(menuItems);
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	locate(1, 1);
}
