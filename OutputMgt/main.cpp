#include "OutputMgt.h"

#include <conio.h>
#include <cstdlib>

void TestClassOutput();

int main()
{
	TestClassOutput();

	getchar();
	return 0;
}

// Test function if all methods are working
void TestClassOutput()
{
	Output::PrintIndentedText("Indented",1);
	Output::PrintNormalList("NormalList");

	list<string> TestList;

	for (int i = 0; i < 6; i++)
	{
		TestList.push_back("Entry" + to_string(i));
	}

	Output::PrintNumberedList(TestList);
	Output::PrintCenteredText("Wollen Sie ihren aktuellen Kontostand abfragen?\n");
}