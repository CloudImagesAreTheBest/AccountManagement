#pragma once

#include "Account.hpp"

class SavingsAccount : public Account
{
public:
	SavingsAccount();
	SavingsAccount(string owner, int number);
	~SavingsAccount();
	bool Withdraw(double amount);

private:
	string CreateNewNumber(int number);
};

