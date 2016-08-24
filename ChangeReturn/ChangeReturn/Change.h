#pragma once
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
	Change() : quarters(0), dimes(0), nickels(0), pennies(0) {};

	void setChange(int cents);

	void getChange();
};