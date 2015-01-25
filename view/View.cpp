/*
 * View.cpp
 *
 *  Created on: 3 sty 2015
 *      Author: Łukasz
 */

#include "View.h"

#include "../util/colors.h"
#include "../util/utils.h"

View::View() {
	rlutil::hidecursor();
}

View::~View() {
}

void View::printMenu(vector<string> &menu) {
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

void View::printButton(const char* label, bool confirmed) {
	if (confirmed == true)
		setColors(FONT_COLOR_WHITE, BACKGROUND_COLOR_LIGHT_BLUE);
	else
		setColors(FONT_COLOR_LIGHT_GRAY, 0);

	printf(label);
}

bool View::confirmationSubView(const string& confirmation) {
	setColors(FONT_COLOR_WHITE, 0);
	locate(1, 4);
	for (int i = 4, j = trows(); i < j; i++)
		fillLine(' ');
	locate(1, 1);
	unsigned int verticalPosition = trows() / 2;
	centerHorizontal(verticalPosition, confirmation.size());
	printf(confirmation.c_str());
	char actionKey = 0;
	bool confirmed = true;
	do {

		centerHorizontal(verticalPosition + 2, 11);

		printButton(" TAK ", confirmed);
		setColors(FONT_COLOR_LIGHT_GRAY, 0);
		putchar(' ');

		printButton(" NIE ", !confirmed);

		actionKey = getkey();

		if (actionKey == KEY_LEFT)
			confirmed = true;
		else if (actionKey == KEY_RIGHT)
			confirmed = false;

	} while (actionKey != KEY_ENTER);
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	locate(1, 4);
	for (int i = 4, j = trows(); i < j; i++)
		fillLine(' ');
	locate(1, 1);
	return confirmed;
}

string View::getDatabaseName() {
	const int FIELD_LENGTH = 20;

	string label = "Podaj nazwe bazy: ";

	center(label.size() + FIELD_LENGTH);

	setColor(WHITE);
	printStdString(label);

	showInputFieldBackground(FIELD_LENGTH);
	for (int i = 0; i < FIELD_LENGTH; i++)
		putchar('\b');

	try {
		string dbName = inputText(FIELD_LENGTH);

		setColors(FONT_COLOR_LIGHT_GRAY, 0);
		string notification = "Operacja zostala zatwierdzona.";

		locate(1, trows() / 2);
		fillLine(' ');

		centerHorizontal(trows() / 2 - 1, notification.size());
		printStdString(notification);
		putchar('\n');

		string message = "Utworzono baze danych o nazwie '" + dbName + "'.";

		centerHorizontal(trows() / 2 + 1, message.size());
		printStdString(message);

		return dbName;

	} catch (int e) {
		printError("Operacja zostala anulowana.");
	}

	setColors(FONT_COLOR_LIGHT_GRAY, 0);

	return "";
}

void View::showInputFieldBackground(const int FIELD_LENGTH) {
	string field = "";
	field.insert(field.end(), FIELD_LENGTH, ' ');
	setColors( FONT_COLOR_WHITE, BACKGROUND_COLOR_GRAY);
	printStdString(field);
}

void View::showReturnSubMenu() {
	std::vector<std::string> menuItems;
	menuItems.push_back("Powrot [Esc]");

	locate(1, trows());
	setColors(FONT_COLOR_WHITE, BACKGROUND_COLOR_GRAY);
	printMenu(menuItems);
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	locate(1, 1);
}
