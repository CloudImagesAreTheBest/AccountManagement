#pragma once

#include "Account.hpp"

class CurrentAccount : public Account
{
public:
	CurrentAccount();
	CurrentAccount(string owner);
	~CurrentAccount();
	double CalculateBalance(double amount);

private:

};

