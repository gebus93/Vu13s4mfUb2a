/*
 * ActionListener.cpp
 *
 *  Created on: 6 sty 2015
 *      Author: Łukasz
 */

#include "ActionListener.h"

ActionListener::ActionListener()
{
	running = true;
}

ActionListener::~ActionListener()
{
}

bool ActionListener::isRunning() const
{
	return running;
}
