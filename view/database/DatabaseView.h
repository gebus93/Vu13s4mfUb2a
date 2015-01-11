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
	bool showSaveAsView();
	bool showExitView();

	bool confirmDeleteView();

	void setDbName(const string& dbName);

	void setRows(const vector<People>& rows);

private:
	string dbName;
	vector<People> rows;
};

#endif /* DATABASEVIEW_H_ */
