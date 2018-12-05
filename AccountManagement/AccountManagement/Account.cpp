#include "Account.hpp"

int Account::GetId()
{
	return Id;
}

void Account::SetId(int id)
{
	Id = id;
}

string Account::GetNumber()
{
	return Number;
}

void Account::SetNumber(string number)
{
	Number = number;
}

string Account::GetOwner()
{
	return Owner;
}

void Account::SetOwner(string owner)
{
	Owner = owner;
}

double Account::GetBalance()
{
	return Balance;
}

void Account::SetBalance(double balance)
{
	Balance = balance;
}

void Account::Deposit(double amount)
{
	Balance += amount;
}

list<string> Account::GetInformation()
{
	list<string> information;

	stringstream stream;

	stream << fixed << setprecision(2) << Balance;

	information.push_back("Kontonummer:  " + Number);
	information.push_back("Kontoinhaber: " + Owner);
	information.push_back("Kontostand:   " + stream.str());

	return information;
}