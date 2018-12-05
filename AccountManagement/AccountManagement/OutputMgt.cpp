#include "OutputMgt.h"

// Static private member
CONSOLE_SCREEN_BUFFER_INFO Output::_csbi;
HANDLE Output::_stdHandle;

void Output::PrintCenteredText(const string TextToPrint)
{
	// Checks if the class got initialized, if not -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	int stringLength = TextToPrint.length();
	int midMargin = stringLength / 2;
	int consoleMid = _csbi.dwMaximumWindowSize.X / 2;
	int textStartPos = consoleMid - midMargin;
	SetConsoleCursorPosition(_stdHandle, { (short)textStartPos,_csbi.dwCursorPosition.Y });

	cout << TextToPrint;
}

void Output::PrintIndentedText(const string TextToPrint, int IndentationLevel)
{
	// Checks if the class got initialized, if not -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	cout << "Indented Text" << endl;
}

void Output::PrintNumberedList(list<string> ListEntry)
{
	// Checks if the class got initialized, if not -> _RefreshConsoleScreenBufferInfo
	_RefreshConsoleScreenBufferInfo();

	//list<string>::iterator i;

	/*for (i = ListEntry.begin() ; i < ListEntry.end();)
	{
		cout << *i << endl;
	}*/

	for (list<string>::iterator i = ListEntry.begin(); i != ListEntry.end(); ++i)
	{
		cout << *i << endl;
	}
}

void Output::PrintNormalList(list<string> ListEntry)
{
	// Checks if the class got initialized, if not -> _RefreshConsoleScreenBufferInfo
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