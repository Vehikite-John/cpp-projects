// MathPractice.cpp
// Practice program to get my daughter Zuleyka ready 
// for 2nd grade math
// FUTURE OPTION: change difficulty and add/subtr after do/while

#include "stdafx.h"
#include <iostream>

// Difficulty selector
// 1: 0-10; 2: 0-20; 3: 0-50; 4: 0-100
int setDifficulty(int selection);

// Random number generator
// based on difficulty
int generateRandomNumber(int difficulty);

// addition/subtraction selector
// 1: add; 2: subtract; 3: mixed
int setOperator(int selection);

// Randome operator generator
// needed only if mixed chosen with setOperator()
int generateOperator();

// Function to clear cin when invalid input occurs
void clearCin(int invalidInput);

int main()
{
	bool continuePlaying = true;
	int operatorSelection;
	int difficultySelection;

	// do while for operator selection
	do 
	{
		std::cout << "Choose operator: ";
		std::cin >> operatorSelection;

		if (operatorSelection < 1 || operatorSelection > 2)
		{
			std::cout << "Invalid input. Please try again.\n";
			clearCin(operatorSelection);
		}
	} while (operatorSelection != 1 && operatorSelection != 2);

	// do while for difficulty selection
	do
	{
		std::cout << "Choose difficulty: \n";
		std::cout << "1: Easy (numbers 0-10)\n";
		std::cout << "2: Medium (numbers 0-20)\n";
		std::cout << "3: Hard (numbers 0-50)\n";
		std::cout << "4: Hardest (numbers 0-100)\n";
		std::cin >> difficultySelection;

		if (difficultySelection < 1 || difficultySelection > 2)
		{
			std::cout << "Invalid input. Please try again.\n";
			clearCin(difficultySelection);
		}
	} while (difficultySelection >= 1 && difficultySelection <= 4);


	// Math practice begins
	do
	{
		
	} while (continuePlaying == true);

    return 0;
}