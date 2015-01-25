/*
 * FilteredDatabase.cpp
 *
 *  Created on: 25 sty 2015
 *      Author: admin
 */

#include "FilteredDatabase.h"

#include "../../libraries/rlutil/rlutil.h"
#include "../../util/colors.h"
#include "../../util/utils.h"

using namespace rlutil;

FilteredDatabase::FilteredDatabase() {
}

void FilteredDatabase::showMainView() {
	cls();
	showMainMenu();

	locate(1, 1);
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	locate(3, 5);
	printf("Wyniki wyszukiwania");
	locate(3, 7);
	printf("Rekordow: %d", (int) rows.size());

	locate(3, 9);

	if (rows.size() > 0) {
		printBorderOfEntityTable();
	} else {
		setColors(FONT_COLOR_WHITE, 0);
		printf("Nic nie znaleziono.");
		setColors(FONT_COLOR_LIGHT_GRAY, 0);
	}

	showEntityList();
}

void FilteredDatabase::showMainMenu() {
	std::vector<std::string> menuItems;
	menuItems.push_back("Powrot [Esc]");
	locate(1, 1);
	setColors(FONT_COLOR_LIGHT_GRAY, BACKGROUND_COLOR_LIGHT_BLUE);
	fillLine(' ');
	printMenu(menuItems);
	fillLine(' ');
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
}

void FilteredDatabase::printMenu(vector<string> &menu) {
	int totalChars = 0;
	int itemsCount = (int) menu.size();

	for (int i = 0; i < itemsCount; i++)
		totalChars += menu[i].size();

	int spaces = tcols() - totalChars;

	if (spaces < itemsCount) {
		printf("Console width is too short.\n");
		return;
	}

	printf("  ");
	unsigned int charsCount = 2;

	for (int i = 0, spacesBetweenItems = (spaces - 2) / itemsCount;
			i < itemsCount; i++) {
		printf("%s", menu[i].c_str());
		charsCount += menu[i].size();

		for (int j = 0; j < spacesBetweenItems; j++, charsCount++)
			putchar(' ');

	}

	while (charsCount++ < (unsigned int) tcols())
		putchar(' ');
}
