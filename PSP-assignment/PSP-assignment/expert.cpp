#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include "mainheader.h"
using namespace std;

// ================== Helper Functions ==================

void InitSchedules(ExpertInfo experts[], int count) {
    const int sessionStarts[2] = { 0, 3 };
    const int sessionHours = 3;

    for (int e = 0; e < count; e++) {
        for (int w = 0; w < WEEKS; w++) {
            // Initialize all slots to "FREE"
            for (int d = 0; d < DAYS; d++) {
                for (int t = 0; t < SLOTS_PER_DAY; t++) {
                    int index = d * SLOTS_PER_DAY + t;
                    experts[e].slots[w][index] = "FREE";
                }
            }
        }
    }
}

// Convert slot index to readable time (slot-of-day only)
string SlotTime(int expertIndex, int t) {
    if (expertIndex == 1) {
        int hour = 9 + t;
        string ampm = (hour >= 12) ? "pm" : "am";
        int displayHour = (hour > 12) ? hour - 12 : hour;
        return to_string(displayHour) + ampm + "-" + to_string(displayHour + 1) + ampm;
    }
    else {
        // Experts 1 & 3 -> Nail Art/Acrylic = 3 hr slots
        if (t == 0) return "9am-12pm";
        if (t == 3) return "12pm-3pm";
        return "";
    }
}

// ================== Schedule Display ==================

// Show all experts’ schedules
void ShowAllSchedules(ExpertInfo experts[], int count) {
    cout << "===== General December Schedule =====\n";
    // Add session notes
    cout << "\n[NOTE] Slot durations by service:\n";
    cout << "All services are 3 hours per session: 9am-12pm, 12pm-3pm\n";

    for (int w = 0; w < WEEKS; w++) {
        cout << "\n" << string(23, '=') << " Week " << (w + 1) << " " << string(24, '=');
        for (int d = 0; d < DAYS; d++) {
<<<<<<< Updated upstream
            cout << "\n" << dayNames[d] << ":" << endl; // Header row 
=======
<<<<<<< HEAD
            cout << "\n" << getDayName((Day)d) << ":" << endl; // Header row 
=======
            cout << "\n" << dayNames[d] << ":" << endl; // Header row 
>>>>>>> 23eb588d4a58fefea13a0f8dd5d6cd8d6d8b768f
>>>>>>> Stashed changes
            cout << left << setw(10) << "Time";
            for (int e = 0; e < count; e++) {
                cout << setw(15) << experts[e].username;
            }
            cout << "\n" << string(10 + 15 * 3, '-') << "\n"; // Slot rows 

            for (int t = 0; t < 2; t++) {  // only slots 0..5 = 9am–3pm
                int index = d * SLOTS_PER_DAY + t;
                string timeLabel = (t == 0) ? "9am-12pm" : "12pm-3pm";    // prints 3-hour ranges
                cout << left << setw(10) << timeLabel;

                for (int e = 0; e < count; e++) {
                    cout << setw(15) << experts[e].slots[w][index];
                }
                cout << "\n";
            }
        }
    }
}

// ===== Show one expert’s schedule in a table format =====
void ShowExpertSchedule(ExpertInfo experts[], int count, int expertIndex) {
    cout << "===== Schedule for " << experts[expertIndex].username << " =====" << endl;

    for (int w = 0; w < WEEKS; w++) {
        cout << "\n" << string(32, '=') << " Week " << (w + 1) << " " << string(32, '=') << endl;

        // Header row: days
        cout << left << setw(12) << "Time";
        for (int d = 0; d < DAYS; d++) {
            cout << setw(12) << getDayName((Day)d);
        }
        cout << "\n" << string(12 + 12 * DAYS, '-') << "\n";

        // Rows: each time slot across the week
        for (int t = 0; t < 2; t++) {  // only 2 slots (9-12, 12-3)
            string timeLabel = (t == 0) ? "9am-12pm" : "12pm-3pm";

            cout << left << setw(12) << timeLabel;
            for (int d = 0; d < DAYS; d++) {
                int index = d * SLOTS_PER_DAY + t;
                cout << setw(12) << experts[expertIndex].slots[w][index];
            }
            cout << "\n";
        }
        cout << "(Note: All services are 3-hour sessions: 9am-12pm, 12am-3pm)\n";
    }
}

void ShowExpertCustomers(Booking bookingList[], int bookingCount, const string& expertName) {
    cout << string(10, '=') << " Customers of " << expertName << " " << string(10, '=') << "\n" << endl;

    int count = 0;
    for (int i = 0; i < bookingCount; i++) {
        if (bookingList[i].expertName == expertName) {
            count++;
            cout << "Customer : " << bookingList[i].customerName << endl;
            cout << "Service  : " << bookingList[i].service << endl;
            cout << "Week     : " << bookingList[i].week << endl;
<<<<<<< Updated upstream
            cout << "Day      : " << dayNames[bookingList[i].day] << endl;
=======
<<<<<<< HEAD
            cout << "Day      : " << getDayName((Day)bookingList[i].day) << endl;
=======
            cout << "Day      : " << dayNames[bookingList[i].day] << endl;
>>>>>>> 23eb588d4a58fefea13a0f8dd5d6cd8d6d8b768f
>>>>>>> Stashed changes
            cout << "Slot     : " << bookingList[i].slot << endl;
            cout << "Duration : 3 Hours" << endl;
            cout << fixed << setprecision(2);
            cout << "Amount   : RM" << bookingList[i].amount << " + RM100.00 (Service Charge)" << endl;
            cout << string(48, '-') << endl;
        }
    }

    if (count == 0) {
        cout << "[OOPS] No Customers Assigned Yet.\n";
    }
}

