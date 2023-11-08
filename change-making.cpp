// The change making program
#include <iostream>
using namespace std;

const int CENTS_PER_QUARTER = 25;
const int CENTS_PER_DIME = 10;
const int CENTS_PER_NICKEL = 5;

int main()
{
	int cents;	  // Total number of cents, input
	int quarters; // Number of quarters, output
	int dimes;	  // Number of dimes, output
	int nickels;  // Number of nickels, output
	int pennies;  // Number of pennies, output

	// Get total number of cents
	cout << "Input cents: ";
	cin >> cents;

	// Calculate number of each coins, largest value first
	quarters = cents / CENTS_PER_QUARTER;
	cents %= CENTS_PER_QUARTER; // Cents remaining after quarters
	dimes = cents / CENTS_PER_DIME;
	cents %= CENTS_PER_DIME; // Cents remaining after dimes
	nickels = cents / CENTS_PER_NICKEL;
	pennies = cents % CENTS_PER_NICKEL;

	// Output number of each coin
	cout << "Quarters: " << quarters << endl;
	cout << "Dimes:    " << dimes << endl;
	cout << "Nickels:  " << nickels << endl;
	cout << "Pennies:  " << pennies << endl;

	return 0;
}
