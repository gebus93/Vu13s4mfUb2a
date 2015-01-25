/*
 * SingleEntityView.cpp
 *
 *  Created on: 25 sty 2015
 *      Author: admin
 */

#include "SingleEntityView.h"

#include "../../libraries/rlutil/rlutil.h"
#include "../../util/colors.h"
#include "../../util/utils.h"

#include <vector>

SingleEntityView::SingleEntityView() {
	currentEntity = 0;
}

void SingleEntityView::showMainView() {
	cls();
	showMainMenu();

}

void SingleEntityView::setRows(const vector<People>& rows) {
	this->rows = rows;
}

void SingleEntityView::setCurrentEntity(int currentEntity) {
	this->currentEntity = currentEntity;
	showMainView();
}

void SingleEntityView::showMainMenu() {
	std::vector<std::string> menuItems;
	menuItems.push_back("Powrot [Esc]");
	locate(1, 1);
	setColors(FONT_COLOR_LIGHT_GRAY, BACKGROUND_COLOR_LIGHT_BLUE);
	fillLine(' ');
	printMenu(menuItems);
	fillLine(' ');
	setColors(FONT_COLOR_LIGHT_GRAY, 0);
}
