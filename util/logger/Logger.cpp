/*
 * Logger.cpp
 *
 *  Created on: 27 gru 2014
 *      Author: Łukasz
 */

#include "Logger.h"
#include "../../compilation_mode.h"

#include <sys/types.h>
#include <ctime>

#include <cstdio>

Logger::Logger() {
	out = err = NULL;

#ifndef DEBUG
	debugMode = false;
#else
	debugMode = true;
#endif
}

std::string Logger::getDateAndTime() {
	time_t t = time(0);
	struct tm* now = localtime(&t);
	int year = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int day = now->tm_mday;

	int hour = now->tm_hour;
	int minute = now->tm_min;
	int sec = now->tm_sec;

	char buf[20];

	sprintf(buf, "%4d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute,
			sec);
	std::string s(buf);

	return s;
}

void Logger::print(std::string s) {
	if (debugMode == false)
		return;

	openConnection();

	if (out == NULL)
		return;

	std::string dateAndTime = getDateAndTime();
	fprintf(out, "%s | %s\n", dateAndTime.c_str(), s.c_str());
	fflush(out);

	closeConnection();
}

void Logger::printErr(std::string s) {
	if (debugMode == false)
		return;

	openConnection();

	if (err == NULL)
		return;

	std::string dateAndTime = getDateAndTime();
	fprintf(err, "%s | %s\n", dateAndTime.c_str(), s.c_str());
	fflush(err);

	closeConnection();
}

Logger::~Logger() {
	closeConnection();
}

void Logger::openConnection()
{
	out = fopen("out.log", "a+");
	err = fopen("err.log", "a+");
}

void Logger::closeConnection()
{
	if (out != NULL) {
		fclose(out);
		out = NULL;
	}

	if (err != NULL) {
		fclose(err);
		err = NULL;
	}
}
