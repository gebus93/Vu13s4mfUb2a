#include <windows.h>
#include <cstdarg>
#include <cstdio>
#include <string>
#include "colors.h"
#include "utils.h"

#include "../libraries/rlutil/rlutil.h"

using namespace rlutil;
using namespace std;

void setColors(WORD fontColor, WORD bgColor) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE) {
		printf("Error while getting input handle\n");
		return;
	}

	SetConsoleTextAttribute(hStdout, fontColor | bgColor);

}

void fillLine(char c, int count) {
	for (int i = 0; i < count; i++)
		putchar(c);
}

int checkCharacter(char c, int &i, int maxLength, bool (*compare)(char)) {
	if (compare(c) && i < maxLength)
		return c;

	if (c == KEY_BACKSPACE && i > 0) {
		printf("\b \b");
		--i;
		return 0;
	}

	if (i == maxLength)
		putchar(ERROR_SOUND);

	return -1;
}

string inputText(int maxLength) {
	char character = 0;
	int currentIndex = 0;
	char input[255];

	showcursor();
	bool isReading = true;
	do {

		character = checkCharacter(character, currentIndex, maxLength, &isAcceptedChar);

		if (character > 0) {
			putchar(character);
			input[currentIndex++] = character;
		}

		character = getkey();
		isReading = character != KEY_ESCAPE && (character != KEY_ENTER || currentIndex == 0);

	} while (isReading);

	if (character == KEY_ESCAPE) {
		hidecursor();
		throw -1;
	}

	input[currentIndex] = 0;

	hidecursor();

	string result(input);
	return result;
}

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

int inputNumber(int maxValue = 1000000000) {
	char character = 0;
	int currentIndex = 0;
	int number = 0;

	showcursor();
	bool isReading = true;
	do {
		character = checkCharacter(character, currentIndex, 255, &isDigit);

		if (character > 0) {
			int newNumber = number * 10 + character - '0';
			if (newNumber <= maxValue) {
				putchar(character);
				number = newNumber;
				currentIndex++;
			}
		} else if (character == 0) {
			number /= 10;
		}

		character = getkey();
		isReading = character != KEY_ESCAPE && (character != KEY_ENTER || currentIndex == 0);

	} while (isReading);

	if (character == KEY_ESCAPE) {
		hidecursor();
		throw -1;
	}

	hidecursor();

	return number;
}

void center(int length) {
	int y = trows() / 2;
	int x = (tcols() - length) / 2;

	locate(x, y);
}

void centerHorizontal(int y, int length) {
	int x = (tcols() - length) / 2;

	locate(x, y);
}

void centerVertical(int x) {
	int y = trows() / 2;
	locate(x, y);
}

bool isAcceptedChar(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '-';
}

void printStdString(std::string s) {
	printf("%s", s.c_str());
}

void printError(std::string errorDetails, int line) {
	setColors(FONT_COLOR_LIGHT_RED, 0);

	locate(1, line);

	fillLine(' ');

	center(errorDetails.size());
	printStdString(errorDetails);
}

void printSeparator(int columns, ...) {
	va_list item;
	va_start(item, columns);
	for (int i = 1; i <= columns; i++) {
		int columnLength = va_arg(item, int);

		putchar('|');
		fillLine('-', columnLength);
	}
	va_end(item);

	putchar('|');
}

void printSeparatorForThreeColumns(int length1, int length2, int length3) {
	printSeparator(3, length1, length2, length3);
}

std::string numberToString(int n) {
	if (n == 0)
		return "0";

	bool negative = false;
	std::string number = "";

	if (n < 0) {
		negative = true;
		n *= -1;
	}

	while (n) {
		number = char(n % 10 + 48) + number;
		n /= 10;
	}

	if (negative)
		return "-" + number;

	return number;

}

bool compareBySurname(People a, People b) {
	return strcmp(a.getSurname().c_str(), b.getSurname().c_str());
}

bool compareByName(People a, People b) {
	return strcmp(a.getName().c_str(), b.getName().c_str());
}

bool compareByDefaultCriteria(People a, People b) {
	return a.getCreateDate() > b.getCreateDate();
}
