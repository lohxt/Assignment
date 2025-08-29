#include <iostream>
#include <iomanip>
#include <string>
#include "mainheader.h"
using namespace std;

int main() {
    int role;
    bool exitProgram = false;

    ExpertInfo experts[3] = {
        {"JOSHUA LOKE", "123", {}},
        {"JOSEPH LEE", "123", {}},
        {"CHAN KUM LONG", "123", {}} 
    };

    InitSchedules(experts, 3);

    do {
        cout << "===== CHROMANAILS STUDIO BOOKING SYSTEM =====\n" << endl;
        cout << "WELCOME TO CHROMANAILS STUDIO'S BOOKING SYSTEM!" << endl;
        cout << "Please select the following options below:\n" << endl;
        cout << "If you are an Admin, choose 1\n"
            << "If you are an Expert, choose 2\n"
            << "If you are a Customer, choose 3\n"
            << "Press any key to exit the program\n" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Expert" << endl;
        cout << "3. Customer" << endl;
        cout << "Exit System" << endl;
        cout << "\nSelection: ";
        cin >> role;
        cout << "\n";

        if (role == 1) {
            admin(experts, 3);
        }
        else if (role == 2) {
            Expert(experts, 3);
        }
        else if (role == 3) {
            customer(experts, 3);
        }
        else {
            exitProgram = true;
            system("CLS");
        }
    } while (!exitProgram);
    cout << "THANK YOU FOR USING CHROMANAILS STUDIO'S BOOKING SYSTEM! PLEASE COME AGAIN SOON!" << endl;

    return 0;
}