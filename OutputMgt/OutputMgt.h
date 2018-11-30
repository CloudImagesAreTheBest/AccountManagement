#pragma once

#include <Windows.h>
#include <string>
#include <iostream>

using namespace std;

// Handles the output of the main programm
class Output
{
public:
	// Prints a centered text 
	static void PrintCenteredText(const string TextToPrint);

	// Prints a indented text with a given indentation level
	static void PrintIndentedText(const string TextToPrint, int IndentationLevel);

	// Prints a numbered list
	static void PrintNumberedList(const string ListEntry, ...);

	// Prints a list without numbers
	static void PrintNormalList(const string ListEntry, ...);
private:
	// Variable of the console screen buffer info which is needed for the calculation
	// of the centered text or to get the current cursor position
	static CONSOLE_SCREEN_BUFFER_INFO _csbi;

	// Standard output handle will be saved in this variable
	static HANDLE _stdHandle;

	// Initialize the class
	static void _RefreshConsoleScreenBufferInfo();
};

