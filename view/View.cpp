/*
 * View.cpp
 *
 *  Created on: 3 sty 2015
 *      Author: Łukasz
 */

#include "View.h"
#include "../libraries/rlutil/rlutil.h"

View::View()
{
	rlutil::hidecursor();
}

View::~View()
{
}

void View::printMenu(vector<string> menu) {
	int totalChars = 0;
	int itemsCount = (int) menu.size();

	for (int i = 0; i < itemsCount; i++)
		totalChars += menu[i].size();

	int spaces = tcols() - totalChars;

	if (spaces < itemsCount) {
		printf("Console width is too short.\n");
		return;
	}

	printf("  ");
	unsigned int charsCount = 2;

	for (int i = 0, spacesBetweenItems = (spaces - 2) / itemsCount; i < itemsCount; i++) {
		printf("%s", menu[i].c_str());
		charsCount += menu[i].size();

		for (int j = 0; j < spacesBetweenItems; j++, charsCount++)
			putchar(' ');

	}

	while (charsCount++ < (unsigned int) tcols())
		putchar(' ');
}
