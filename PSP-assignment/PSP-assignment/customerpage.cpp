#include <iostream>
#include <iomanip>
#include <string>
#include "header.cpp"
using namespace std;

void customer()
{
	string username, password;
	int option;
	char choice;

	cout << "\n===== CHROMANAILS STUDIO BOOKING SYSTEM =====\n" << endl;

	cout << "Enter Username: ";
	getline(cin, username);
	cout << "Password: ";
	cin >> password;

	cout << "Welcome, " << username << "!\n" << endl;
	cout << "What would you like to do today?" << endl;
	cout << "1. View Information About ChromaNails Studio\n"
		<< "2. View Service & Experts\n"
		<< "3. View My Bookings\n"
		<< "4. Exit to Menu\n" << endl;

	cout << "Selection: ";
	cin >> option;

	if (option == 1) {
		cout << "..." << endl;
	}
	else if (option == 2) {
		cout << "\nService: Nail Care & Art\n" << endl;
		cout << "Expert 1: Low Zihao" << endl;
		cout << "Specialization: Nail Art" << endl;
		cout << "Availability: Weekdays 8AM - 8PM" << endl;
		cout << "Service Price: RM600\n" << endl;

		cout << "Expert 2: Lim Shi Ming" << endl;
		cout << "Specialization: Manicure & Pedicure" << endl;
		cout << "Availability: MON - SAT 10AM - 8PM" << endl;
		cout << "Service Price: RM300 Each\n" << endl;

		cout << "Expert 3: Chan Kum Long" << endl;
		cout << "Specialization: Acrylic Nails" << endl;
		cout << "Availability: Weekends 10AM - 4PM" << endl;
		cout << "Service Price: RM750\n" << endl;

		cout << "Do you want to check appointment availability? (Y/N): ";
		cin >> choice;

		switch (choice)
		{
		case 'Y':
		case 'y':
			cout << "..." << endl;
			break;
		case 'N':
		case 'n':
			//return to menu list
			break;
		default:
			cout << "Enter Y/y/N/n. Please try again." << endl;
		}
	}
}