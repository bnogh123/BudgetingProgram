// Month.cpp: The class file for the Month class
// by Bassem Noghnogh for CIS-2541-NET02
// last edited 5/10/2021
#include "Month.h"
#include <iostream>
#include <iomanip>
using namespace std;

// initialize static var
int Month::totalMonths = 0;

// default constructor
Month::Month()
{
	monthNum = -1;
	utilities = nullptr;

	// do not let total months go above 12
	if (totalMonths < 12)
		totalMonths++;
}

// Specific nextMonth constructor
Month::Month(int newMonthNum)
{
	monthNum = newMonthNum;
	utilities = new Payment[4];

	// do not increment totmonths
}

// newMonthNum - number of new month
// baseUtility - pointer to base utility for first month
Month::Month(int newMonthNum, Payment* baseUtility)
{
	monthNum = newMonthNum;
	utilities = &baseUtility[4 * (monthNum - 1)];

	// do not let total months go above 12
	if (totalMonths < 12)
		totalMonths++;
}

// newMonthNum - number of new month
// baseUtility - pointer to base utility for first month
void Month::setMonth(int newMonthNum, Payment* baseUtility)
{
	monthNum = newMonthNum;
	utilities = &baseUtility[4 * (monthNum - 1)];
}


// sets the utility's cost
// pos - the utility's position
void Month::setUtility(int pos, double cost)
{
	utilities[pos].setCost(cost);
}

//adds a new payment to the month
void Month::addOtherPayment(Payment newPayment)
{
	// return payment
	other.push_back(newPayment);
}



// prompts for and then adds a new payment to the month
void Month::addOtherPayment()
{
	// initialize variables
	string input;
	double cost;
	Payment newPayment;

	// prompt for name
	cout << "Name: ";
	cin >> input;

	// add name to payment
	newPayment.setName(input);

	// prompt for cost
	cout << "Cost: ";
	cin >> cost;

	while (cost <= 0.0)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a positive number\nCost: ";
		cin >> cost;
	}

	// add cost to payment
	newPayment.setCost(cost);

	// prompt for payment status
	cout << "Is the payment payed(P) or unpayed(U): ";
	cin >> input;

	while (input != "P" && input != "p" && input != "U" && input != "u")
	{
		cout << "Please enter \"P\" for payed, or \"U\" for unpayed: ";
		cin >> input;
	}

	if (input == "P" || input == "p")
		newPayment.setPayed();

	// return payment
	other.push_back(newPayment);
}

// sets an other payment to payed
// pos - position in vector
void Month::payOther(int pos)
{
	try
	{
		other[pos].setPayed();
	}
	catch (const std::exception&)
	{
		cout << "Could not find payment" << endl;
	}
}

// checks if all payments of a month have been payed
bool Month::isAllPayed()
{
	bool allPayed = true;

	//check if utilities are payed
	for (int i = 0; i < 4; i++)
	{
		if (!utilities[i].isPayed())
			allPayed = false;
	}

	//check if other payments are payed
	for (unsigned i = 0; i < other.size(); i++)
	{
		if (!other[i].isPayed())
			allPayed = false;
	}

	return allPayed;
}

// resets the utility at the specified position
void Month::resetUtility(int utilityPos)
{
	utilities[utilityPos].reset();
}

// deletes the nth element of other represented by num
// pos - position in vector
void Month::deleteOther(int pos)
{
	cout << other[pos].getName() << " has been removed." << endl;
	other.erase(other.begin() + pos);
}

void Month::displayAll()
{
	// initialize variables
	string utility = "Utility";

	// set syntax
	cout << fixed << setprecision(2);

	// print out month number
	cout << "  Month " << monthNum << endl;

	//print out header
	cout << left << setw(10) << "  Payment"
		<< setw(10) << "Cost"
		<< setw(14) << "Payment Status" << endl
		<< setw(10) << "  -------"
		<< setw(10) << "----"
		<< setw(10) << "-----" << endl;

	// print out utilities
	for (int i = 0; i < 4; i++)
	{
		switch (static_cast<Utility>(i))
		{
		case Utility::ELEC:
			utility = "Electric";
			break;
		case Utility::NTER:
			utility = "Internet";
			break;
		case Utility::RENT:
			utility = "Rent";
			break;
		case Utility::WATR:
			utility = "Water";
			break;
		}

		cout << "  " << setw(10) << utility
			<< setw(10) << utilities[i].getCost();
		if (utilities[i].isPayed())
			cout << setw(14) << "Payed" << endl;
		else
			cout << setw(14) << "Unpayed" << endl;
	}

	// print out othe payments
	for (int i = 0; i < other.size(); i++)
	{
		other[i].display();
	}
}