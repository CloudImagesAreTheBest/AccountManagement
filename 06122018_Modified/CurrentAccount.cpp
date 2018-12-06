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

bool CurrentAccount::Withdraw(double amount)
{
	Balance -= amount;
	
	return true;
}
