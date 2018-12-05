#include "SavingsAccount.hpp"

SavingsAccount::SavingsAccount()
{
	Owner = "Unbekannt";
	Balance = 0;
}

SavingsAccount::SavingsAccount(string owner)
{
	Owner = owner;
	Balance = 0;
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