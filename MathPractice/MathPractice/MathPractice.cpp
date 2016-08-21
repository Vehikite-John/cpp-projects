// MathPractice.cpp
// Practice program to get my daughter Zuleyka ready 
// for 2nd grade math
// FUTURE OPTION: change difficulty and add/subtr after do/while

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <string>

// Difficulty selector
// 1: 0-10; 2: 0-20; 3: 0-50; 4: 0-100
int setDifficulty(int selection);

// Random number generator
// based on difficulty
int generateRandomNumber(int difficulty);

// addition/subtraction selector
// 1: add; 2: subtract; 3: mixed
// appears to be unnecessary
//int setOperator(int selection);

// Randome operator generator
// needed only if mixed chosen with setOperator()
// for future release
//int generateOperator();

// Function to clear cin when invalid input occurs
void clearCin(int invalidInput);

int main()
{
	srand(time(NULL));
	bool continuePlaying = true;
	int operatorSelection;
	int difficultySelection;
	int difficulty;
	int answer;
	int guess;

	// do while for operator selection
	do 
	{
		std::cout << "Choose operator:\n";
		std::cout << "1: Addition (+)\n";
		std::cout << "2: Subtraction (-)\nSelection: ";
		std::cin >> operatorSelection;

		if (operatorSelection < 1 || operatorSelection > 2)
		{
			std::cout << "Invalid input. Please try again.\n";
			clearCin(operatorSelection);
		}
		switch (operatorSelection)
		{
		case 1:
			std::cout << "You selected addition.\n";
			break;
		case 2:
			std::cout << "You selected subtraction.\n";
			break;
			
			// Get ready for future release
		case 3:
			std::cout << "You selected both addition and subtraction.\n";
			break;
		}
		std::cout << std::endl;
	} while (operatorSelection != 1 && operatorSelection != 2);

	// do while for difficulty selection
	do
	{
		std::cout << "Choose difficulty: \n";
		std::cout << "1: Easy (numbers 0-10)\n";
		std::cout << "2: Medium (numbers 0-20)\n";
		std::cout << "3: Hard (numbers 0-50)\n";
		std::cout << "4: Hardest (numbers 0-100)\n";
		std::cout << "Selection: ";
		std::cin >> difficultySelection;

		if (difficultySelection < 1 || difficultySelection > 4)
		{
			std::cout << "Invalid input. Please try again.\n";
			clearCin(difficultySelection);
			difficultySelection = 0;
		}
	} while (difficultySelection < 1);


	// Math practice begins
	do
	{
		difficulty = setDifficulty(difficultySelection);
		std::cout << std::endl;
		int num1 = generateRandomNumber(difficulty);
		char input;
		std::string equation;
		int num2 = generateRandomNumber(difficulty);
		if (operatorSelection == 1)
		{
			answer = num1 + num2;
			std::cout << num1 << " + " << num2 << " = ?\n";
		}
		else if (operatorSelection == 2)
		{
			// switch numbers if num2 > num1
			if (num2 > num1)
			{
				int temp = num2;
				num2 = num1;
				num1 = temp;
			}
			answer = num1 - num2;
			std::cout << num1 << " - " << num2 << " = ?\n";
		}
		std::cout << "\nGuess: ";
		std::cin >> guess;

		while (guess != answer)
		{
			std::cout << "Incorrect answer. Please try again.\n";
			clearCin(guess);
			std::cout << "Guess: ";
			std::cin >> guess;
		}

		std::cout << "Good job! How about another one? (y/n): ";
		std::cin >> input;
		if (input == 'n')
		{
			continuePlaying = false;
		}
		std::cout << std::endl;
	} while (continuePlaying == true);

	std::cout << "Have a math-tastic day!\n";
    return 0;
}

int setDifficulty(int selection)
{
	switch (selection)
	{
	case 1:
		return 11;
	case 2:
		return 21;
	case 3:
		return 51;
	case 4:
		return 101;
	}
}

int generateRandomNumber(int difficulty)
{
	return rand() % difficulty;
}

//int setOperator(int selection)
//{
//	switch (selection)
//	{
//	case 1:
//		std::cout << "You selected addition.\n";
//		break;
//	case 2:
//		std::cout << "You selected subtraction.\n";
//		break;
//	case 3:
//		std::cout << "You selected both addition and subtraction.\n";
//		break;
//	}
//}


// For future release
//int generateOperator()
//{
//
//}

void clearCin(int invalidInput)
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}