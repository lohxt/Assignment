#include <iostream>
#include <iomanip>
#include <string>
#include "mainheader.h"
using namespace std;

int main() {
    int role;
    bool exitProgram = false;

    ExpertInfo experts[3] = {
        {"JOSHUA LOKE", "123"},
        {"JOSEPH LEE", "123"},
        {"CHAN KUM LONG", "123"} 
    };

    Booking bookingList[MAX_BOOKINGS];
    int bookingCount = 0;

    InitSchedules(experts, 3);

    do {
        cout << "===== CHROMANAILS STUDIO BOOKING SYSTEM =====\n" << endl;
        cout << "WELCOME TO CHROMANAILS STUDIO'S BOOKING SYSTEM!" << endl;
        cout << "Please select the following options below:\n" << endl;
        cout << "If you are an Admin, Choose 1\n"
            << "If you are an Expert, Choose 2\n"
            << "If you are a Customer, Choose 3\n"
            << "To exit the program, Choose 4\n" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Expert" << endl;
        cout << "3. Customer" << endl;
        cout << "4. Exit System" << endl;
        cout << "\nSelection: ";
        cin >> role;

        while ((role < 1 || role > 4) || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[ERROR] Invalid Selection! Please Choose (1-4) Only." << endl;
            cout << "\nSelection: ";
            cin >> role;
        }

        switch (role) {
        case 1:
            cout << "\n";
            admin(experts, 3, bookingList, bookingCount);
            break;
        case 2:
            cout << "\n";
            Expert(experts, 3, bookingList, bookingCount);
            break;
        case 3:
            cout << "\n";
            customer(experts, 3, bookingList, bookingCount);
            break;
        case 4:
            exitProgram = true;
            system("CLS");
            break;
        }
    } while (!exitProgram);
    cout << "THANK YOU FOR USING CHROMANAILS STUDIO'S BOOKING SYSTEM! PLEASE COME AGAIN SOON!" << endl;

    return 0;
}