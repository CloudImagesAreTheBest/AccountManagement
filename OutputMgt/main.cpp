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
	Output::PrintNumberedList("NumberedList");
	Output::PrintCenteredText("Centered");
}