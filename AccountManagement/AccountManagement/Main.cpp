#include "Database.hpp"
#include "OutputMgt.h"
#include "CurrentAccount.hpp"
#include "SavingsAccount.hpp"
#include "TestClass.h"
#include <iostream>
#include <conio.h>

// BASE MENU CAPTIONS
#define CAPTION_BASEMENU_EXIT						"Beenden"
#define CAPTION_BASEMENU_LOGIN						"Anmelden"
#define CAPTION_BASEMENU_CREATEACCOUNT				"Konto erstellen"
#define CAPTION_BASEMENU_INFO						"Info"

// ACCOUNT CREATION MENU
#define CAPTION_ACC_CREATE_MENU_CURRENTACCOUNT		"Kontokorrentkonto"
#define CAPTION_ACC_CREATE_MENU_SAVINGSACCOUNT		"Sparkonto"

// WELCOME CAPTIONS
#define CAPTION_STARTING_WELCOME					"Willkommen zur Kontenverwaltung"

// OPTION CAPTIONS
#define CAPTION_CONFIRMATION_CHOOSE_OPTION			"Bitte waehlen Sie eine Option!"
#define CAPTION_INPUT								"Eingabe: "

// SALUTATION CAPTIONS
#define CAPTION_SALUTATION_1						"Vielen Dank fuer das Nutzen der Kontenverwaltung!"
#define CAPTION_SALUTATION_2						"Bis zum naechsten Mal\n"

// INFO CAPTIONS
#define CAPTION_INFO_CREATEDBY						"Erstellt von Tim C. und Kevin M."
#define CAPTION_INFO_YEAR							"2018\n"

// Additional database handling based on the account application
bool InitializeDatabase(const char* databaseName);
bool GetNumberRange(const char* databaseName, int* number, int type);
bool CheckAccount(const char* databaseName, const string accountNumber);
bool InsertNewSavingsAccount(const char* databaseName, SavingsAccount account, int number);
bool InsertNewCurrentAccount(const char* databaseName, CurrentAccount account, int number);
bool UpdateBalance(const char* databaseName, int id, double balance);
bool DeleteAccount(const char* databaseName, int id);

// Additional output handling based on the account application
void InsertListEntry(list<string> &listToModify, string entryToAdd);
int GetListEntryIndex(list<string> stringList, string stringToSearch);
void DisplayHeader(list<string> menuToDisplay);

