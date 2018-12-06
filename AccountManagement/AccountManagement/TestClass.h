#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include "OutputMgt.h"

class TestClass
{
public:
	static void OutputClass();
private:
	static void LogMessage(string logMessage);
	static void EndTest();
};

