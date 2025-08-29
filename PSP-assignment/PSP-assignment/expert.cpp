#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include "mainheader.h"
using namespace std;



string dayNames[DAYS] = {"Mon", "Tue", "Wed", "Thu", "Fri"};

// ================== Helper Functions ==================

// Initialize all slots with working rules
void InitSchedules(ExpertInfo experts[], int count) {
    // Each expert's valid slot start times (relative to 9am base)
    // Nail Care -> 3 * 2hr
    // Pedi/Mani -> 6 * 1hr
    // Acrylic -> 3 * 2hr
    const int expertSlotCounts[3] = { 3, 6, 3 };
    const int expertSlotStartTimes[3][6] = {
        {0, 2, 4},                 // Nail Care: 9–11, 11–1, 1–3
        {0, 1, 2, 3, 4, 5},        // Pedi/Mani: 9–10, … , 2–3
        {0, 2, 4}                  // Acrylic: 9–11, 11–1, 1–3
    };

    for (int e = 0; e < count; e++) {
        for (int w = 0; w < WEEKS; w++) {
            int totalHoursThisWeek = 0;

            for (int d = 0; d < DAYS; d++) {
                for (int t = 0; t < SLOTS_PER_DAY; t++) {
                    int index = d * SLOTS_PER_DAY + t;

                    // Weekends = not available
                    if (d >= 5) {
                        experts[e].slots[w][index] = "N/A";
                        continue;
                    }

                    // Any time after 3pm = not available
                    if (t >= 6) { // slot 6 = 3–4pm
                        experts[e].slots[w][index] = "N/A";
                        continue;
                    }

                    // Weekly max reached?
                    if (totalHoursThisWeek >= 30) {
                        experts[e].slots[w][index] = "N/A";
                        continue;
                    }

                    // Check if this slot belongs to expert’s valid schedule
                    bool valid = false;
                    for (int s = 0; s < expertSlotCounts[e]; s++) {
                        if (t == expertSlotStartTimes[e][s]) {
                            valid = true;
                            break;
                        }
                    }

                    if (valid) {
                        // Nail Care + Acrylic = 2 hrs, Pedi/Mani = 1 hr
                        int hours = (e == 1) ? 1 : 2;

                        if (totalHoursThisWeek + hours <= 30) {
                            experts[e].slots[w][index] = "FREE";
                            totalHoursThisWeek += hours;
                        }
                        else {
                            experts[e].slots[w][index] = "N/A";
                        }
                    }
                    else {
                        experts[e].slots[w][index] = "N/A";
                    }
                }
            }
        }
    }
}


// Convert slot index to readable time (slot-of-day only)
string SlotTime(int expertIndex, int t) {
    if (expertIndex == 1) {
        // Expert 2 -> Pedicure/Manicure = 1 hr slots
        int hour = 9 + t;
        string ampm = (hour >= 12) ? "pm" : "am";
        int displayHour = (hour > 12) ? hour - 12 : hour;
        return to_string(displayHour) + ampm + "-" + to_string(displayHour + 1) + ampm;
    }
    else {
        // Expert 1 & 3 -> Nail Care / Acrylic = 2 hr slots (9–11, 11–1, 1–3)
        if (t == 0) return "9am-11am";
        if (t == 2) return "11am-1pm";
        if (t == 4) return "1pm-3pm";
        return "";
    }
}

// ================== Schedule Display ==================

// Show all experts’ schedules
void ShowAllSchedules(ExpertInfo experts[], int count) {
    cout << "\n===== General December Schedule =====\n"; 
    // Add session notes
    cout << "\n[NOTE] Slot durations by service:\n";
    cout << " - Nail Care: 2 hours (9–11, 11–1, 1–3)\n";
    cout << " - Pedicure & Manicure: 1 hour (9–10, 10–11, … , 2–3)\n";
    cout << " - Acrylic Nails: 2 hours (9–11, 11–1, 1–3)\n";
    for (int w = 0; w < WEEKS; w++) {
        cout << "\n----------- Week " << (w + 1) << " -----------\n"; 
        for (int d = 0; d < DAYS; d++) {
            cout << "\n" << dayNames[d] << ":\n"; // Header row 
            cout << left << setw(10) << "Time"; 
            for (int e = 0; e < count; e++) {
                cout << setw(15) << experts[e].username;
            } 
            cout << "\n" << string(10 + 15 * 3, '-') << "\n"; // Slot rows 
            for (int t = 0; t < 6; t++) {  // only slots 0..5 = 9am–3pm
                int index = d * SLOTS_PER_DAY + t;

                // Always use 1-hour slot labels for the global view (so all experts align)
                int hour = 9 + t;
                string ampm1 = (hour >= 12) ? "pm" : "am";
                string ampm2 = ((hour + 1) >= 12) ? "pm" : "am";
                int displayHour1 = (hour > 12) ? hour - 12 : hour;
                int displayHour2 = ((hour + 1) > 12) ? (hour + 1) - 12 : (hour + 1);
                string timeLabel = to_string(displayHour1) + ampm1 + "-" +
                    to_string(displayHour2) + ampm2;

                cout << left << setw(10) << timeLabel;

                for (int e = 0; e < count; e++) {
                    cout << setw(15) << experts[e].slots[w][index];
                }
                cout << "\n\n";
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
        for (int t = 0; t < 6; t++) {  // only 9am–3pm
            // Always show 1-hour labels for alignment
            int hour = 9 + t;
            string ampm1 = (hour >= 12) ? "pm" : "am";
            string ampm2 = ((hour + 1) >= 12) ? "pm" : "am";
            int displayHour1 = (hour > 12) ? hour - 12 : hour;
            int displayHour2 = ((hour + 1) > 12) ? (hour + 1) - 12 : (hour + 1);
            string timeLabel = to_string(displayHour1) + ampm1 + "-" +
                to_string(displayHour2) + ampm2;

            cout << left << setw(12) << timeLabel;

            for (int d = 0; d < DAYS; d++) {
                int index = d * SLOTS_PER_DAY + t;
                cout << setw(12) << experts[expertIndex].slots[w][index];
            }
            cout << "\n";
        }            // Add session note per expert
        if (expertIndex == 0)
            cout << "(Note: Nail Care sessions are 2 hours each: 9-11, 11-1, 1-3)\n";
        else if (expertIndex == 1)
            cout << "(Note: Pedicure & Manicure sessions are 1 hour each: 9-10 … 2-3)\n";
        else if (expertIndex == 2)
            cout << "(Note: Acrylic Nails sessions are 2 hours each: 9-11, 11-1, 1-3)\n";
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
