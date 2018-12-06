#pragma once

#include <string>
#include <list>
#include <iomanip>
#include <sstream>

using namespace std;

class Account
{
public:
	int GetId();
	void SetId(int id);
	string GetNumber();
	void SetNumber(string number);
	string GetOwner();
	void SetOwner(string owner);
	double GetBalance();
	void SetBalance(double balance);
	void Deposit(double amount);
	virtual bool Withdraw(double amount) = 0;
	list<string> GetInformation();

protected:
	int Id;
	string Number;
	string Owner;
	double Balance;
};

