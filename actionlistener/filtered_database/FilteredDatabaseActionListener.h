/*
 * FilteredDatabaseActionListener.h
 *
 *  Created on: 25 sty 2015
 *      Author: admin
 */

#ifndef FILTEREDDATABASEACTIONLISTENER_H_
#define FILTEREDDATABASEACTIONLISTENER_H_

#include <vector>

#include "../../database/entity/Entity.cpp"
#include "../../util/logger/Logger.h"
#include "../../view/filtered_database/FilteredDatabaseView.h"
#include "../ActionListener.h"

class FilteredDatabaseActionListener: public ActionListener {
public:
	static void invoke(std::vector<People> rows);

private:
	FilteredDatabaseActionListener(std::vector<People> rows);
	Logger log;
	int currentEntity;
	std::vector<People> rows;
	FilteredDatabaseView view;

	void listen(char action);
	void downArrowAction();
	void upArrowAction();
	void escapeAction();
	void openInSingleView();
};

#endif /* FILTEREDDATABASEACTIONLISTENER_H_ */
