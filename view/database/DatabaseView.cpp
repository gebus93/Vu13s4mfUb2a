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
	currentEntity = 0;
	lastPageRowsCount = 10;
}

void DatabaseView::showMainMenu() {
	std::vector<std::string> menuItems;
	menuItems.push_back("Dodaj [N]");
	menuItems.push_back("Zapisz [S]");
	menuItems.push_back("Zapisz jako [F2]");
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

	int rowsCount = calculateRowsCount();

	for (int i = 0, j = rowsCount; i < j; i++, row++) {
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

void DatabaseView::printEntityRow(int index, int lineNumber) {
	People personData = rows[index];
	locate(4, lineNumber);
	printf(" %2d ", (index + 1));
	locate(9, lineNumber);
	printf(" %-10s ", personData.getName().c_str());
	locate(22, lineNumber);
	printf(" %-20s ", personData.getSurname().c_str());
	locate(45, lineNumber);
	printf(" %-5d ", personData.getAge());
	locate(53, lineNumber);
	printf(" %-8d ", personData.getHeight());
	locate(64, lineNumber);
	printf(" %-5d ", personData.getWeight());
}

int DatabaseView::calculateRowsCount() {
	int index = (currentEntity / 10) * 10;
	int rowsCount = rows.size() - index;
	if (rowsCount > 10)
		rowsCount = 10;

	return rowsCount;
}

void DatabaseView::showEntityList() {
	int lineNumber = 11;

	int index = (currentEntity / 10) * 10;

	int rowsCount = calculateRowsCount();

	if (lastPageRowsCount != rowsCount) {
		int i = lastPageRowsCount > rowsCount ? rowsCount : lastPageRowsCount;

		lineNumber += i;

		for (; i <= 10; ++i) {
			locate(1, lineNumber++);
			fillLine(' ');
		}

		printBorderOfEntityTable();

		lineNumber = 11;
	}

	setColors(FONT_COLOR_GRAY, 0);
	for (int i = 0; i < rowsCount; ++i, ++index, ++lineNumber) {
		if (index == currentEntity) {
			setColors(FONT_COLOR_WHITE, 0);
			printEntityRow(index, lineNumber);
			setColors(FONT_COLOR_GRAY, 0);
		} else {
			printEntityRow(index, lineNumber);
		}
	}

	lastPageRowsCount = rowsCount;
	locate(1, 1);
}

void DatabaseView::showMainView() {
	cls();
	showMainMenu();
	showSubMenu();

	locate(1, 1);
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	locate(3, 5);
	printf("Aktualna baza: %s", dbName.c_str());
	locate(3, 7);
	printf("Rekordow: %d", (int) rows.size());

	locate(3, 9);

	if (rows.size() > 0) {
		printBorderOfEntityTable();
	} else {
		setColors(FONT_COLOR_WHITE, 0);
		printf("Nie dodano jeszcze zadnego rekordu.");
		setColors(FONT_COLOR_LIGHT_GRAY, 0);
		return;
	}

	showEntityList();
}

string DatabaseView::showSaveAsView() {
	cls();
	showMainMenu();
	showReturnSubMenu();

	return getDatabaseName();
}

bool DatabaseView::showSaveView() {
	string confirmation = "Czy chcesz zapisac wprowadzone zmiany?";
	return confirmationSubView(confirmation);
}

bool DatabaseView::showExitView() {
	string message = "Czy na pewno chcesz wyjsc z bazy danych?";

	return confirmationSubView(message);
}

bool DatabaseView::confirmDeleteView() {
	string confirmation = "Czy na pewno chcesz usunac wpis nr "
			+ numberToString(currentEntity + 1) + "?";
	return confirmationSubView(confirmation);
}

void DatabaseView::setDbName(const string& dbName) {
	this->dbName = dbName;
}

void DatabaseView::setRows(const vector<People>& rows) {
	this->rows = rows;
}

void DatabaseView::setCurrentEntity(int currentEntity) {
	this->currentEntity = currentEntity;

	if (rows.size() > 0)
		showEntityList();
}

void DatabaseView::showLabelForEntity(const char* label, const int fieldSize,
		int line) {
	locate(3, line);
	printf("%10s:", label);
}

string DatabaseView::readString(int line, const int FIELD_LENGTH) {
	locate(15, line);
	showInputFieldBackground(FIELD_LENGTH);
	locate(15, line);
	string text = inputText(FIELD_LENGTH);

	locate(15, line);
	setColors( FONT_COLOR_WHITE, 0);

	fillLine(' ', FIELD_LENGTH);
	locate(15, line);
	printStdString(text);

	return text;
}

int DatabaseView::readInt(int line, const int FIELD_LENGTH, int maxNumber) {
	locate(15, line);
	showInputFieldBackground(FIELD_LENGTH);
	locate(15, line);
	int number = inputNumber(maxNumber);

	locate(15, line);
	setColors( FONT_COLOR_WHITE, 0);

	fillLine(' ', FIELD_LENGTH);
	locate(15, line);
	printf("%d", number);

	return number;
}

string DatabaseView::showSearchView() {
	cls();
	showMainMenu();
	showReturnSubMenu();

	const int FIELD_LENGTH = 20;

	string label = "Podaj nazwisko poszukiwanej osoby: ";

	center(label.size() + FIELD_LENGTH);

	setColor(WHITE);
	printStdString(label);

	showInputFieldBackground(FIELD_LENGTH);
	for (int i = 0; i < FIELD_LENGTH; i++)
		putchar('\b');

	try {
		string personsSurname = inputText(FIELD_LENGTH);
		setColors(FONT_COLOR_LIGHT_GRAY, 0);
		return personsSurname;

	} catch (int e) {
		printError("Operacja zostala anulowana.");
		getkey();
	}

	setColors(FONT_COLOR_LIGHT_GRAY, 0);

	return "";
}

void DatabaseView::entityCreatedCorrectly() {
	cls();
	showMainMenu();
	showReturnSubMenu();

	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	string notification = "Operacja zostala zatwierdzona.";
	centerHorizontal(trows() / 2 - 1, notification.size());
	printStdString(notification);
	string message = "Encja zostala dodana do bazy danych.";
	centerHorizontal(trows() / 2 + 1, message.size());
	printStdString(message);
}

People DatabaseView::showCreateEntityView() {
	cls();
	showMainMenu();
	showReturnSubMenu();
	int line = 5;
	const int FIELD_LENGTH = 20;

	setColors( FONT_COLOR_WHITE, 0);

	showLabelForEntity("Imie", FIELD_LENGTH, line);
	showLabelForEntity("Nazwisko", FIELD_LENGTH, ++line);
	showLabelForEntity("Wiek", FIELD_LENGTH, ++line);
	showLabelForEntity("Wzost", FIELD_LENGTH, ++line);
	showLabelForEntity("Waga", FIELD_LENGTH, ++line);

	try {
		People person;
		line = 5;

		string name = readString(line, FIELD_LENGTH);
		person.setName(name);

		string surname = readString(++line, FIELD_LENGTH);
		person.setSurname(surname);

		int age = readInt(++line, FIELD_LENGTH, 150);
		person.setAge(age);

		int height = readInt(++line, FIELD_LENGTH, 250);
		person.setHeight(height);

		int weight = readInt(++line, FIELD_LENGTH, 350);
		person.setWeight(weight);

		entityCreatedCorrectly();

		return person;

	} catch (int e) {
		setColors( FONT_COLOR_WHITE, 0);
		cls();
		showMainMenu();
		showReturnSubMenu();
		printError("Operacja zostala anulowana.");
	}

	setColors(FONT_COLOR_LIGHT_GRAY, 0);

	People person;
	return person;
}
