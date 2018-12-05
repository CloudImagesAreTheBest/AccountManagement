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
	string GetNumber();
	string GetOwner();
	double GetBalance();
	virtual double CalculateBalance(double amount) = 0;//�berarbeiten: Eine allgemeine Methode zum einzahlen und eine virtual methode zum auszahlen plus setter f�r alle Felder wegen datenbank holen
	list<string> GetInformation();

protected:
	int Id;
	string Number;
	string Owner;
	double Balance;
};

