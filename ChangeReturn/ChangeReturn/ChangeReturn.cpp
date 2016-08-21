// ChangeReturn.cpp
// This program simulates a vending machine
// User chooses what he/she wants to buy
// Inserts the amount of money
// Change is presented in amounts of quarters,
// dimes, nickels, and pennies
//

#include "stdafx.h"
#include <iostream>

// change object???
// member variables - quarters, dimes, nickels, pennies
// member function - calculate amount of each coin
class Change
{
private:
	int quarters;
	int dimes;
	int nickels;
	int pennies;

public:
	void setChange(int cents);

	void getChange();
};

void Change::setChange(int cents)
{
	// calculate difference
	// if difference is negative, ask for more money (maybe do while or while)
	// use integer division to know how many of each coin
	// then use modulus to know how much change is left
	// repeat for each coin
}

void Change::getChange()
{
	// output member variables
}

// function to calculate difference between amount of money
// inserted and price of item

// function to calculate amount of each coin

int main()
{
	// output items for sale

	// user chooses item he/she wants
	
	// setChange()

	// getChange()
    return 0;
}

