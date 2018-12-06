#include "SavingsAccount.hpp"

SavingsAccount::SavingsAccount()
{
	Owner = "Unbekannt";
	Balance = 0;
}

SavingsAccount::SavingsAccount(string owner, int number)
{
	Owner = owner;
	Balance = 0;
	Number = CreateNewNumber(number);
}

SavingsAccount::~SavingsAccount()
{

}

bool SavingsAccount::Withdraw(double amount)
{
	if (amount > Balance)
	{
		return false;
	}
	else
	{
		Balance -= amount;

		return true;
	}
}

string SavingsAccount::CreateNewNumber(int number)
{
	stringstream stream;

	number = abs(number);

	stream << "SK";

	if (number < 10 && number > 0)
	{
		stream << "00" << to_string(number);
	}
	else if (number < 100 && number >= 10)
	{
		stream << "0" << to_string(number);
	}
	else if (number >= 100)
	{
		stream << to_string(number);
	}

	return stream.str();
}