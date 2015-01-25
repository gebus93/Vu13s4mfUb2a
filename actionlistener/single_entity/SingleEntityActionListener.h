/*
 * SingleEntityActionListener.h
 *
 *  Created on: 25 sty 2015
 *      Author: admin
 */

#ifndef SINGLEENTITYACTIONLISTENER_H_
#define SINGLEENTITYACTIONLISTENER_H_

#include <vector>

#include "../../database/entity/Entity.cpp"
#include "../../util/logger/Logger.h"
#include "../../view/single_entity/SingleEntityView.h"
#include "../ActionListener.h"

class SingleEntityActionListener: public ActionListener {
public:
	static void invoke(std::vector<People> rows);

private:
	SingleEntityActionListener(std::vector<People> rows);
	SingleEntityActionListener(std::vector<People> rows, int currentEntity);
	Logger log;
	int currentEntity;
	std::vector<People> rows;
	SingleEntityView view;

	void listen(char action);
	void leftArrowAction();
	void rightArrowAction();
	void escapeAction();
};

#endif /* SINGLEENTITYACTIONLISTENER_H_ */
