#include <iostream>
#include <iomanip>
#include "mainheader.h"
using namespace std;

int main() {
    InitSchedules(); // Initialize schedule to all FREE
    int role;
    bool exitProgram = false;

    while (!exitProgram) {
        cout << "===== CHROMANAILS STUDIO BOOKING SYSTEM =====\n" << endl;
        cout << "WELCOME TO CHROMANAILS STUDIO'S BOOKING SYSTEM!" << endl;
        cout << "Please select the following options below:\n" << endl;
        cout << "If you are an Admin, choose 1\n"
            << "If you are an Expert, choose 2\n"
            << "If you are a Customer, choose 3\n"
            << "If you wish to exit the booking system, choose other numbers\n" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Expert" << endl;
        cout << "3. Customer" << endl;
        cout << "4. Exit System" << endl;
        cout << "\nSelection: ";
        cin >> role;
        cout << "\n";

        if (role == 1) {
            admin();
        }
        else if (role == 2) {
            Expert();
        }
        else if (role == 3) {
            customer();
        }
        else {
            exitProgram = true;
            system("CLS");
        }
    }
    cout << "THANK YOU FOR USING CHROMANAILS STUDIO'S BOOKING SYSTEM! PLEASE COME AGAIN SOON!" << endl;

    return 0;
}
