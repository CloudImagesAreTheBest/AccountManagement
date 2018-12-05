#include "CurrentAccount.hpp"

CurrentAccount::CurrentAccount()
{
	Owner = "Unbekannt";
	Balance = 0;
}

CurrentAccount::CurrentAccount(string owner)
{
	Owner = owner;
	Balance = 0;
}

CurrentAccount::~CurrentAccount()
{

}

double CurrentAccount::CalculateBalance(double amount)
{
	return Balance += amount;
}
