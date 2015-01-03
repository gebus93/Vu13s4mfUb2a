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

void MainView::showMainView()
{
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

string MainView::showCreateView()
{
	cls();
	showMainMenu();
	showReturnSubMenu();

	// -----------------------------

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

bool MainView::showSaveView()
{
	string confirmation = "Czy chcesz zapisac wprowadzone zmiany?";
	return confirmationSubView(confirmation);
}

bool MainView::showExitView()
{
	string message = "Czy na pewno chcesz wyjsc z programu?";

	return confirmationSubView(message);
}
bool MainView::confirmationSubView(const string& confirmation) {
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

bool MainView::confirmDeleteView()
{
	Database<People> currentDb = databaseList[currentDB];
	string confirmation = "Czy na pewno chcesz usunac baze '" + currentDb.getFileName() + "' wraz z danymi?";
	bool confirmed = confirmationSubView(confirmation);
	return confirmed;
}

/*
 * Others
 */

MainView::MainView()
{
	this->currentDB = 0;
}

MainView::~MainView()
{
}

void MainView::showMainMenu()
{
	std::vector<std::string> menuItems;
	menuItems.push_back("Nowa baza [N]");
	menuItems.push_back("Zapisz [S]");
	menuItems.push_back("Usun [Del]");
	menuItems.push_back("Wyjscie [Q]");

	locate(1, 1);
	setColors(FONT_COLOR_LIGHT_GRAY, BACKGROUND_COLOR_LIGHT_BLUE);
	fillLine(' ');
	printMenu(menuItems);
	fillLine(' ');
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
}

void MainView::showReturnSubMenu()
{
	std::vector<std::string> menuItems;
	menuItems.push_back("Powrot [Esc]");

	locate(1, trows());
	setColors(FONT_COLOR_WHITE, BACKGROUND_COLOR_GRAY);
	printMenu(menuItems);
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
	locate(1, 1);
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
	setColors(FONT_COLOR_WHITE, headerBackground);
	locate(3, row++);
	printf("| Nr | %-20s | %-15s |", "Nazwa bazy", "Ilosc rekordow");
	locate(3, row++);
	printSeparatorForThreeColumns(4, 22, 17);
	setColors(FONT_COLOR_WHITE, contentBackground);
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

void MainView::setDatabaseList(const std::vector<Database<People> >& databaseList) {
	this->databaseList = databaseList;
}

void MainView::showInputFieldBackground(const int FIELD_LENGTH)
		{
	string field = "";
	field.insert(field.end(), FIELD_LENGTH, ' ');
	setColors( FONT_COLOR_WHITE, BACKGROUND_COLOR_GRAY);
	printStdString(field);
}

