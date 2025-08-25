#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
#include "mainheader.h"
using namespace std;



string dayNames[DAYS] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

// ================== Helper Functions ==================

// Initialize all slots as FREE
void InitSchedules(ExpertInfo experts[], int count) {
    for (int e = 0; e < count; e++) {
        for (int w = 0; w < WEEKS; w++) {
            for (int s = 0; s < TOTAL_SLOTS_WEEK; s++) {
                experts[e].slots[w][s] = "FREE";
            }
        }
    }
}

// Convert slot index to readable time (slot-of-day only)
string SlotTime(int s) {
    int hour = 9 + s; // slots start at 9am
    string ampm = (hour >= 12) ? "pm" : "am";
    int displayHour = (hour > 12) ? hour - 12 : hour;
    return to_string(displayHour) + ampm;
}

// ================== Schedule Display ==================

// Show all experts’ schedules
void ShowAllSchedules(ExpertInfo experts[], int count) {
    cout << "\n===== General December Schedule =====\n"; 
    for (int w = 0; w < WEEKS; w++) {
        cout << "\n----------- Week " << (w + 1) << " -----------\n"; 
        for (int d = 0; d < DAYS; d++) {
            cout << "\n" << dayNames[d] << ":\n"; // Header row 
            cout << left << setw(10) << "Time"; 
            for (int e = 0; e < count; e++) {
                cout << setw(15) << experts[e].username;
            } 
            cout << "\n" << string(10 + 15 * 3, '-') << "\n"; // Slot rows 
            for (int t = 0; t < SLOTS_PER_DAY; t++) { 
                int index = d * SLOTS_PER_DAY + t; 
                cout << left << setw(10) << SlotTime(t); 
                for (int e = 0; e < count; e++) {
                    cout << setw(15) << experts[e].slots[w][index]; }
                cout << "\n"; 
            } 
        } 
    } 
}

// ===== Show one expert’s schedule in a table format =====
void ShowExpertSchedule(ExpertInfo experts[], int count, int expertIndex) {
    cout << "\n===== Schedule for " << experts[expertIndex].username << " =====\n";

    for (int w = 0; w < WEEKS; w++) {
        cout << "\n" << string(42, '=') << " Week " << (w + 1) << " " << string(42, '=') << endl;

        // Header row: days
        cout << left << setw(8) << "Time";
        for (int d = 0; d < DAYS; d++) {
            cout << setw(12) << dayNames[d];
        }
        cout << "\n" << string(8 + 12 * DAYS, '-') << "\n";

        // Rows: each time slot across the week
        for (int t = 0; t < SLOTS_PER_DAY; t++) {
            cout << left << setw(8) << SlotTime(t);

            for (int d = 0; d < DAYS; d++) {
                int index = d * SLOTS_PER_DAY + t;
                cout << setw(12) << experts[expertIndex].slots[w][index];
            }
            cout << "\n";
        }
    }
}

// ================== Expert Login & Menu ==================
void Expert(ExpertInfo experts[], int count) {
    string username, password;

    clearInputBuffer();

    cout << "===== CHROMANAILS STUDIO EXPERT MENU =====\n";

    int loggedExpert = -1;

    // ===== Login Loop =====
    while (true) {
        cout << "Enter Username: ";
        getline(cin, username);

        // Uppercase for comparison
        transform(username.begin(), username.end(), username.begin(), ::toupper);

        // Check against experts
        loggedExpert = -1;
        for (int i = 0; i < 3; i++) {
            if (username == experts[i].username) {
                loggedExpert = i;
                break;
            }
        }

        if (loggedExpert == -1) {
            cout << "\n[ERROR] Expert not found. Please try again.\n";
            continue;
        }

        cout << "Password: ";
        getline(cin, password);

        if (password == experts[loggedExpert].password) {
            break; // success
        } else {
            cout << "\n[ERROR] Invalid password. Please try again.\n";
        }
    }

    system("CLS");

    // ===== Expert Menu =====
    int option;
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "Welcome, Expert " << experts[loggedExpert].username << "!" << endl;
        cout << "What would you like to do today?" << endl;
        cout << "1. View Individual Schedule\n";    
        cout << "2. View Assigned Customer List\n";
        cout << "3. View Earnings Bonus Entitlement\n";
        cout << "4. Exit to Main Menu\n\n";
        cout << "Selection: ";

        if (!(cin >> option)) {
            cin.clear();
			clearInputBuffer();
            cout << "\n[ERROR] Invalid input. Please enter a number.\n";
            continue;
        }
        clearInputBuffer(); // clean newline after numeric input

        switch (option) {
            case 1: 
                ShowExpertSchedule(experts, count, loggedExpert);
                cout << "\nPress [ENTER] to return to Expert Menu.....";
                clearInputBuffer();
                system("CLS");
                break;
            case 2: 
                cout << "[TODO] View Assigned Customer List\n"; 
                break;
            case 3: 
                cout << "[TODO] View Earnings Bonus Entitlement\n"; 
                break;
            case 4: 
                exitMenu = true; 
                system("CLS");
                break;
            default: 
                cout << "[ERROR] Invalid Selection!\n";
                break;
        }
    }
}
