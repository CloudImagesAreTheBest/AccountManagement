#include "Database.hpp"
#include <list>
#include <iostream>
#include <conio.h>

int main() 
{
	bool result;

	result = Database::Open("test.db");

	if (!result)
	{
		cout << "Could not open database connection\n";
		getchar();
		return 0;
	}

	cout << "Connection open\n";
	
	result = Database::Execute("CREATE TABLE IF NOT EXISTS Test("
							   "Id INTEGER PRIMARY KEY NOT NULL, "
							   "Name TEXT NOT NULL)");
	
	if (!result) 
	{ 
		cout << Database::GetErrorMessage() << endl;
		getchar(); 
		return 0;
	}

	cout << "Success\n";
	
	//result = Database::Execute("INSERT INTO Test(Name) VALUES('Tim')");
	//
	//if (!result) cout << Database::GetErrorMessage() << endl;
	//else cout << "Success\n";

	//result = Database::Execute("INSERT INTO Test(Name) VALUES('Kevin')");

	//if (!result) cout << Database::GetErrorMessage() << endl;
	//else cout << "Success\n";

	list<Test> TestList;

	result = Database::FetchData("SELECT rowid, Id, Name FROM Test");

	if (!result)
	{
		cout << Database::GetErrorMessage() << endl;
	}
	else
	{
		while (Database::FetchRow())
		{
			Test newTest;
			newTest.RowId = Database::GetInteger("_rowid");
			newTest.Id = Database::GetInteger("Id");
			newTest.Name = Database::GetString("Name");
			TestList.push_back(newTest);
		}

		Database::FreeMemory();
	}

	cout << "Count: " << Database::Count("SELECT COUNT(*) FROM Test") << endl;

	Database::Close();
	
	cout << "Connection closed\n";

	getchar();
	return 0;
}