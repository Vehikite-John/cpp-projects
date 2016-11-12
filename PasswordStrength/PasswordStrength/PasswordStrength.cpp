/***********************************************************************
* Program:
*    Week 09, Password Strength
*    Brother Wilson, CS470
* Author:
*    John Vehikite
* Summary:
*    A program to analyze the strength of a given user password. 
*    The program will return the number of guesses it will take the 
*    crack the password.
************************************************************************/

//#include "stdafx.h"

#include <string>
#include <iostream>
#include <math.h>		// for log2
#include <iomanip>      // for setprecision

std::string prompt();
double calcCombo(std::string password);
int calcBits(double numCombo);
void output(std::string input, double numCombo, int numBits);
int calcAlphabetSize(std::string password);

int main()
{
	std::string input = prompt();
	double numCombo = calcCombo(input);
	int numBits = calcBits(numCombo);
	output(input, numCombo, numBits);
	
	return 0;
}

std::string prompt() {
	std::string password;
	std::cout << "Please enter the password: ";
	std::cin >> password;
	return password;
}

/*********************************************
* calcCombo
* calculates number of combinations; equating 
* to the number of guesses to crack the password
*********************************************/
double calcCombo(std::string password) {

	int passwordSize = password.length();
	int alphabetSize = calcAlphabetSize(password);
	double numCombo = pow(alphabetSize, passwordSize);
	return numCombo;
}

/*********************************************
* calcAlphabetSize
* calculates possible characters based on char
* types in the password (number, uppercase
* letter, lowercase letter, or symbol)
*********************************************/
int calcAlphabetSize(std::string password) {
	
	int alphabetSize = 0;
	
	// once type is found, change bool to true
	bool foundNum = false;
	bool foundLower = false;
	bool foundUpper = false;
	bool foundSymbol = false;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	
	char currChar = 'a';
	
	// iterate through each char in password
	for (int i = 0; i < password.length(); i++) {
		currChar = password[i];
		if (ispunct(currChar)) {
			if (foundSymbol) {
				continue;
			}
			// There are 32 symbols, so add 32 to alphabetSize
			alphabetSize += 32;
			foundSymbol = true;
		}
		if (isdigit(currChar)) {
			if (foundNum) {
				continue;
			}
			alphabetSize += 10;
			foundNum = true;
		}
		else {
			if (isupper(currChar)) {
				if (foundUpper) {
					continue;
				}
				alphabetSize += 26;
				foundUpper = true;
			}
			else {
				if (foundLower) {
					continue;
				}
				alphabetSize += 26;
				foundLower = true;
			}
		}
	}

	// after iteration, return final alphabet size
	return alphabetSize;
}

/*********************************************
* calcBits
* calculates bit strength
*********************************************/
int calcBits(double numCombo) {
	// bits = log2(n^m)
	// m = password length
	// n = alphabet size
	// numCombo = n^m
	
	int numBits = (int)log2(numCombo);
	return numBits;
}

void output(std::string input, double numCombo, int numBits) {
	// print out double without scientific notation
	std::cout.setf(std::ios::fixed);

	std::cout << "There are " << 
		std::setprecision(0) <<	numCombo <<		// print without decimal
		" combinations\n" << "That is equivalent to a key of " 
		<< numBits << " bits\n";
}