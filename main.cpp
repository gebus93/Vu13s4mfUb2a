#include "actionlistener/main/MainActionListener.h"
#include "database/dbmanager/DBManager_test.cpp"

#define DEBUG

int main(int argc, char **argv) {

#ifdef DEBUG
	DBManager_test test;
	test.start();
#endif // DEBUG

	MainActionListener::invoke();

	return 0;
}
