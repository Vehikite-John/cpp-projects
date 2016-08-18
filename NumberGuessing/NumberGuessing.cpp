// NumberGuessing.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <assert.h>
#include <time.h> // for seeding of random number
int main()
{
	bool isCorrect = false;
	int guess;
	int numberOfGuesses = 0;

	// generate random number from 1-100
	// without +1, range would be 0-99
	// number after '+' is the start of range
	// number after '%' is how many numbers in range
	// source for srand() help: http://stackoverflow.com/questions/1108780/why-do-i-always-get-the-same-sequence-of-random-numbers-with-rand
	srand(time(NULL));
	int answer = rand() % 100 + 1;

	std::cout << "Welcome to the number guessing game!\n"
		<< "I'm thinking of a number between 1 and 100...\n";
	do
	{
		numberOfGuesses++;
		std::cout << "Guess: ";
		std::cin >> guess;

		// error handling
		if (guess < 1 || guess > 100)
		{
			std::cout << "Invalid guess. Please try again.\n";

			// following code is needed to handle strings
			// source: http://stackoverflow.com/questions/22122337/while-loop-skipping-cin
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		// compare guess to answer
		// let user know if too high or low
		else
		{
			if (guess == answer)
			{
				std::cout << "You got it! YOU WON!\n";
				std::cout << "It took you " << numberOfGuesses;
				(numberOfGuesses == 1) ? std::cout << " guess!\n" : std::cout << " guesses!\n";
				isCorrect = true;
			}
			else
			{
				if (guess > answer)
				{
					std::cout << "Too high\n";
				}
				else
				{
					std::cout << "Too low\n";
				}
			}
		}

	} while (isCorrect == false);

	return 0;
}

