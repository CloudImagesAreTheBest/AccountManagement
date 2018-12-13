#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <stdarg.h>
#include <list>

using namespace std;

// Handles the output of the main programm
class Output
{
public:
	// Prints a centered text 
	static void PrintCenteredLine(const string TextToPrint);

	// Prints a indented text with a given indentation level
	static void PrintIndentedText(const string TextToPrint, int IndentationLevel);

	// Prints a numbered list
	static void PrintNumberedList(list<string> ListEntry);

	// Prints a numbered list with indentation
	static void PrintNumberedList(list<string> ListEntry, int indentationLevel);

	// Prints a numbered list with indentation and a line feed at the end if boolean parameter is true
	static void PrintNumberedList(list<string> ListEntry, int indentationLevel, bool addLineFeedAtEnd);

	// Prints a list without numbers
	static void PrintNormalList(list<string> ListEntry);

	// Prints a list without numbers
	static void PrintNormalList(list<string> ListEntry, int indentationLevel);

	// Prints a list without numbers
	static void PrintNormalList(list<string> ListEntry, int indentationLevel, bool addLineFeedAtEnd);

	// Prints a seperator
	static void PrintSeperator(char seperatorCharacter);

	// Prints a seperator with line feed at end if true
	static void PrintSeperator(char seperatorCharacter, bool doLineFeedAtEnd);

	// Set input focus for user
	static void SetInputFocus(short x = 0);

	// Set input focus for user with prompt
	static void SetInputFocus(string prompt, short x = 0);
private:
	// Variable of the console screen buffer info which is needed for the calculation
	// of the centered text or to get the current cursor position
	static CONSOLE_SCREEN_BUFFER_INFO _csbi;

	// Standard output handle will be saved in this variable
	static HANDLE _stdHandle;

	// Initialize the class
	static void _RefreshConsoleScreenBufferInfo();

	// Sets the current input focus on the new line with a given x coordinate
	static void _SetFocusOnNewLine(short x = 0);
};

