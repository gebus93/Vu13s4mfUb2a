/*
 * MainView.h
 *
 *  Created on: 3 sty 2015
 *      Author: Łukasz
 */

#ifndef VIEW_MAIN_MAINVIEW_H_
#define VIEW_MAIN_MAINVIEW_H_

#include <string>
#include <vector>

#include "../../database/database/Database.cpp"
#include "../../database/entity/Entity.cpp"
#include "../View.h"

class MainView: View {
public:
	MainView();
	virtual ~MainView();
	void showMainView();
	string showCreateView();
	void showSaveView();
	void showExitView();

	bool confirmDeleteView();

	void setDatabaseList(const std::vector<Database<People> >& databaseList);

	void setCurrentDb(int currentDb);

private:
	int currentDB;
	std::vector<Database<People> > databaseList;
	void showMainMenu();
	void printBorderOfDatabasesTable();
	void pressEnterToAccept(int lineNumber);
	void printRowWithDatabase(int lineNumber, int index);
	void showDatabaseList();
	void showReturnSubMenu();
	void showInputFieldBackground(const int FIELD_LENGTH);
	bool confirmationSubView(const string& confirmation);
};

#endif /* VIEW_MAIN_MAINVIEW_H_ */
