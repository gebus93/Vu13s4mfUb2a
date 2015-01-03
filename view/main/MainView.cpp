/*
 * MainView.cpp
 *
 *  Created on: 3 sty 2015
 *      Author: Łukasz
 */

#include "MainView.h"

#include "../../util/utils.h"

MainView::MainView()
{
	this->currentDB = 0;
}

MainView::~MainView()
{
	// TODO Auto-generated destructor stub
}

void MainView::showMainMenu()
{
	locate(1, 1);
	setColors(FONT_COLOR_LIGHT_GRAY, BACKGROUND_COLOR_LIGHT_BLUE);
	fillLine(' ');
	printMenu(getMainMenu());
	fillLine(' ');
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
}

void MainView::setCurrentDb(int currentDb) {
	this->currentDB = currentDb;

	if (!databaseList.empty())
		showDatabaseList();
}

void MainView::printBorderOfDatabasesTable()
{
	int row = 8;
	int headerBackground = 0;
	int contentBackground = 0;
	setColors( FONT_COLOR_WHITE, headerBackground);
	locate(3, row++);
	printf("| Nr | %-20s | %-15s |", "Nazwa bazy", "Ilosc rekordow");
	locate(3, row++);
	printSeparatorForThreeColumns(4, 22, 17);
	setColors( FONT_COLOR_WHITE, contentBackground);
	for (int i = 0, j = databaseList.size(); i < j; i++, row++) {
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

void MainView::showDatabaseList()
{
	setColors(FONT_COLOR_GRAY, 0);
	int lineNumber = 10;
	for (int index = 0, databaseSize = databaseList.size(); index < databaseSize; index++, lineNumber++) {
		if (index == currentDB) {
			setColors(FONT_COLOR_WHITE, 0);
			printRowWithDatabase(lineNumber, index);
			setColors(FONT_COLOR_GRAY, 0);
		} else {
			printRowWithDatabase(lineNumber, index);
		}
	}

	pressEnterToAccept(lineNumber);
}

void MainView::showMainView()
{
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

void MainView::showCreateView()
{
}

void MainView::showSaveView()
{
}

void MainView::showExitView()
{
}

void MainView::confirmDeleteView()
{
}

std::vector<std::string> MainView::getMainMenu()
{
	std::vector<std::string> mainMenu;
	mainMenu.push_back("Nowa baza [N]");
	mainMenu.push_back("Zapisz [S]");
	mainMenu.push_back("Usun [Del]");
	mainMenu.push_back("Wyjscie [Q]");
	return mainMenu;
}

void MainView::setDatabaseList(const std::vector<Database<People> >& databaseList) {
	this->databaseList = databaseList;
}
