#include "actionlistener/main/MainActionListener.h"
#include "database/dbmanager/DBManager_test.cpp"

#include "compilation_mode.h"

#include "dbgenerator.h"

int main(int argc, char **argv) {

#ifdef RUN_GENERATOR
	generateDatabase();
#endif

#ifdef DEBUG
	DBManager_test test;
	test.start();
#endif

	MainActionListener::invoke();

	return 0;
}
