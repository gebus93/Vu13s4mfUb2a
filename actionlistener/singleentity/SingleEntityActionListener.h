/*
 * SingleEntityActionListener.h
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#ifndef ACTIONLISTENER_SINGLEENTITY_SINGLEENTITYACTIONLISTENER_H_
#define ACTIONLISTENER_SINGLEENTITY_SINGLEENTITYACTIONLISTENER_H_

#include "../../util/logger/Logger.h"
#include "../../database/dbmanager/DBManager.h"

class SingleEntityActionListener {
public:
	SingleEntityActionListener(int currentDB);
	virtual ~SingleEntityActionListener();
	static void invoke();

private:
	DBManager* dbManager;
	Logger log;
	int currentDB;

	void listen(char action);
	void leftArrowAction();
	void rightArrowAction();
	void entityEntityAction();
	void escapeAction();
};

#endif /* ACTIONLISTENER_SINGLEENTITY_SINGLEENTITYACTIONLISTENER_H_ */
