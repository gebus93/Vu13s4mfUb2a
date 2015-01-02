/*
 * SelectedDatabaseActionListener.cpp
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#include "SelectedDatabaseActionListener.h"

#include "../singleentity/SingleEntityActionListener.h"

SelectedDatabaseActionListener::SelectedDatabaseActionListener(int currentDB) {
	this->currentDB = currentDB;
	dbManager = &DBManager::getInstance();
}

SelectedDatabaseActionListener::~SelectedDatabaseActionListener()
{
}

void SelectedDatabaseActionListener::invoke()
{
}

void SelectedDatabaseActionListener::listen(char action)
		{
}

void SelectedDatabaseActionListener::upArrowAction()
{
}

void SelectedDatabaseActionListener::downArrowAction()
{
}

void SelectedDatabaseActionListener::deleteEntityAction()
{
}

void SelectedDatabaseActionListener::createEntityAction()
{
}

void SelectedDatabaseActionListener::saveAction()
{
}

void SelectedDatabaseActionListener::saveAsAction()
{
}

void SelectedDatabaseActionListener::escapeAction()
{
}

void SelectedDatabaseActionListener::openEntityInSingleView()
{
	SingleEntityActionListener::invoke();
	// TODO AFTER_INVOKE showDBView();
}
