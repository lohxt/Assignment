#include <iostream>
#include <iomanip>
#include "header.cpp"
using namespace std;

int main()
{
	int role;

	cout << "===== NAIL CARE & ART BOOKING SYSTEM =====\n" << endl;

	cout << "What is your role?\n"
		<< "1. Admin\n"
		<< "2. Expert\n"
		<< "3. Customer\n" << endl;

	cout << "Role: ";
	cin >> role;

	if (role == 1) {

	}
	else if (role == 2) {

	}
	else if (role == 3) {
		cin.ignore();
		customer();
	}
	else {
		cout << "Invalid Role Number!" << endl;
	}

	return 0;
}