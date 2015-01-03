/*
 * View.h
 *
 *  Created on: 3 sty 2015
 *      Author: Łukasz
 */

#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <cstdio>
#include <string>
#include <vector>
#include "../libraries/rlutil/rlutil.h"

using namespace rlutil;
using namespace std;

class View {
public:
	View();
	virtual ~View();

protected:
	void printMenu(vector<string> menu);
};

#endif /* VIEW_VIEW_H_ */
