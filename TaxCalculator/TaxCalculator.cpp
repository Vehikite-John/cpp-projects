// TaxCalculator.cpp
// A simple program to calculate a user-specified value plus tax
//

//#include "stdafx.h"
#include <iostream>
#include <assert.h>

// Calculates the value plus tax
float calcTax(float value, float tax);

int main()
{
	float value;
	float tax;

	// Get info from user
	std::cout << "Enter dollar value: ";
	std::cin >> value;
	std::cout << "Enter tax percentage (Ex: 9.8): ";
	std::cin >> tax;

	// calculate value plus tax
	float total = calcTax(value, tax);

	// output
	std::cout << "The subtotal is: " << value << std::endl;
	std::cout << "The grand total is: " << total << std::endl;
    return 0;
}

float calcTax(float value, float tax)
{
	assert(value >= 0 && tax >= 0);
	tax /= 100;
	return (value * (1 + tax));
}