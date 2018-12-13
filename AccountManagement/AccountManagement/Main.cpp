#include "main.h"

int main()
{
	const char* DatabaseName = "Accounts.db";
	string nameOfAccountOwner, accountNumberToVerify;
	list<string> baseMenu, accountCreationMenu, loginMenu;

	int userFirstInput, userSecondInput;
	bool databaseIsInitialized = false, databaseResult = false;

	// Insert base menu list entries
	InsertListEntry(baseMenu, CAPTION_BASEMENU_LOGIN);
	InsertListEntry(baseMenu, CAPTION_BASEMENU_CREATEACCOUNT);
	InsertListEntry(baseMenu, CAPTION_BASEMENU_EXIT);
	InsertListEntry(baseMenu, CAPTION_BASEMENU_INFO);

	// Insert login menu list entries
	InsertListEntry(loginMenu, CAPTION_LOGINMENU_PRINTINFORMATION);
	InsertListEntry(loginMenu, CAPTION_LOGINMENU_DEPOSIT);
	InsertListEntry(loginMenu, CAPTION_LOGINMENU_WITHDRAW);
	InsertListEntry(loginMenu, CAPTION_LOGINMENU_DELETEACCOUNT);
	InsertListEntry(loginMenu, CAPTION_LOGINMENU_LOGOUT);

	// Insert account creation list entries
	InsertListEntry(accountCreationMenu, CAPTION_ACC_CREATE_MENU_CURRENTACCOUNT);
	InsertListEntry(accountCreationMenu, CAPTION_ACC_CREATE_MENU_SAVINGSACCOUNT);

	// Welcome message and login prompt
	DisplayHeader(baseMenu);

	// Set input focus and demand input
	Output::SetInputFocus(CAPTION_INPUT, 13);
	cin >> userFirstInput;

	while (userFirstInput != GetListEntryIndex(baseMenu, CAPTION_BASEMENU_EXIT)) 
	{
		// Initialize the database
		if (!databaseIsInitialized) InitializeDatabase(DatabaseName);

		// Check what the user input is
		// switch case didn't work because no constants
		if (userFirstInput == GetListEntryIndex(baseMenu, CAPTION_BASEMENU_LOGIN)) 
		{
			// CASE: LOGIN
			// Input of account no. and verify it
			Account* account = NULL;
			Output::PrintCenteredLine(CAPTION_LOGIN_ACCOUNT_NO);

			Output::SetInputFocus(CAPTION_INPUT, 13);
			cin >> accountNumberToVerify;
			databaseResult = CheckAccount(DatabaseName, accountNumberToVerify, &account);
			if (!databaseResult) 
			{
				Output::PrintCenteredLine(CAPTION_LOGIN_INVALID_ACCOUNT_NO);

				cin.ignore();
				getchar();
			}
			else 
			{
				Output::PrintCenteredLine(CAPTION_LOGIN_PROCEDURE_SUCCESSFUL);

				Sleep(1500);

				system("cls");
				DisplayHeader(loginMenu);

				Output::SetInputFocus(CAPTION_INPUT, 13);
				cin >> userSecondInput;

				while (userSecondInput != GetListEntryIndex(loginMenu, CAPTION_LOGINMENU_LOGOUT))
				{
					bool accountIsDeleted = false;
					double amount = 0.0;
					bool withdrawResult = true;
					if (userSecondInput == GetListEntryIndex(loginMenu, CAPTION_LOGINMENU_PRINTINFORMATION))
					{
						cout << endl;
						Output::PrintNormalList(account->GetInformation(), 13);
					}
					else if (userSecondInput == GetListEntryIndex(loginMenu, CAPTION_LOGINMENU_DEPOSIT))
					{
						Output::PrintCenteredLine(CAPTION_ACTION_DEPOSIT_AMOUNT);

						// Set input focus
						Output::SetInputFocus(CAPTION_INPUT, 13);
						cin >> amount;

						// Deposit
						account->Deposit(amount);
						UpdateBalance(DatabaseName, account->GetId(), account->GetBalance());
					}
					else if (userSecondInput == GetListEntryIndex(loginMenu, CAPTION_LOGINMENU_WITHDRAW))
					{
						Output::PrintCenteredLine(CAPTION_ACTION_WITHDRAW_AMOUNT);

						// Set input focus
						Output::SetInputFocus(CAPTION_INPUT, 13);
						cin >> amount;

						// Withdraw action
						withdrawResult = account->Withdraw(amount);
						if (withdrawResult)
						{
							UpdateBalance(DatabaseName, account->GetId(), account->GetBalance());
						}
						else
						{
							Output::PrintCenteredLine(CAPTION_ACTION_WITHDRAW_FAILED(to_string(account->GetBalance())));
						}
					}
					else if (userSecondInput == GetListEntryIndex(loginMenu, CAPTION_LOGINMENU_DELETEACCOUNT))
					{
						DeleteAccount(DatabaseName, account->GetId());
						cout << CAPTION_ACTION_DELETED;
					}

					cin.ignore();
					getchar();

					if (accountIsDeleted) break;

					system("cls");
					DisplayHeader(loginMenu);
					Output::SetInputFocus(CAPTION_INPUT, 13);
					cin >> userSecondInput;
				}
			}
			delete account;
			account = NULL;
		}
		else if (userFirstInput == GetListEntryIndex(baseMenu, CAPTION_BASEMENU_INFO)) {
			// CASE: DISPLAY INFORMATION
			Output::PrintSeperator('+', true);
			Output::PrintCenteredLine(CAPTION_INFO_CREATEDBY);
			Output::PrintCenteredLine(CAPTION_INFO_YEAR);
			Output::PrintSeperator('+');

			cin.ignore();
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
				//cout << "Bitte geben Sie Ihren Namen ein: ";
				Output::PrintCenteredLine(CAPTION_CREATE_ACCOUNT_ENTER_NAME);
				Output::SetInputFocus(CAPTION_INPUT, 13);
				cin >> nameOfAccountOwner;

				databaseResult = GetNumberRange(DatabaseName, &number, 2);

				if (databaseResult)
				{
					CurrentAccount currentAccountToCreate(nameOfAccountOwner, number);
					databaseResult = InsertNewCurrentAccount(DatabaseName, currentAccountToCreate, number);

					if (databaseResult)
					{
						Output::PrintCenteredLine(CAPTION_CREATE_CURRENT_ACCOUNT_SUCCESS(currentAccountToCreate.GetNumber()));
					}
					else
					{
						Output::PrintCenteredLine(CAPTION_CREATE_CURRENT_ACCOUNT_FAIL);
					}
				}
				else
				{
					Output::PrintCenteredLine(CAPTION_CREATE_CURRENT_ACCOUNT_FAIL);
				}
			}
			else if (userSecondInput == GetListEntryIndex(accountCreationMenu, CAPTION_ACC_CREATE_MENU_SAVINGSACCOUNT)) {
				// Create saving account
				Output::PrintCenteredLine(CAPTION_CREATE_ACCOUNT_ENTER_NAME);
				Output::SetInputFocus(CAPTION_INPUT, 13);
				cin >> nameOfAccountOwner;

				databaseResult = GetNumberRange(DatabaseName, &number, 1);

				if (databaseResult)
				{
					SavingsAccount savingsAccountToCreate(nameOfAccountOwner, number);
					databaseResult = InsertNewSavingsAccount(DatabaseName, savingsAccountToCreate, number);

					if (databaseResult)
					{
						Output::PrintCenteredLine(CAPTION_CREATE_SAVINGS_ACCOUNT_SUCCESS(savingsAccountToCreate.GetNumber()));
					}
					else
					{
						Output::PrintCenteredLine(CAPTION_CREATE_SAVINGS_ACCOUNT_FAIL);
					}
				}
				else
				{
					Output::PrintCenteredLine(CAPTION_CREATE_SAVINGS_ACCOUNT_FAIL);
				}
			}

			cin.ignore();
			getchar();
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

	Sleep(2000);

	return 0;
}