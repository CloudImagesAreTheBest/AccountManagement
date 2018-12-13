#pragma once

#include "Database.hpp"
#include "Output.h"
#include "CurrentAccount.hpp"
#include "SavingsAccount.hpp"
#include <conio.h>

// BASE MENU CAPTIONS
#define CAPTION_BASEMENU_EXIT						"Beenden"
#define CAPTION_BASEMENU_LOGIN						"Anmelden"
#define CAPTION_BASEMENU_CREATEACCOUNT				"Konto erstellen"
#define CAPTION_BASEMENU_INFO						"Info"

// LOGIN MENU CAPTIONS
#define CAPTION_LOGINMENU_PRINTINFORMATION			"Kontoauszug drucken"
#define CAPTION_LOGINMENU_DEPOSIT					"Einzahlung"
#define CAPTION_LOGINMENU_WITHDRAW					"Auszahlung"
#define CAPTION_LOGINMENU_DELETEACCOUNT				"Konto loeschen"
#define CAPTION_LOGINMENU_LOGOUT					"Abmelden"

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

// LOGIN PROCEDURE CAPTIONS
#define CAPTION_LOGIN_ACCOUNT_NO					"Bitte Geben sie Ihre Kontonummer ein: "
#define CAPTION_LOGIN_INVALID_ACCOUNT_NO			"Keine gueltige Kontonummer eingegeben\n"
#define CAPTION_LOGIN_PROCEDURE_SUCCESSFUL			"Login erfolgreich"

// ACCOUNT ACTIONS
#define CAPTION_ACTION_DEPOSIT_AMOUNT				"Bitte geben sie die Menge ein die sie einzahlen moechten: "
#define CAPTION_ACTION_WITHDRAW_AMOUNT				"Bitte geben sie die Menge ein die sie abheben moechten: "
#define CAPTION_ACTION_WITHDRAW_FAILED(x)			"Nicht genuegend Guthaben vorhanden.\nKontostand ist: " + x
#define CAPTION_ACTION_DELETED						"Konto wurde geloescht"

// ACCOUNT CREATION CAPTIONS
#define CAPTION_CREATE_ACCOUNT_ENTER_NAME			"Bitte geben Sie Ihren Namen ein: "
#define CAPTION_CREATE_CURRENT_ACCOUNT_SUCCESS(x)	"Kontokorrentkonto mit der Kontonummer: " + x + " erfolgreich erstellt\n"
#define CAPTION_CREATE_CURRENT_ACCOUNT_FAIL			"Kontokorrentkonto konnte nicht erstellt werden"
#define CAPTION_CREATE_SAVINGS_ACCOUNT_SUCCESS(x)	"Sparkonto mit der Kontonummer: " + x + " erfolgreich erstellt\n"
#define CAPTION_CREATE_SAVINGS_ACCOUNT_FAIL			"Sparkonto konnte nicht erstellt werden"

// Initialize the database
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
		"NextNumber INT NOT NULL)");

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
		result = Database::Execute("INSERT INTO NumberRange(Type, NextNumber) VALUES(1, 1)");

		if (!result)
		{
			cout << "Error trying to access numberrange table\nReason: " << Database::GetErrorMessage() << endl;

			Database::Close();

			return false;
		}

		result = Database::Execute("INSERT INTO NumberRange(Type, NextNumber) VALUES(2, 1)");

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

// Get the next number from the numberrange for the given type
bool GetNumberRange(const char* databaseName, int* number, int type)
{
	bool result;

	result = Database::Open(databaseName);

	if (!result)
	{
		cout << "Could not open database connection\n";

		return false;
	}

	result = Database::FetchData("SELECT NextNumber FROM NumberRange WHERE Type = " + to_string(type));

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
			*number = Database::GetInteger("NextNumber");
		}
	}

	Database::Close();

	return true;
}

// Check if the accountnumber is valid and return the found account as the third parameter
bool CheckAccount(const char* databaseName, const string accountNumber, Account** outAccount)
{
	bool result;

	result = Database::Open(databaseName);

	if (!result)
	{
		cout << "Could not open database connection\n";

		return false;
	}

	int count = -1;

	count = Database::Count("SELECT COUNT(*) FROM Accounts WHERE Number = '" + accountNumber + "' AND IsDeleted = 0");

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

	result = Database::FetchData("SELECT Id, Number, Owner, Balance, Type FROM Accounts WHERE Number = '" + accountNumber + "' AND IsDeleted = 0");

	if (!result)
	{
		cout << "Error trying to access accounts table\nReason: " << Database::GetErrorMessage() << endl;

		Database::Close();

		return false;
	}

	result = Database::FetchRow();

	if (!result)
	{
		Database::Close();

		return false;
	}

	int type = Database::GetInteger("Type");

	if (type == 1)
	{
		*outAccount = new SavingsAccount();
	}
	else if (type == 2)
	{
		*outAccount = new CurrentAccount();
	}
	else
	{
		cout << "Unknown type\n";

		Database::Close();

		return false;
	}

	(*outAccount)->SetId(Database::GetInteger("Id"));
	(*outAccount)->SetNumber(accountNumber);
	(*outAccount)->SetOwner(Database::GetString("Owner"));
	(*outAccount)->SetBalance(Database::GetDouble("Balance"));

	Database::Close();

	return true;
}

// Insert a new savingsaccount into the database
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

	Database::Execute("UPDATE NumberRange SET NextNumber = " + to_string(++number) + " WHERE Type = 1");

	Database::Close();

	return true;
}

// Insert a new currentaccount into the database
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

	Database::Execute("UPDATE NumberRange SET NextNumber = " + to_string(++number) + " WHERE Type = 2");

	Database::Close();

	return true;
}

// Update the balance for the account belonging to the given id
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

// Delete the account for belonging to the given id
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

// Insert an entry into the given list
void InsertListEntry(list<string> &listToModify, string entryToAdd) {
	listToModify.push_back(entryToAdd);
}

// Display the given list in header format
void DisplayHeader(list<string> menuToDisplay)
{
	Output::PrintCenteredLine(CAPTION_STARTING_WELCOME);
	Output::PrintCenteredLine(CAPTION_CONFIRMATION_CHOOSE_OPTION);
	Output::PrintSeperator('-', true);
	Output::PrintNumberedList(menuToDisplay, 10, true);
	Output::PrintSeperator('-', true);
}

// Get the index of the searched entry from the given list
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