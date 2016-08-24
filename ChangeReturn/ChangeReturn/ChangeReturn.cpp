// ChangeReturn.cpp
// This program simulates a vending machine
// User chooses what he/she wants to buy
// Inserts the amount of money
// Change is presented in amounts of quarters,
// dimes, nickels, and pennies
//

#include "stdafx.h"
#include <iostream>
#include "Change.h"

// function to calculate difference between amount of money
// inserted and price of item
int calculateDifferenceCents(float price, float money);

const int MAXITEMS = 3;

// clearCin()
void clearCin(int input);

int main()
{
	int selection;
	float price;
	float money;
	int differenceCents;

	Change change;
	
	// output items for sale
	std::cout << "Welcome to the JV Vending Machine!\n";
	std::cout << "Here are the items for sale:\n";
	std::cout << "1: Snickers - $1.29\n";
	std::cout << "2: Cheetos - $1.67\n";
	std::cout << "3: Ice Cream Sandwich - $2.07\n\n";
	std::cout << "What do you want?\n";
	std::cout << "Selection: ";

	// user chooses item he/she wants
	std::cin >> selection;
	
	while (selection < 1 || selection > MAXITEMS)
	{
		std::cout << "Invalid selection. Please try again.\nSelection: ";
		clearCin(selection);
	}

	switch (selection)
	{
	case 1:
		price = 1.29;
		break;
	case 2:
		price = 1.67;
		break;
	case 3:
		price = 2.07;
		break;
	}

	// ask for money
	std::cout << "Please enter money (ex: 2.00): ";
	std::cin >> money;

	// error handling - FOR FUTURE RELEASE

	// calculate difference
	// if difference is negative, ask for more money
	differenceCents = calculateDifferenceCents(price, money);
	
	while (differenceCents < 0)
	{
		// ask for more money
		std::cout << "Please enter more money (ex:2.00): ";
		float moreMoney;
		std::cin >> moreMoney;
		money += moreMoney;

		// difference
		differenceCents = calculateDifferenceCents(price, money);
	}
	// setChange()
	change.setChange(differenceCents);

	std::cout << "Total change: $" << (money - price) << "\n";
	
	// getChange()
	change.getChange();

    return 0;
}

void clearCin(int input)
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int calculateDifferenceCents(float price, float money)
{
	return ((int)((money - price) * 100));
}