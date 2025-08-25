#include <iostream>
#include <cctype>
#include <string>
#include "mainheader.h"
using namespace std;

void Indi_schedule(ExpertInfo experts[], int count) {
    int ex;
    cout << "Select an expert:\n";
    cout << "1. " << experts[0].username << "\n";
    cout << "2. " << experts[1].username << "\n";
    cout << "3. " << experts[2].username << "\n";
    cin >> ex;

    if (ex >= 1 && ex <= 3) {
        ShowExpertSchedule(experts, count, ex - 1);
    }
    else {
        cout << "Invalid expert selection.\n";
    }
}

void Schedule(ExpertInfo experts[], int count) {
    ShowAllSchedules(experts, count);
}

void Customer_list() {
    cout << "Displaying customer list... (Feature pending)\n";
}

void Generate_sales_rpt() {
    cout << "Generating sales report... (Feature pending)\n";
}

void Expert_bonus() {
    cout << "Calculating expert bonus... (Feature pending)\n";
}

void admin(ExpertInfo experts[], int count) {
    char username[50];
    string password, expectedpw;
    bool validUsername = false;

    clearInputBuffer();

    // Login section
    cout << "===== CHROMANAILS STUDIO ADMIN MENU =====\n";

    while (!validUsername) {
        cout << "Enter Username: ";
        cin.getline(username, 50);

        if (username[0] == '\0' || username[1] == '\0') {
            cout << "\n[ERROR] Username must contain only letters and spaces. Please Try Again." << endl;
            continue;
        }

        validUsername = true;

        for (int i = 0; username[i] != '\0'; i++) {
            if (!isalpha(username[i]) && !isspace(username[i])) {
                validUsername = false;
                break;
            }
        }
        if (!validUsername) {
            cout << "\n[ERROR] Username must contain only letters and spaces. Please Try Again." << endl;
        }
    }

    while (true) {
        cout << "Password: ";
        getline(cin, password);

        for (int i = 0; password[i] != '\0'; i++) {
            password[i] = tolower(password[i]);
        }

        expectedpw = string(username) + "123";

        if (password[0] == '\0' || password[1] == '\0') {
            cout << "\n[ERROR] Password cannot be empty! Please Try Again." << endl;
            continue;
        }

        if (password != expectedpw) {
            cout << "\n[ERROR] Wrong Password! Please Try Again." << endl;
        }
        else {
            break;
        }
    }

    for (int i = 0; username[i] != '\0'; i++) {
        username[i] = toupper(username[i]);
    }

    system("CLS");

    int option;
    bool exitMenu = false;

    // Menu loop
    while (!exitMenu) {
        cout << "Welcome, Admin " << username << "!" << endl;
        cout << "What do you want to look at?" << endl;
        cout << "1. Individual Expert Schedule\n"
            << "2. Overall Schedule\n"
            << "3. Customer List\n"
            << "4. Generate Sales Reports\n"
            << "5. Expert Bonus Entitlements\n"
            << "6. Exit to Main Menu\n" << endl;
        cout << "Selection: ";
        cin >> option;

        switch (option) {
        case 1:
            Indi_schedule(experts, 3);
            break;
        case 2:
            Schedule(experts, 3);
            break;
        case 3:
            Customer_list();
            break;
        case 4:
            Generate_sales_rpt();
            break;
        case 5:
            Expert_bonus();
            break;
        case 6:
            exitMenu = true;
            system("CLS");
            break;
        default:
            cout << "[ERROR] Invalid Selection!\n";
            break;
        }
    } 
}
