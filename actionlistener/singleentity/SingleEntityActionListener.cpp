/*
 * SingleEntityActionListener.cpp
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#include "SingleEntityActionListener.h"

SingleEntityActionListener::SingleEntityActionListener(int currentDB) {
	this->currentDB = currentDB;
	dbManager = &DBManager::getInstance();

}

SingleEntityActionListener::~SingleEntityActionListener()
{
	// TODO Auto-generated destructor stub
}

void SingleEntityActionListener::invoke()
{
}

void SingleEntityActionListener::listen(char action)
		{
}

void SingleEntityActionListener::leftArrowAction()
{
}

void SingleEntityActionListener::rightArrowAction()
{
}

void SingleEntityActionListener::entityEntityAction()
{
}

void SingleEntityActionListener::escapeAction()
{
}
