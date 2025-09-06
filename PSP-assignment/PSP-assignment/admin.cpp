#include <iostream>
#include <iomanip>
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
    cout << string(12, '=') << " All Customer Bookings " << string(12, '=') << "\n" << endl;
    if (bookingCount == 0)
    {
		cout << "No Customers Have Booked Yet." << endl;
        return;
    }
    for (int i = 0; i < bookingCount; i++)
    {
		cout << "Customer : " << bookingList[i].customerName << endl;
		cout << "Service  : " << bookingList[i].service << endl;
		cout << "Expert   : " << bookingList[i].expertName << endl;
		cout << "Week     : " << bookingList[i].week << endl;
		cout << "Day      : " << dayNames[bookingList[i].day] << endl;
		cout << "Slot     : " << bookingList[i].slot << endl;
        cout << fixed << setprecision(2);
        cout << "Amount   : RM" << bookingList[i].amount << " + RM100.00 (Service Charge)" << endl;
		cout << string(48, '-') << endl;
    }
}

void Expert_bonus(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount) {
    cout << string(11, '=') << " Expert Bonus Entitlements " << string(11, '=') << "\n\n";

    if (bookingCount == 0) {
        cout << "No Bookings available. Cannot Calculate Bonuses.\n";
        return;
    }

    // Loop through each expert
    for (int e = 0; e < count; e++) {
        string expertName = experts[e].username;
        int hoursWorked = 0;
        double totalCharges = 0.0;
        double bonusRate = 0.0;
        double bonusEarned = 0.0;
        double SERVICE_CHARGE = 100.00;

        // Go through bookings to accumulate hours & value
        for (int i = 0; i < bookingCount; i++) {
            if (bookingList[i].expertName == expertName) {
                hoursWorked += 3; // Each slot is 3 hours
            }
        }

        // Apply bonus rules
        if (hoursWorked < 25) {
            bonusRate = 0.0;
        }
        else if (hoursWorked < 30) {
            bonusRate = 0.25;
        }
        else if (hoursWorked >= 30) {
            bonusRate = 0.5;
        }

        totalCharges = SERVICE_CHARGE * hoursWorked / 3;
        bonusEarned = totalCharges * bonusRate;

        // Print entitlement details
        cout << "Expert: " << expertName << endl;
        cout << "Total Hours Worked     : " << hoursWorked << " hrs" << endl;
        cout << fixed << setprecision(2);
        cout << "Total Service Charges  : RM" << totalCharges << endl;
        cout << "Bonus Rate             : " << (bonusRate * 100) << "%" << endl;
        cout << "Bonus Amount Earned    : RM" << bonusEarned << endl;
        cout << string(49, '-') << "\n" << endl;
    }
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
        case 4: {
            system("CLS");
            int selection;
            bool exitSalesReport = false;
            do {
                cout << string(10, '=') << " SALES REPORT MENU " << string(10, '=') << "\n" << endl;
                cout << "1. View Sales Report By Date Range" << endl;
                cout << "2. View Sales Report By Service Category" << endl;
                cout << "3. View Sales Report By Expert" << endl;
                cout << "4. Exit to Admin Menu\n" << endl;
                cout << "Selection: ";
                cin >> selection;

                while (cin.fail() || (selection < 1 || selection > 4)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "[ERROR] Invalid Selection! Please Choose (1-4) Only." << endl;
                    cout << "\nSelection: ";
                    cin >> selection;
                }

                cout << fixed << setprecision(2);
                switch (selection) {
                case 1: {
                    system("CLS");
                    // ==== Sales by Week Range ====
                    double totalSalesInRange = 0.0;

                    cout << "===== SALES REPORT (Weeks 1-" << WEEKS << ") =====\n" << endl;
                    cout << left << setw(10) << "Week" << setw(15) << "Sales (RM)" << endl;
                    cout << "--------------------------\n";

                    for (int week = 1; week <= WEEKS; week++) {
                        double weeklySales = 0.0;     // reset per week
                        for (int i = 0; i < bookingCount; i++) {
                            if (bookingList[i].week == week) {
                                weeklySales += bookingList[i].amount + 100; // base + service charge
                            }
                        }
                        cout << left << setw(10) << week << setw(15) << weeklySales << "\n";
                        totalSalesInRange += weeklySales;
                    }

                    cout << "--------------------------\n";
                    cout << left << setw(10) << "TOTAL" << setw(15) << totalSalesInRange << "\n" << endl;
                    cout << "Press [ENTER] to return to Admin Menu.....";
                    clearInputBuffer();
                    cin.get();
                    system("CLS");
                    break;
                }
                case 2: {
                    system("CLS");
                    // ==== Total Treatment Sales (By Service Type) ====
                    double NailArtSales = 0.0;
                    double ManicureSales = 0.0;
                    double PedicureSales = 0.0;
                    double AcrylicNailsSales = 0.0;
                    double totalSales = 0.0;
                    cout << "===== SALES REPORT (By Service) =====\n" << endl;

                    for (int i = 0; i < bookingCount; i++) {
                        double value = bookingList[i].amount + 100; // ensure consistent service charge
                        const string& svc = bookingList[i].service;

                        if (svc == "Nail Art") {
                            NailArtSales += value;
                        }
                        else if (svc == "Manicure") {
                            ManicureSales += value;
                        }
                        else if (svc == "Pedicure") {
                            PedicureSales += value;
                        }
                        else if (svc == "Acrylic Nails") {
                            AcrylicNailsSales += value;
                        }
                    }

                    cout << "Nail Art      : RM" << NailArtSales << endl;
                    cout << "Manicure      : RM" << ManicureSales << endl;
                    cout << "Pedicure      : RM" << PedicureSales << endl;
                    cout << "Acrylic Nails : RM" << AcrylicNailsSales << endl;

                    totalSales = NailArtSales + ManicureSales + PedicureSales + AcrylicNailsSales;
                    cout << "-------------------------------------" << endl;
                    cout << "TOTAL SALES   : RM" << totalSales << "\n" << endl;
                    cout << "Press [ENTER] to return to Admin Menu.....";
                    clearInputBuffer();
                    cin.get();
                    system("CLS");
                    break;
                }
                case 3: {
                    system("CLS");
                    // ==== Sales by Expert ====
                    cout << "===== SALES REPORT (By Expert) =====\n" << endl;

                    double totalSales = 0.0;  // <-- reset per run

                    for (int e = 0; e < count; e++) {
                        double expertSales = 0.0; // <-- reset per expert
                        for (int i = 0; i < bookingCount; i++) {
                            if (bookingList[i].expertName == experts[e].username) {
                                expertSales += bookingList[i].amount + 100; // base + service charge
                            }
                        }
                        cout << "Expert " << experts[e].username << "\t: RM" << expertSales << endl;
                        totalSales += expertSales;
                    }

                    cout << "------------------------------------" << endl;
                    cout << "TOTAL SALES" << string(13, ' ') << ": RM" << totalSales << "\n" << endl;
                    cout << "Press [ENTER] to return to Admin Menu.....";
                    clearInputBuffer();
                    cin.get();
                    system("CLS");
                    break;
                }
                case 4:
                    exitSalesReport = true;
                    system("CLS");
                    break;
                }
            } while (!exitSalesReport);
            break;
        }
        case 5:
            system("CLS");
            Expert_bonus(experts, count, bookingList, bookingCount);
            cout << "\nPress [ENTER] to return to Admin Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 6:
            exitMenu = true;
            system("CLS");
            break;
        }
    } while (!exitMenu);
}
