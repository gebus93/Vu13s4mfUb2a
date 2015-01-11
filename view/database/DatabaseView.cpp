/*
 * DatabaseView.cpp
 *
 *  Created on: 11 sty 2015
 *      Author: admin
 */

#include "DatabaseView.h"

DatabaseView::DatabaseView() {
	// TODO Auto-generated constructor stub

}

void DatabaseView::showMainView() {
}

bool DatabaseView::showSaveAsView() {
	return true;
}

bool DatabaseView::showExitView() {
	return true;
}

bool DatabaseView::confirmDeleteView() {
	return false;
}

void DatabaseView::setDbName(const string& dbName) {
	this->dbName = dbName;
}

void DatabaseView::setRows(const vector<People>& rows) {
	this->rows = rows;
}
