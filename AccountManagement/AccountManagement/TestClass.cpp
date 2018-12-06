#include "TestClass.h"

void TestClass::OutputClass() {
	LogMessage("CLASS: Output");
	LogMessage("PrintCenteredLine");
	Output::PrintCenteredLine("This is a centered line!");
	EndTest();

	LogMessage("PrintIndentedText, Indentation level: 2");
	Output::PrintIndentedText("Indented text level 2", 2);
	EndTest();

	LogMessage("PrintNormalList");
	list<string> testListOfStringsForNormal;
	for (int i = 0; i < 10; i++) {
		testListOfStringsForNormal.push_back("NormalEntry_" + to_string(i));
	}
	Output::PrintNormalList(testListOfStringsForNormal);
	EndTest();

	LogMessage("PrintNumberedList");
	list<string> testListOfStringsForNumbered;
	for (int i = 0; i < 13; i++) {
		testListOfStringsForNumbered.push_back("NumberedEntry_" + to_string(i));
	}
	Output::PrintNumberedList(testListOfStringsForNumbered);
	EndTest();
}

void TestClass::LogMessage(string logMessage) {
	cout << "Start \"" + logMessage + "\":" << endl;
}

void TestClass::EndTest() {
	cout << endl << endl;
}
