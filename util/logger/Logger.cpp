/*
 * Logger.cpp
 *
 *  Created on: 27 gru 2014
 *      Author: Łukasz
 */

#include "Logger.h"

#include <sys/types.h>
#include <ctime>

Logger::Logger() {
	debugMode = true;
	out = fopen("out.log", "a+");
	err = fopen("err.log", "a+");
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
	if (debugMode == false || out == NULL)
		return;

	std::string dateAndTime = getDateAndTime();
	fprintf(out, "%s | %s\n", dateAndTime.c_str(), s.c_str());
	fflush(out);
}

void Logger::printErr(std::string s) {
	if (debugMode == false || err == NULL)
		return;

	std::string dateAndTime = getDateAndTime();
	fprintf(err, "%s | %s\n", dateAndTime.c_str(), s.c_str());
	fflush(err);
}

Logger::~Logger() {
	if (out != NULL)
		fclose(out);

	if (err != NULL)
		fclose(err);
}

