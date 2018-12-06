#include "Database.hpp"
#include "OutputMgt.h"
#include "CurrentAccount.hpp"
#include "SavingsAccount.hpp"
#include "TestClass.h"
#include <iostream>
#include <conio.h>

// Additional database handling based on the account application
bool InitializeDatabase(const char* databaseName);
bool InsertNewSavingsAccount(const char* databaseName, SavingsAccount account);
bool InsertNewCurrentAccount(const char* databaseName, CurrentAccount account);
bool UpdateBalance(const char* databaseName, int id, double balance);
bool DeleteAccount(const char* databaseName, int id);

// Additional output handling based on the account application
void InsertListEntry(list<string> &listToModify, string entryToAdd);

int main()
{
	const char* DatabaseName = "Accounts.db";
	list<string> baseMenu;

	InsertListEntry(baseMenu, "Anmelden");
	InsertListEntry(baseMenu, "Beenden");
	InsertListEntry(baseMenu, "Info");

	// Welcome message and login prompt
	Output::PrintCenteredLine("Willkommen zur Kontenverwaltung");
	Output::PrintCenteredLine("Bitte waehlen Sie eine Option!");
	Output::PrintSeperator('-');
	Output::PrintNumberedList(baseMenu, 10, true);
	Output::PrintSeperator('-');
	Output::SetInputFocus("Eingabe: ", 13);
	

	/*stringstream stream;
	string test;
	double testdouble = 654325.583;
	stream << fixed << setprecision(2) << testdouble;
	test = stream.str();

	test = "DE38" + test;

	cout << test;*/

	getchar();

	return 0;
}

bool InitializeDatabase(const char* databaseName)
{
	bool result;
	
	result = Database::Open(databaseName);

	if (!result)
	{
		cout << "Could not open database connection\n";
		
		return false;
	}

	result = Database::Execute("CREATE TABLE IF NOT EXISTS Accounts("
							   "Id INTEGER PRIMARY KEY NOT NULL, "
							   "Number TEXT NOT NULL"
							   "Owner TEXT NOT NULL"
							   "Balance REAL NOT NULL"
							   "IsDeleted INT NOT NULL"
							   "Type INT NOT NULL)");

	if (!result)
	{
		cout << "Could not create database table.\nReason: " << Database::GetErrorMessage() << endl;;

		return false;
	}

	Database::Close();

	return true;
}

bool InsertNewSavingsAccount(const char* databaseName, SavingsAccount account)
{
	bool result;

	result = Database::Open(databaseName);

	if (!result)
	{
		cout << "Could not open database connection\n";

		return false;
	}

	result = Database::Execute("INSERT INTO Accounts(Number, Owner, Balance, IsDeleted, Type) VALUES('" 
								+ account.GetOwner() + "', '" + account.GetNumber() + "', " 
								+ to_string(account.GetBalance()) + ", 0, 1)");

	if (!result)
	{
		cout << "Could not insert account\nReason: " << Database::GetErrorMessage() << endl;

		return false;
	}

	Database::Close();

	return true;
}

bool InsertNewCurrentAccount(const char* databaseName, CurrentAccount account)
{
	bool result;

	result = Database::Open(databaseName);

	if (!result)
	{
		cout << "Could not open database connection\n";

		return false;
	}

	result = Database::Execute("INSERT INTO Accounts(Number, Owner, Balance, IsDeleted, Type) VALUES('"
								+ account.GetOwner() + "', '" + account.GetNumber() + "', "
								+ to_string(account.GetBalance()) + ", 0, 2)");

	if (!result)
	{
		cout << "Could not insert account\nReason: " << Database::GetErrorMessage() << endl;

		return false;
	}

	Database::Close();

	return true;
}

bool UpdateBalance(const char* databaseName, int id, double balance)
{
	bool result;

	result = Database::Open(databaseName);

	if (!result)
	{
		cout << "Could not open database connection\n";

		return false;
	}

	result = Database::Execute("UPDATE Accounts SET Balance = " + to_string(balance));

	if (!result)
	{
		cout << "Could not update balance\nReason: " << Database::GetErrorMessage() << endl;

		return false;
	}

	Database::Close();

	return true;
}

bool DeleteAccount(const char* databaseName, int id)
{
	bool result;

	result = Database::Open(databaseName);

	if (!result)
	{
		cout << "Could not open database connection\n";

		return false;
	}

	result = Database::Execute("UPDATE Accounts SET IsDeleted = 1 WHERE Id = " + to_string(id));

	if (!result)
	{
		cout << "Could not delete account " << id << "\nReason: " << Database::GetErrorMessage() << endl;

		return false;
	}

	Database::Close();

	return true;
}

void InsertListEntry(list<string> &listToModify, string entryToAdd) {
	listToModify.push_back(entryToAdd);
}
