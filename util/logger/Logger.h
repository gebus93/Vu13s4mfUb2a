/*
 * Logger.h
 *
 *  Created on: 27 gru 2014
 *      Author: Łukasz
 */

#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include <cstdio>
#include <string>

class Logger {
public:
	Logger();
	void print(std::string s);
	void printErr(std::string s);
	virtual ~Logger();

private:
	FILE *out;
	FILE *err;
	bool debugMode;

	std::string getDateAndTime();
	void openConnection();
	void closeConnection();
};

#endif /* SRC_LOGGER_H_ */
