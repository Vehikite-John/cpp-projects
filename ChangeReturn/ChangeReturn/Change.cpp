#include "Change.h"
#include <iostream>

void Change::setChange(int cents)
{
	// use integer division to know how many of each coin
	// then use modulus to know how much change is left
	// repeat for each coin
	quarters = cents / 25;
	cents %= 25;
	dimes = cents / 10;
	cents %= 10;
	nickels = cents / 5;
	pennies = cents % 5;
}

void Change::getChange()
{
	// output member variables
	std::cout << "Quarters: " << quarters << std::endl;
	std::cout << "Dimes: " << dimes << std::endl;
	std::cout << "Nickels: " << nickels << std::endl;
	std::cout << "Pennies: " << pennies << std::endl;
}