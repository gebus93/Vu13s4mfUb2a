/*
 * DatabaseView.cpp
 *
 *  Created on: 11 sty 2015
 *      Author: admin
 */

#include "DatabaseView.h"

#include <cstdio>

#include "../../libraries/rlutil/rlutil.h"
#include "../../util/colors.h"
#include "../../util/utils.h"

DatabaseView::DatabaseView() {
	// TODO Auto-generated constructor stub

}

void DatabaseView::showMainMenu() {
	std::vector<std::string> menuItems;
	menuItems.push_back("Dodaj [N]");
	menuItems.push_back("Edytuj [Enter]");
	menuItems.push_back("Usun [Del]");
	menuItems.push_back("Powrot [Esc]");
	locate(1, 1);
	setColors(FONT_COLOR_LIGHT_GRAY, BACKGROUND_COLOR_LIGHT_BLUE);
	fillLine(' ');
	printMenu(menuItems);
	fillLine(' ');
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
}

void DatabaseView::showSubMenu() {
	std::vector<std::string> menuItems;
	menuItems.push_back(
			"Sortuj: domyslnie [1] wg wieku [2] wg nazwiska [3] | Wyszukaj po nazwisku [4]");
	locate(1, trows());
	setColors(FONT_COLOR_WHITE, BACKGROUND_COLOR_GRAY);
	printMenu(menuItems);
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	locate(1, 1);
}

void DatabaseView::printBorderOfEntityTable() {
	//			printBorderOfEntityTable();
	int row = 9;
	int headerBackground = 0;
	int contentBackground = 0;
	setColors( FONT_COLOR_WHITE, headerBackground);
	locate(3, row++);
	printf("| ID | %-10s | %-20s | %-5s | %-8s | %-5s |", "Imie", "Nazwisko",
			"Wiek", "Wzrost", "Waga");
	locate(3, row++);
	printSeparator(6, 4, 12, 22, 7, 10, 7);
	setColors( FONT_COLOR_WHITE, contentBackground);
	for (int i = 0, j = rows.size(); i < j; i++, row++) {
		locate(3, row);
		printf("| %2s | %10s | %20s | %5s | %8s | %5s |", "", "", "", "", "",
				"");
	}
	locate(3, row);
	printSeparator(6, 4, 12, 22, 7, 10, 7);
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	locate(3, row + 1);
	fillLine(' ');
}

void DatabaseView::showMainView() {
	showMainMenu();
	showSubMenu();

	locate(1, 1);

	// TODO: Sortowanie -> modyfikacja

	// TODO: Wyszukiwanie -> nie modyfikacja

	// TODO: Edycja -> jezeli zatwierdzono to modyfikacja

	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	locate(3, 5);
	printf("Aktualna baza: %s", dbName.c_str());
	locate(3, 7);
	printf("Rekordow: %d", rows.size());

	locate(3, 9);

	if (rows.size() > 0) {
		printBorderOfEntityTable();
	} else {
		setColors(FONT_COLOR_WHITE, 0);
		printf("Nie dodano jeszcze zadnego rekordu.");
		setColors(FONT_COLOR_LIGHT_GRAY, 0);
	}
}

bool DatabaseView::showSaveAsView() {
	return true;
}

bool DatabaseView::showExitView() {
	return true;
}

bool DatabaseView::confirmDeleteView() {
	return false;
}

void DatabaseView::setDbName(const string& dbName) {
	this->dbName = dbName;
}

void DatabaseView::setRows(const vector<People>& rows) {
	this->rows = rows;
}

void DatabaseView::setCurrentEntity(int currentEntity) {
	this->currentEntity = currentEntity;
}
