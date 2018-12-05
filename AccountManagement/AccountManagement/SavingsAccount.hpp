#pragma once

#include "Account.hpp"

class SavingsAccount : public Account
{
public:
	SavingsAccount();
	SavingsAccount(string owner);
	~SavingsAccount();
	double CalculateBalance(double amount);

private:

};

