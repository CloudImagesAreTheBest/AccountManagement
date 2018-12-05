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

double SavingsAccount::CalculateBalance(double amount)
{
	double newBalance = Balance += amount;
	
	return Balance += amount;
}