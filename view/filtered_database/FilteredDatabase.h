/*
 * FilteredDatabase.h
 *
 *  Created on: 25 sty 2015
 *      Author: admin
 */

#ifndef FILTEREDDATABASE_H_
#define FILTEREDDATABASE_H_

#include "../database/DatabaseView.h"

class FilteredDatabase: public DatabaseView {
public:
	FilteredDatabase();
	void showMainView();

protected:
	void showMainMenu();
	void printMenu(vector<string> &menu);
};

#endif /* FILTEREDDATABASE_H_ */