int main()
{
	const char* DatabaseName = "Accounts.db";
	string nameOfAccountOwner, accountNumberToVerify;
	list<string> baseMenu, accountCreationMenu;

	int userFirstInput, userSecondInput;
	bool databaseIsInitialized = false, databaseResult = false;

	InsertListEntry(baseMenu, CAPTION_BASEMENU_LOGIN);
	InsertListEntry(baseMenu, CAPTION_BASEMENU_CREATEACCOUNT);
	InsertListEntry(baseMenu, CAPTION_BASEMENU_EXIT);
	InsertListEntry(baseMenu, CAPTION_BASEMENU_INFO);

	// Welcome message and login prompt
	DisplayHeader(baseMenu);

	// Set input focus and demand input
	Output::SetInputFocus(CAPTION_INPUT, 13);
	cin >> userFirstInput;

	while (userFirstInput != GetListEntryIndex(baseMenu, CAPTION_BASEMENU_EXIT)) {
		// Initialize the database
		if (!databaseIsInitialized) InitializeDatabase(DatabaseName);

		// Check what the user input is
		// switch case didn't work because no constants
		if (userFirstInput == GetListEntryIndex(baseMenu, CAPTION_BASEMENU_LOGIN)) {
			// CASE: LOGIN
			// Input of account no. and verify it
			cout << "Bitte Geben sie Ihre Kontonummer ein: ";
			cin >> accountNumberToVerify;
			databaseResult = CheckAccount(DatabaseName, accountNumberToVerify);

			if (!databaseResult)
			{
				cout << "Keine gültige Kontonummer eingegeben\n";
			}
			else
			{
				cout << "Login erfolgreich\n";
				// TODO hier Menü für funktionen
			}
		}
		else if (userFirstInput == GetListEntryIndex(baseMenu, CAPTION_BASEMENU_INFO)) {
			// CASE: DISPLAY INFORMATION
			Output::PrintSeperator('+', true);
			Output::PrintCenteredLine(CAPTION_INFO_CREATEDBY);
			Output::PrintCenteredLine(CAPTION_INFO_YEAR);
			Output::PrintSeperator('+');

			getchar();
		}
		else if (userFirstInput == GetListEntryIndex(baseMenu, CAPTION_BASEMENU_CREATEACCOUNT)) {
			// CASE: CREATE ACCOUNT
			// Ask for account type
			Output::PrintCenteredLine(CAPTION_CONFIRMATION_CHOOSE_OPTION);
			Output::PrintNumberedList(accountCreationMenu, 10, true);

			// Set input focus and demand input
			Output::SetInputFocus(CAPTION_INPUT, 13);
			cin >> userSecondInput;

			int number;

			if (userSecondInput == GetListEntryIndex(accountCreationMenu, CAPTION_ACC_CREATE_MENU_CURRENTACCOUNT)) {
				// Create current account
				cin >> nameOfAccountOwner;

				databaseResult = GetNumberRange(DatabaseName, &number, 2);

				if (databaseResult)
				{
					CurrentAccount currentAccountToCreate(nameOfAccountOwner, 1);
					databaseResult = InsertNewCurrentAccount(DatabaseName, currentAccountToCreate, number);

					if (databaseResult)
					{
						cout << "Kontokorrentkonto mit der Kontonummer: " << currentAccountToCreate.GetNumber() << " erfolgreich erstellt\n";
					}
					else
					{
						cout << "Kontokorrentkonto konnte nicht erstellt werden\n";
					}
				}
				else
				{
					cout << "Kontokorrentkonto konnte nicht erstellt werden\n";
				}

				getchar();
			}
			else if (userSecondInput == GetListEntryIndex(accountCreationMenu, CAPTION_ACC_CREATE_MENU_SAVINGSACCOUNT)) {
				// Create saving account
				cin >> nameOfAccountOwner;
				
				databaseResult = GetNumberRange(DatabaseName, &number, 1);

				if (databaseResult)
				{
					SavingsAccount savingsAccountToCreate(nameOfAccountOwner, 1);
					databaseResult = InsertNewSavingsAccount(DatabaseName, savingsAccountToCreate, number);

					if (databaseResult)
					{
						//Nummernkreis updaten
						cout << "Sparkonto mit der Kontonummer: " << savingsAccountToCreate.GetNumber() << " erfolgreich erstellt\n";
					}
					else
					{
						cout << "Sparkonto konnte nicht erstellt werden\n";
					}
				}
				else
				{
					cout << "Sparkonto konnte nicht erstellt werden\n";
				}
				getchar();
			}
		}

		// Refresh the layout
		system("cls");
		DisplayHeader(baseMenu);

		// Set input focus and demand input
		Output::SetInputFocus(CAPTION_INPUT, 13);
		cin >> userFirstInput;
	}

	Output::PrintSeperator('-', true);
	Output::PrintCenteredLine(CAPTION_SALUTATION_1);
	Output::PrintCenteredLine(CAPTION_SALUTATION_2);
	Output::PrintSeperator('-');

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
							   "Number TEXT NOT NULL,"
							   "Owner TEXT NOT NULL,"
							   "Balance REAL NOT NULL,"
							   "IsDeleted INT NOT NULL,"
							   "Type INT NOT NULL)");

	if (!result)
	{
		cout << "Could not create database table.\nReason: " << Database::GetErrorMessage() << endl;

		Database::Close();

		return false;
	}

	result = Database::Execute("CREATE TABLE IF NOT EXISTS NumberRange("
							   "Type INT PRIMARY KEY NOT NULL,"
							   "LastNumber INT NOT NULL)");

	if (!result)
	{
		cout << "Could not create numberrange table.\nReason: " << Database::GetErrorMessage() << endl;

		Database::Close();

		return false;
	}

	int count = -1;

	count = Database::Count("SELECT COUNT(*) FROM NumberRange");

	if (count == -1)
	{
		cout << "Error trying to access numberrange table\nReason: " << Database::GetErrorMessage() << endl;

		Database::Close();

		return false;
	}
	else if (count == 0)
	{
		result = Database::Execute("INSERT INTO NumberRange(Type, LastNumber) VALUES(1, 1)");

		if (!result)
		{
			cout << "Error trying to access numberrange table\nReason: " << Database::GetErrorMessage() << endl;

			Database::Close();

			return false;
		}

		result = Database::Execute("INSERT INTO NumberRange(Type, LastNumber) VALUES(2, 1)");

		if (!result)
		{
			cout << "Error trying to access numberrange table\nReason: " << Database::GetErrorMessage() << endl;

			Database::Close();

			return false;
		}
	}

	Database::Close();

	return true;
}

