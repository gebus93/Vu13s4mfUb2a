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
	void showCreateView();
	void showSaveView();
	void showExitView();

	void confirmDeleteView();

	void setDatabaseList(const std::vector<Database<People> >& databaseList);

	void setCurrentDb(int currentDb);

private:
	int currentDB;
	std::vector<std::string> getMainMenu();
	std::vector<Database<People> > databaseList;
	void showMainMenu();
	void printBorderOfDatabasesTable();
	void pressEnterToAccept(int lineNumber);
	void printRowWithDatabase(int lineNumber, int index);
	void showDatabaseList();
};

#endif /* VIEW_MAIN_MAINVIEW_H_ */
