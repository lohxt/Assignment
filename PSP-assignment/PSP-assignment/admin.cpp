#include <iostream>
#include <cctype>
#include <string>
#include "mainheader.h"
using namespace std;

void Indi_schedule(ExpertInfo experts[], int count) {
    int expertselect;
    cout << "Select an expert:\n";
    cout << "1. " << experts[0].username << endl;
    cout << "2. " << experts[1].username << endl;
    cout << "3. " << experts[2].username << endl;

    while (true) {
        cout << "\nSelection: ";
        cin >> expertselect;

        if (expertselect >= 1 && expertselect <= 3) {
            system("CLS");
            ShowExpertSchedule(experts, count, expertselect - 1);
            break;
        }
        else if (cin.fail() || (expertselect < 1 || expertselect > 3)){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[ERROR] Invalid Expert Selection! Please Select Expert 1-3 Only." << endl;
        }
    }
}

void Schedule(ExpertInfo experts[], int count) {
    ShowAllSchedules(experts, count);
}

void Customer_list(Booking bookingList[], int bookingCount) {
	string dayNames[5] = { "Mon", "Tue", "Wed", "Thu", "Fri" };
    cout << "===== All Customer Bookings =====\n";
    if (bookingCount == 0)
    {
		cout << "No Customers have booked yet.\n";
        return;
    }
    for (int i = 0; i < bookingCount; i++)
    {
		cout << "Customer: " << bookingList[i].customerName << endl;
		cout << "Service : " << bookingList[i].service << endl;
		cout << "Expert  : " << bookingList[i].expertName << endl;
		cout << "Week    : " << bookingList[i].week << endl;
		cout << "Day     : " << dayNames[bookingList[i].day] << endl;
		cout << "Slot    : " << bookingList[i].slot << endl;
        cout<<"Amount  : RM"<< bookingList[i].amount << " + RM100 (Service Charge)"<< endl;
		cout << string(40, '-') << endl;
    }
}

void Generate_sales_rpt() {
    cout << "Generating sales report... (Feature pending)\n";
}

void Expert_bonus() {
    cout << "Calculating expert bonus... (Feature pending)\n";
}

// ================== Admin Login & Menu ==================
void admin(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount) {
    char username[50];
    string password, expectedpw;
    bool validUsername = false, validPassword = false;

    clearInputBuffer();

    // Login section
    cout << "===== CHROMANAILS STUDIO ADMIN MENU =====\n";

    do {
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
    } while (!validUsername);

    do {
        cout << "Password: ";
        getline(cin, password);

        for (int i = 0; password[i] != '\0'; i++) {
            password[i] = tolower(password[i]);
        }

        expectedpw = string(username) + "123";

        if (password.empty()) {
            cout << "\n[ERROR] Password cannot be empty! Please Try Again." << endl;
            continue;
        }
        else if (password != expectedpw) {
            cout << "\n[ERROR] Wrong Password! Please Try Again." << endl;
        }
        else {
            validPassword = true;
            break;
        }
    } while (!validPassword);

    for (int i = 0; username[i] != '\0'; i++) {
        username[i] = toupper(username[i]);
    }

    system("CLS");

    int option;
    bool exitMenu = false;

    // ===== Admin Menu =====
    do {
        cout << "Welcome, Admin " << username << "!" << endl;
        cout << "What do you want to look at?" << endl;
        cout << "1. View Individual Expert Schedule" << endl;
        cout << "2. View Overall Schedule" << endl;
        cout << "3. View Customer List" << endl;
        cout << "4. View Generate Sales Reports" << endl;
        cout << "5. View Expert Bonus Entitlements" << endl;
        cout << "6. Exit to Main Menu\n" << endl;
        cout << "Selection: ";
        cin >> option;

        while ((option < 1 || option > 6) || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[ERROR] Invalid Selection! Please Choose (1-4) Only." << endl;
            cout << "\nSelection: ";
            cin >> option;
        }

        switch (option) {
        case 1:
            system("CLS");
            Indi_schedule(experts, 3);
            cout << "\nPress [ENTER] to return to Admin Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 2:
            system("CLS");
            Schedule(experts, 3);
            cout << "\nPress [ENTER] to return to Admin Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 3:
			system("CLS");
            Customer_list(bookingList, bookingCount);
			cout << "\nPress [ENTER] to return to Admin Menu.....";
			clearInputBuffer();
			cin.get();
			system("CLS");
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
        }
    } while (!exitMenu);
}
