#include "CurrentAccount.hpp"

CurrentAccount::CurrentAccount()
{
	Owner = "Unbekannt";
	Balance = 0;
}

CurrentAccount::CurrentAccount(string owner, int number)
{
	Owner = owner;
	Balance = 0;
	Number = CreateNewNumber(number);
}

CurrentAccount::~CurrentAccount()
{

}

bool CurrentAccount::Withdraw(double amount)
{
	Balance -= amount;
	
	return true;
}

string CurrentAccount::CreateNewNumber(int number)
{
	stringstream stream;

	number = abs(number);

	stream << "KK";

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
