#pragma once

#include "Account.hpp"

class SavingsAccount : public Account
{
public:
	SavingsAccount();
	SavingsAccount(string owner);
	~SavingsAccount();
	bool Withdraw(double amount);

private:

};

