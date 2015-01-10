/*
 * SingleEntityActionListener.h
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#ifndef ACTIONLISTENER_SINGLEENTITY_SINGLEENTITYACTIONLISTENER_H_
#define ACTIONLISTENER_SINGLEENTITY_SINGLEENTITYACTIONLISTENER_H_

#include "../../database/database/Database.cpp"
#include "../../database/entity/Entity.cpp"
#include "../../util/logger/Logger.h"
#include "../ActionListener.h"

class DBManager;

class SingleEntityActionListener: ActionListener {
public:
	SingleEntityActionListener(int currentDB);
	virtual ~SingleEntityActionListener();
	static void invoke(int currentDB);

private:
	DBManager* dbManager;
	Logger log;
	Database<People> database;
	int currentDB;

	void listen(char action);
	void leftArrowAction();
	void rightArrowAction();
	void entityEntityAction();
	void escapeAction();
};

#endif /* ACTIONLISTENER_SINGLEENTITY_SINGLEENTITYACTIONLISTENER_H_ */
