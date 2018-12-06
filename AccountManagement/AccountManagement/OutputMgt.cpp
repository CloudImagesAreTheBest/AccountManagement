#include "OutputMgt.h"

// Static private member
CONSOLE_SCREEN_BUFFER_INFO Output::_csbi;
HANDLE Output::_stdHandle;

void Output::PrintCenteredLine(const string TextToPrint)
{
	// Checks if the class got initialized, if not -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	// Calculate the starting position based on the middle of the console screen subtracted by the half of the length of the string
	int stringLength = TextToPrint.length();
	int midMargin = stringLength / 2;
	int consoleMid = _csbi.dwMaximumWindowSize.X / 2;
	int textStartPos = consoleMid - midMargin;

	// Set the position on the calculated x coordinate
	SetConsoleCursorPosition(_stdHandle, { (short)textStartPos,_csbi.dwCursorPosition.Y });

	// Print out text
	cout << TextToPrint;

	// Set the input focus on the next line
	_SetFocusOnNewLine();
}

void Output::PrintIndentedText(const string TextToPrint, int IndentationLevel)
{
	// Gets the current console screen information -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	for (int i = 1; i <= IndentationLevel; i++) {
		cout << ' ';
	}
	cout << TextToPrint << endl;
}

void Output::PrintNumberedList(list<string> ListEntry)
{
	// Gets the current console screen information -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	// Initialize a counter needed for the enumeration
	int iCounter = 0;

	// Iterate through the entries of the given list
	for (list<string>::iterator i = ListEntry.begin(); i != ListEntry.end(); ++i)
	{
		cout << ++iCounter << ". " << *i << endl;
	}
}

void Output::PrintNumberedList(list<string> ListEntry, int indentationLevel)
{
	// Gets the current console screen information -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	// Initialize a counter needed for the enumeration
	int iCounter = 0;

	// Iterate through the entries of the given list
	for (list<string>::iterator i = ListEntry.begin(); i != ListEntry.end(); ++i)
	{
		for (int f = 1; f <= indentationLevel; f++) {
			cout << ' ';
		}
		cout << ++iCounter << ". " << *i << endl;
	}
}

void Output::PrintNumberedList(list<string> ListEntry, int indentationLevel, bool addLineFeedAtEnd)
{
	// Gets the current console screen information -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	// Initialize a counter needed for the enumeration
	int iCounter = 0;

	// Iterate through the entries of the given list
	for (list<string>::iterator i = ListEntry.begin(); i != ListEntry.end(); ++i)
	{
		for (int f = 1; f <= indentationLevel; f++) {
			cout << ' ';
		}
		cout << ++iCounter << ". " << *i << endl;
	}

	if (addLineFeedAtEnd) {
		cout << endl;
	}
}

void Output::PrintNormalList(list<string> ListEntry)
{
	// Gets the current console screen information -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	// Iterate through the entries of the given list
	for (list<string>::iterator i = ListEntry.begin(); i != ListEntry.end(); ++i)
	{
		cout << *i << endl;
	}
}

void Output::PrintSeperator(char seperatorCharacter)
{
	// Gets the current console screen information -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	// Print out the seperator based on the given character
	for (int i = 1; i <= _csbi.dwMaximumWindowSize.X; i++) {
		cout << seperatorCharacter;
	}

	// Set focus on the new line
	_SetFocusOnNewLine();
}

void Output::PrintSeperator(char seperatorCharacter, bool doLineFeedAtEnd)
{
	// Gets the current console screen information -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	// Print out the seperator based on the given character
	for (int i = 1; i <= _csbi.dwMaximumWindowSize.X - 1; i++) {
		cout << seperatorCharacter;
	}

	if (doLineFeedAtEnd) {
		cout << endl;
	}

	// Set focus on the new line
	_SetFocusOnNewLine();
}

void Output::SetInputFocus(short x)
{
	// Gets the current console screen information -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	// Set focus on new line
	_SetFocusOnNewLine();

	// Set console cursor position at the input location
	SetConsoleCursorPosition(_stdHandle, { x, _csbi.dwCursorPosition.Y });
}

void Output::SetInputFocus(string prompt, short x)
{
	// If prompt is bigger than the x then exit the function
	if (x < prompt.length()) {
		return;
	}
	
	// Gets the current console screen information -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	// Set focus on new line
	_SetFocusOnNewLine();

	// Set console cursor position at the input location
	SetConsoleCursorPosition(_stdHandle, { x - (short)prompt.length(), _csbi.dwCursorPosition.Y });

	// Display prompt
	cout << prompt;
}

void Output::_RefreshConsoleScreenBufferInfo()
{
	// Save the current standard output handle in _stdHandle
	_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get the current screen buffer information for additional console info
	GetConsoleScreenBufferInfo(_stdHandle, &_csbi);
}

void Output::_SetFocusOnNewLine(short x)
{
	// Gets the current console screen information -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	// Set new console cursor position
	SetConsoleCursorPosition(_stdHandle, { x,_csbi.dwCursorPosition.Y + 1 });
}
