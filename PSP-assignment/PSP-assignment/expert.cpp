#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include "mainheader.h"
using namespace std;

string dayNames[DAYS] = {"Mon", "Tue", "Wed", "Thu", "Fri"};

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
    cout << "\n===== General December Schedule =====\n"; 
    // Add session notes
    cout << "\n[NOTE] Slot durations by service:\n";
	cout << "All services are 3 hours per session: 9am-12pm, 12pm-3pm\n";

    for (int w = 0; w < WEEKS; w++) {
        cout << "\n----------- Week " << (w + 1) << " -----------\n"; 
        for (int d = 0; d < DAYS; d++) {
            cout << "\n" << dayNames[d] << ":\n"; // Header row 
            cout << left << setw(10) << "Time"; 
            for (int e = 0; e < count; e++) {
                cout << setw(15) << experts[e].username;
            } 
            cout << "\n" << string(10 + 15 * 3, '-') << "\n"; // Slot rows 
    
            for (int t = 0; t < 2; t++) {  // only slots 0..5 = 9am–3pm
                int index = d * SLOTS_PER_DAY + (t * 3);
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
    cout << "\n===== Schedule for " << experts[expertIndex].username << " =====\n";

    for (int w = 0; w < WEEKS; w++) {
        cout << "\n" << string(42, '=') << " Week " << (w + 1) << " " << string(42, '=') << endl;

        // Header row: days
        cout << left << setw(12) << "Time";
        for (int d = 0; d < DAYS; d++) {
            cout << setw(12) << dayNames[d];
        }
        cout << "\n" << string(12 + 12 * DAYS, '-') << "\n";

        // Rows: each time slot across the week
        for (int t = 0; t < 2; t++) {  // only 2 slots (9-12, 12-3)
            string timeLabel = (t == 0) ? "9am-12pm" : "12pm-3pm";

            cout << left << setw(12) << timeLabel;
            for (int d = 0; d < DAYS; d++) {
                int index = d * SLOTS_PER_DAY + (t * 3);
                cout << setw(12) << experts[expertIndex].slots[w][index];
            }
            cout << "\n";
        }
        cout << "(Note: All services are 3-hour sessions: 9am-12pm, 12am-3pm)\n";
    }
}

// ================== Expert Login & Menu ==================
void Expert(ExpertInfo experts[], int count) {
    string username, password;

    clearInputBuffer();

    cout << "===== CHROMANAILS STUDIO EXPERT MENU =====\n";

    int loggedExpert = -1;
    bool loggedIn = false;
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
    } while (!exitMenu);
}
