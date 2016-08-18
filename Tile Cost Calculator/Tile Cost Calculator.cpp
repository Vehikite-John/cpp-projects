// Tile Cost Calculator.cpp
// Calculate the cost to put tile on a four-sided room
//

//#include "stdafx.h"
#include <iostream>
#include "assert.h"

// Room class to practice class construction
class Room {
public:
	// constructors
	// default constructor
	Room() {};
	
	// non-default constructor
	Room(float len, float wid) : length(len), width(wid) {};

	float calcArea()
	{
		return length * width;
	}

	float setLength(float len)
	{
		length = len;
	}

	float setWidth(float wid)
	{
		width = wid;
	}

private:
	// member variables
	float length;
	float width;
};

float calcTileCost(float cost, float area)
{
	return area * cost;
}

int main()
{
	float cost;
	float width;
	float length;
	
	// get data from user
	std::cout << "Please enter the length of the room: ";
	std::cin >> length;
	std::cout << "Please enter the width of the room: ";
	std::cin >> width;
	std::cout << "Please enter the cost per unit in dollars: ";
	std::cin >> cost;

	// error handling
	assert(length > 0 && width > 0 && cost >= 0);
	
	// create new room with user specified length and width
	Room newRoom(length, width);

	// calculate the cost to tile entire area
	float total = calcTileCost(cost, newRoom.calcArea());

	std::cout << "The cost to tile the entire room is: " << total << std::endl;
    return 0;
}

