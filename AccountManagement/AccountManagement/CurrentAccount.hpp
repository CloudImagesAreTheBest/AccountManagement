#pragma once

#include "Account.hpp"

class CurrentAccount : public Account
{
public:
	CurrentAccount();
	CurrentAccount(string owner, int number);
	~CurrentAccount();
	bool Withdraw(double amount);

private:
	string CreateNewNumber(int number);
};

