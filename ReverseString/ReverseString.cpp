// ReverseString.cpp
// This program takes in a string and outputs the string reversed
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>

int main()
{
	std::string userString;
	std::cout << "Please enter a string: ";
	std::getline(std::cin, userString);

	// use reverse function with string iterator
	std::cout << "\"" << userString  << "\" reversed is ";
	
	// reverse() overrides whatever is stored in userString
	std::reverse(userString.begin(), userString.end());
	std::cout << "\"" << userString << "\"" << std::endl;
	
    return 0;
}