bool GetNumberRange(const char* databaseName, int* number, int type)
{
	bool result;

	result = Database::Open(databaseName);

	if (!result)
	{
		cout << "Could not open database connection\n";

		return false;
	}

	result = Database::FetchData("SELECT LastNumber FROM NumberRange WHERE Type = " + to_string(type));

	if (!result)
	{
		cout << "Error trying to access numberrange table\nReason: " << Database::GetErrorMessage() << endl;

		Database::Close();

		return false;
	}
	else
	{
		result = Database::FetchRow();

		if (!result)
		{
			cout << "No numberrange found\n";

			Database::Close();

			return false;
		}
		else
		{
			*number = Database::GetInteger("LastNumber");
		}
	}

	Database::Close();

	return true;
}

bool CheckAccount(const char* databaseName, const string accountNumber)
{
	bool result;

	result = Database::Open(databaseName);

	if (!result)
	{
		cout << "Could not open database connection\n";

		return false;
	}

	int count = -1;

	count = Database::Count("SELECT COUNT(*) FROM Accounts WHERE Number = '" + accountNumber + "'");

	if (count == -1)
	{
		cout << "Error trying to access accounts table\nReason: " << Database::GetErrorMessage() << endl;

		Database::Close();

		return false;
	}
	else if (count == 0)
	{
		Database::Close();

		return false;
	}

	Database::Close();

	return true;
}

bool InsertNewSavingsAccount(const char* databaseName, SavingsAccount account, int number)
{
	bool result;

	result = Database::Open(databaseName);

	if (!result)
	{
		cout << "Could not open database connection\n";

		return false;
	}

	result = Database::Execute("INSERT INTO Accounts(Number, Owner, Balance, IsDeleted, Type) VALUES('"
								+ account.GetNumber() + "', '" + account.GetOwner() + "', "
								+ to_string(account.GetBalance()) + ", 0, 1)");

	if (!result)
	{
		cout << "Could not insert account\nReason: " << Database::GetErrorMessage() << endl;

		Database::Close();

		return false;
	}

	Database::Execute("UPDATE NumberRange SET LastNumber = " + to_string(number) + " WHERE Type = 1");

	Database::Close();

	return true;
}

bool InsertNewCurrentAccount(const char* databaseName, CurrentAccount account, int number)
{
	bool result;

	result = Database::Open(databaseName);

	if (!result)
	{
		cout << "Could not open database connection\n";

		return false;
	}

	result = Database::Execute("INSERT INTO Accounts(Number, Owner, Balance, IsDeleted, Type) VALUES('"
								+ account.GetNumber() + "', '" + account.GetOwner() + "', "
								+ to_string(account.GetBalance()) + ", 0, 2)");

	if (!result)
	{
		cout << "Could not insert account\nReason: " << Database::GetErrorMessage() << endl;

		Database::Close();

		return false;
	}

	Database::Execute("UPDATE NumberRange SET LastNumber = " + to_string(number) + " WHERE Type = 2");

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

		Database::Close();

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

		Database::Close();

		return false;
	}

	Database::Close();

	return true;
}

void InsertListEntry(list<string> &listToModify, string entryToAdd) {
	listToModify.push_back(entryToAdd);
}

void DisplayHeader(list<string> menuToDisplay)
{
	Output::PrintCenteredLine(CAPTION_STARTING_WELCOME);
	Output::PrintCenteredLine(CAPTION_CONFIRMATION_CHOOSE_OPTION);
	Output::PrintSeperator('-', true);
	Output::PrintNumberedList(menuToDisplay, 10, true);
	Output::PrintSeperator('-', true);
}

int GetListEntryIndex(list<string> stringList, string stringToSearch)
{
	int iCounter = 1;

	for (list<string>::iterator i = stringList.begin(); i != stringList.end(); ++i)
	{
		if (*i == stringToSearch) {
			return iCounter;
		}
		iCounter++;
	}
}