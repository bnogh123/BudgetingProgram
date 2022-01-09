// Month.h: The header file for the Month class
// by Bassem Noghnogh for CIS-2541-NET02
// last edited 5/10/2021
#pragma once
#include <vector>
#include "Payment.h"
using namespace std;

enum class Utility{RENT = 0, ELEC = 1, WATR = 2, NTER = 3};

class Month
{
private:
	static int totalMonths;
	int monthNum;
	Payment* utilities;
	vector<Payment> other;

public:
	Month(int, Payment*);
	Month(int);
	Month();
	void setUtility(int, double);
	void setMonth(int, Payment*);
	void addOtherPayment();
	void addOtherPayment(Payment);
	void payOther(int);
	bool isAllPayed();
	void resetUtility(int);
	void deleteOther(int);
	void displayAll();

	int getTotMonths()
		{ return totalMonths; }

	int getMonthNum()
		{ return monthNum; }

	Payment getUtility(int i)
		{ return utilities[i]; }

	Payment getOther(int num)
		{ return other[num]; }

	int getOtherSize()
		{ return (int) other.size(); }
};

