/*
 * DatabaseView.h
 *
 *  Created on: 11 sty 2015
 *      Author: admin
 */

#ifndef DATABASEVIEW_H_
#define DATABASEVIEW_H_

#include <string>
#include <vector>

#include "../View.h"
#include "../../database/entity/Entity.cpp"

using namespace std;

class DatabaseView: View {
public:
	DatabaseView();

	void showMainView();
	bool showSaveView();
	string showSaveAsView();
	People showCreateEntityView();
	bool showExitView();

	bool confirmDeleteView();

	void setDbName(const string& dbName);

	void setRows(const vector<People>& rows);

	void setCurrentEntity(int currentEntity);

private:
	string dbName;
	vector<People> rows;
	int currentEntity;

	void showMainMenu();
	void showSubMenu();
	void printBorderOfEntityTable();
	void showLabelForEntity(const char* label, const int fieldSize, int line);
	string readString(int line, const int FIELD_LENGTH);
	int readInt(int line, const int FIELD_LENGTH, int maxNumber = 1000000);
	void entityCreatedCorrectly();
	void printEntityRow(int index, int lineNumber);
};

#endif /* DATABASEVIEW_H_ */
