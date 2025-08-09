#include <iostream>
#include <iomanip>
#include "header.h"
using namespace std;

int main() {
    int role;

    cout << "===== NAIL CARE & ART BOOKING SYSTEM =====\n" << endl;
    cout << "What is your role?\n"
        << "1. Admin\n"
        << "2. Expert\n"
        << "3. Customer\n" << endl;

    cout << "Role: ";
    cin >> role;

    if (role == 1) {
        int choice;
        cout << "What do you want to look at?\n";
        cout << "1. Individual expert schedule\n"
            << "2. Overall schedule\n"
            << "3. Customer list\n"
            << "4. Generate sales reports\n"
            << "5. Expert bonus entitlements\n";
        cin >> choice;

        switch (choice) {
        case 1: Indi_schedule(); break;
        case 2: Schedule(); break;
        case 3: Customer_list(); break;
        case 4: Generate_sales_rpt(); break;
        case 5: Expert_bonus(); break;
        default: cout << "Invalid choice"; break;
        }
    }
    else if (role == 2) {
        cout << "Expert features coming soon...";
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
