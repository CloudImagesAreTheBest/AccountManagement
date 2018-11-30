#include "OutputMgt.h"

// Static private member
CONSOLE_SCREEN_BUFFER_INFO Output::_csbi;
HANDLE Output::_stdHandle;

void Output::PrintCenteredText(const string TextToPrint)
{
	// Checks if the class got initialized, if not -> initialize_Initialize
	_RefreshConsoleScreenBufferInfo();

	cout << "Centered Text" << endl;
}

void Output::PrintIndentedText(const string TextToPrint, int IndentationLevel)
{
	// Checks if the class got initialized, if not -> initialize_Initialize
	_RefreshConsoleScreenBufferInfo();

	cout << "Indented Text" << endl;
}

void Output::PrintNumberedList(const string ListEntry, ...)
{
	// Checks if the class got initialized, if not -> initialize_Initialize
	_RefreshConsoleScreenBufferInfo();

	cout << "Numbered List" << endl;
}

void Output::PrintNormalList(const string ListEntry, ...)
{
	// Checks if the class got initialized, if not -> initialize_Initialize
    _RefreshConsoleScreenBufferInfo();

	cout << "Normal List" << endl;
}

void Output::_RefreshConsoleScreenBufferInfo()
{
	// Save the current standard output handle in _stdHandle
	_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get the current screen buffer information for additional console info
	GetConsoleScreenBufferInfo(_stdHandle, &_csbi);
}