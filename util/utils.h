#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "colors.h"
#include "../libraries/rlutil/rlutil.h"
#include "../database/entity/Entity.cpp"
#include<string>

#define ERROR_SOUND 7
#define KEY_BACKSPACE 8

void setColors(WORD fontColor, WORD bgColor);

std::string inputText(int maxLength = 255);

void center(int length);
void centerHorizontal(int y, int length);
void centerVertical(int x = 1);

void printStdString(std::string s);

bool isAcceptedChar(char c);
void fillLine(char c, int count = rlutil::tcols());
void printError(std::string errorDetails, int line = rlutil::trows() / 2);

void printSeparator(int columns, ...);
void printSeparatorForThreeColumns(int length1, int length2, int length3);

std::string numberToString(int n);

bool compareBySurname(People a, People b);
bool compareByName(People a, People b);
bool compareByDefaultCriteria(People a, People b);

#endif // UTILS_H_INCLUDED
