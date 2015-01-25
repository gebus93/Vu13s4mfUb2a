/*
 * MainView.cpp
 *
 *  Created on: 3 sty 2015
 *      Author: Łukasz
 */

#include "MainView.h"

#include <cstdio>

#include "../../libraries/rlutil/rlutil.h"
#include "../../util/colors.h"
#include "../../util/utils.h"

/*
 * Views
 */

void MainView::showMainView() {
	cls();
	showMainMenu();

	locate(3, 5);
	printf("Lista baz danych:");

	if (databaseList.empty()) {
		locate(5, 7);
		printf("> Nie dodano jeszcze zadnej bazy danych.");
		return;
	}

	setColors(FONT_COLOR_LIGHT_GRAY, 0);

	printBorderOfDatabasesTable();
	showDatabaseList();
}

string MainView::showCreateView() {
	cls();
	showMainMenu();
	showReturnSubMenu();

	return getDatabaseName();

}

bool MainView::showSaveView() {
	string confirmation = "Czy chcesz zapisac wprowadzone zmiany?";
	return confirmationSubView(confirmation);
}

bool MainView::showExitView() {
	string message = "Czy na pewno chcesz wyjsc z programu?";

	return confirmationSubView(message);
}

bool MainView::confirmDeleteView() {
	Database<People> currentDb = databaseList[currentDB];
	string confirmation = "Czy na pewno chcesz usunac baze '" + currentDb.getFileName() + "' wraz z danymi?";
	bool confirmed = confirmationSubView(confirmation);
	return confirmed;
}

/*
 * Others
 */

MainView::MainView() {
	this->currentDB = 0;
	lastPageCount = 0;
}

MainView::~MainView() {
}

void MainView::showMainMenu() {
	std::vector<std::string> menuItems;
	menuItems.push_back("Nowa baza [N]");
	menuItems.push_back("Zapisz [S]");
	// FIXME to nie działa
	menuItems.push_back("Usun [Del]");
	menuItems.push_back("Wyjscie [Q]");

	locate(1, 1);
	setColors(FONT_COLOR_LIGHT_GRAY, BACKGROUND_COLOR_LIGHT_BLUE);
	fillLine(' ');
	printMenu(menuItems);
	fillLine(' ');
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
}

void MainView::setCurrentDb(int currentDb) {
	this->currentDB = currentDb;

	if (!databaseList.empty())
		showDatabaseList();
}

void MainView::printBorderOfDatabasesTable() {
	int row = 8;
	int headerBackground = 0;
	int contentBackground = 0;
	setColors(FONT_COLOR_WHITE, headerBackground);
	locate(3, row++);
	printf("| Nr | %-20s | %-15s |", "Nazwa bazy", "Ilosc rekordow");
	locate(3, row++);
	printSeparatorForThreeColumns(4, 22, 17);
	setColors(FONT_COLOR_WHITE, contentBackground);

	int rowsCount = calculateRowsCount();

	for (int i = 0, j = rowsCount; i < j; i++, row++) {
		locate(3, row);
		Database<People> currentDatabase = databaseList[i];
		printf("| %2s | %20s | %15s |", "", "", "");
	}
	locate(3, row);
	printSeparatorForThreeColumns(4, 22, 17);
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	locate(3, row + 1);
	fillLine(' ');
}

void MainView::pressEnterToAccept(int lineNumber) {
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	if (lineNumber > (int) (((trows() - 3))))
		lineNumber += 2;
	else
		lineNumber = trows() - 2;

	string message = "Aby zatwierdzic wybor, kliknij Enter.";
	centerHorizontal(lineNumber, message.size());
	printf(message.c_str());
}

void MainView::printRowWithDatabase(int lineNumber, int index) {
	locate(4, lineNumber);
	Database<People> currentDatabase = databaseList[index];
	printf(" %2d ", (index + 1));
	locate(9, lineNumber);
	printf(" %-20s ", currentDatabase.getFileName().c_str());
	locate(32, lineNumber);
	printf(" %-15d ", currentDatabase.getRowsCount());

}

int MainView::calculateRowsCount()
{
	int index = (currentDB / 10) * 10;
	int rowsCount = databaseList.size() - index;
	if (rowsCount > 10)
		rowsCount = 10;

	return rowsCount;
}

void MainView::showDatabaseList() {
	int lineNumber = 10;

	int index = (currentDB / 10) * 10;
	int rowsCount = calculateRowsCount();

	if (lastPageCount != rowsCount) {
		int i = lastPageCount > rowsCount ? rowsCount : lastPageCount;

		lineNumber += i;

		for (; i <= 10; ++i) {
			locate(1, lineNumber++);
			fillLine(' ');
		}

		printBorderOfDatabasesTable();

		lineNumber = 10;
	}

	setColors(FONT_COLOR_GRAY, 0);
	for (int i = 0; i < rowsCount; ++i, ++index, ++lineNumber) {
		if (index == currentDB) {
			setColors(FONT_COLOR_WHITE, 0);
			printRowWithDatabase(lineNumber, index);
			setColors(FONT_COLOR_GRAY, 0);
		} else {
			printRowWithDatabase(lineNumber, index);
		}
	}

	pressEnterToAccept(lineNumber);
	lastPageCount = rowsCount;
}

void MainView::setDatabaseList(
		const std::vector<Database<People> >& databaseList) {
	this->databaseList = databaseList;
}

