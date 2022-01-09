// Payment.h: The header and class file for the Payment Class
// by Bassem Noghnogh for CIS-2541-NET02
// last edited 5/10/2021
#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Payment
{
private:
	double cost;
	bool payed;
	string name;

public:
	//default constructor for payment
	Payment(double cost, string name)
	{
		setCost(cost);
		setName(name);
		payed = false;
	}

	//alternate constructor for Utility payment
	Payment()
	{
		setCost(0.0);
		setName("Utility");
		payed = false;
	}

	void reset()
	{
		setCost(0.0);
		payed = false;
	}

	void display()
	{
		cout << "  " << left << fixed << setprecision(2);

		cout << setw(10) << name << setw(10) << cost;
		if (payed)
			cout << setw(14) << "Payed" << endl;
		else
			cout << setw(14) << "Unpayed" << endl;
	}

	void setCost(double newCost)
		{ cost = newCost; }

	void setName(string newName)
		{ name = newName; }

	void setPayed()
		{ payed = true; }

	double getCost()
		{ return cost; }

	bool isPayed()
		{ return payed; }

	string getName()
		{ return name; }
};