void ShowExpertBonus(string username, int count, Booking bookingList[], int bookingCount) {
    int hoursWorked = 0;
    double totalCharges = 0.0;
    double bonusRate = 0.0;
    double bonusEarned = 0.0;
    double SERVICE_CHARGE = 100.00;

    if (bookingCount == 0) {
        cout << "No Bookings Available. Cannot Calculate Bonuses.\n";
        return;
    }

    // Go through bookings to accumulate hours & value
    for (int i = 0; i < bookingCount; i++) {
        if (bookingList[i].expertName == username) {
            hoursWorked += 3; // Each slot is 3 hours
        }
    }

    if (hoursWorked < 25) {
        bonusRate = 0.0;
    }
    else if (hoursWorked < 30) {
        bonusRate = 0.25;
    }
    else if (hoursWorked >= 30) {
        bonusRate = 0.5;
    }

    system("CLS");
    totalCharges = SERVICE_CHARGE * hoursWorked / 3;
    bonusEarned = totalCharges * bonusRate;
    cout << "Expert " << username << " Bonus Report - December" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Total Hours Worked     : " << hoursWorked << " hrs" << endl;
    cout << fixed << setprecision(2);
    cout << "Total Service Charges  : RM" << totalCharges << endl;
    cout << "Bonus Percentage       : " << bonusRate * 100 << "%" << endl;
    cout << "Bonus Earned           : RM" << bonusEarned << endl;
}

// ================== Expert Login & Menu ==================
void Expert(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount) {
    string username, password;
    int loggedExpert = -1, hoursWorked;
    bool loggedIn = false;

    clearInputBuffer();

    cout << "===== CHROMANAILS STUDIO EXPERT MENU =====\n";
    // ===== Login Loop =====
    do {
        cout << "Enter Username: ";
        getline(cin, username);

        // Uppercase for comparison
        for (int i = 0; i < username.length(); i++) {
            username[i] = toupper(username[i]);
        }

        // Check against experts
        loggedExpert = -1;
        for (int i = 0; i < 3; i++) {
            if (username == experts[i].username) {
                loggedExpert = i;
                break;
            }
        }

        if (username.empty()) {
            cout << "\n[ERROR] Username cannot be empty! Please Try Again." << endl;
            continue;
        }

        if (loggedExpert == -1) {
            cout << "\n[ERROR] Unknown Expert! Please Try Again.\n";
            continue;
        }

        bool validPassword = false;
        do {
            cout << "Password: ";
            getline(cin, password);

            if (password.empty()) {
                cout << "\n[ERROR] Password cannot be empty! Please Try Again." << endl;
                continue;
            }

            if ((loggedExpert == 0 && (password == "JOSH123" || password == "josh123")) ||
                (loggedExpert == 1 && (password == "JOSEPH123" || password == "joseph123")) ||
                (loggedExpert == 2 && (password == "CKL123" || password == "ckl123"))) {
                validPassword = true;
                loggedIn = true;
                break;
            }
            else {
                cout << "\n[ERROR] Wrong Password! Please Try Again.\n";
            }
        } while (!validPassword);
    } while (!loggedIn);

    system("CLS");

    // ===== Expert Menu =====
    int option;
    bool exitMenu = false;

    do {
        cout << "Welcome, Expert " << experts[loggedExpert].username << "!" << endl;
        cout << "What would you like to do today?" << endl;
        cout << "1. View Individual Schedule" << endl;
        cout << "2. View Assigned Customer List" << endl;
        cout << "3. View Earnings Bonus Entitlement" << endl;
        cout << "4. Exit to Main Menu\n" << endl;
        cout << "Selection: ";
        cin >> option;

        while ((option < 1 || option > 4) || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[ERROR] Invalid Selection! Please Choose (1-4) Only." << endl;
            cout << "\nSelection: ";
            cin >> option;
        }

        switch (option) {
        case 1:
            system("CLS");
            ShowExpertSchedule(experts, count, loggedExpert);
            cout << "\nPress [ENTER] to return to Expert Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 2:
            system("CLS");
            ShowExpertCustomers(bookingList, bookingCount, experts[loggedExpert].username);
            cout << "\nPress [ENTER] to return to Expert Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 3:
            system("CLS");
            ShowExpertBonus(username, count, bookingList, bookingCount);
            cout << "\nPress [ENTER] to return to Expert Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 4:
            exitMenu = true;
            system("CLS");
            break;
        }
    } while (!exitMenu);
}