#include "Account.hpp"

int Account::GetId()
{
	return Id;
}

string Account::GetNumber()
{
	return Number;
}

string Account::GetOwner()
{
	return Owner;
}

double Account::GetBalance()
{
	return Balance;
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