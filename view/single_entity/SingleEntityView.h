/*
 * SingleEntityView.h
 *
 *  Created on: 25 sty 2015
 *      Author: admin
 */

#ifndef SINGLEENTITYVIEW_H_
#define SINGLEENTITYVIEW_H_

#include <vector>

#include "../../database/entity/Entity.cpp"
#include "../View.h"

class SingleEntityView: public View {
public:
	SingleEntityView();

	void showMainView();

	void setRows(const vector<People>& rows);

	void setCurrentEntity(int currentEntity);

private:
	vector<People> rows;
	int currentEntity;
	void showMainMenu();
};

#endif /* SINGLEENTITYVIEW_H_ */
