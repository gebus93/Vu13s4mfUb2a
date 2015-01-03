/*
 * MainActionListener.h
 *
 *  Created on: 2 sty 2015
 *      Author: Łukasz
 */

#ifndef ACTIONLISTENER_MAIN_MAINACTIONLISTENER_H_
#define ACTIONLISTENER_MAIN_MAINACTIONLISTENER_H_

#include "../../util/logger/Logger.h"
#include "../../view/main/MainView.h"

class DBManager;

class MainActionListener {
public:
	virtual ~MainActionListener();
	static void invoke();
	void listen(char action);
	bool isRunning() const;

private:
	DBManager* dbManager;
	MainView view;
	Logger log;
	int currentDB;
	bool running;

	MainActionListener();
	void upArrowAction();
	void downArrowAction();
	void deleteDBAction();
	void saveAction();
	void createDBAction();
	void openDBAction();
	void exitAction();
};

#endif /* ACTIONLISTENER_MAIN_MAINACTIONLISTENER_H_ */
