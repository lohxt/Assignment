#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
#include "mainheader.h"
using namespace std;

// Define global data
ExpertInfo experts[3] = {
    {"JOSHUA LOKE", "123", {}},
    {"JOSEPH LEE", "123", {}},
    {"CHAN KUM LONG", "123", {}}
};

// Day names (global)
std::string dayNames[DAYS] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

// ===== Helper: Initialize all slots as FREE =====
void InitSchedules() {
    for (int e = 0; e < 3; e++) {
        for (int w = 0; w < WEEKS; w++) {
            for (int s = 0; s < TOTAL_SLOTS_WEEK; s++) {
                experts[e].slots[w][s] = "FREE";
            }
        }
    }
}

// ===== Helper: Convert slot index to readable time (slot-of-day only) =====
string SlotTime(int s) {
    // s is 0..7 for 9am..4pm
    int hour = 9 + s;
    string ampm = (hour >= 12) ? "pm" : "am";
    int displayHour = (hour > 12) ? hour - 12 : hour;
    return to_string(displayHour) + ampm;
}

 //===== Show all experts’ schedules =====
void ShowAllSchedules() {
    cout << "\n=== General December Schedule ===\n";
    for (int w = 0; w < WEEKS; w++) {
        cout << "\nWeek " << w + 1 << ":\n";
        for (int d = 0; d < DAYS; d++) {
            cout << "\n" << dayNames[d] << ":\n";
            cout << setw(8) << "Time";
            for (int e = 0; e < 3; e++) {
                cout << setw(15) << experts[e].username;
            }
            cout << "\n";

            for (int t = 0; t < SLOTS_PER_DAY; t++) {
                cout << setw(8) << SlotTime(t);
                int index = d * SLOTS_PER_DAY + t; // map day+time to flat index (0..55)
                for (int e = 0; e < 3; e++) {
                    cout << setw(15) << experts[e].slots[w][index];
                }
                cout << "\n";
            }
        }
    }
}

// ===== Show one expert’s schedule (uses flattened mapping) =====
void ShowExpertSchedule(int expertIndex) {
    cout << "\n=== Schedule for " << experts[expertIndex].username << " ===\n";
    for (int w = 0; w < WEEKS; w++) {
        cout << "\nWeek " << w + 1 << ":\n";
        for (int d = 0; d < DAYS; d++) {
            cout << "\n" << dayNames[d] << ":\n";
            cout << setw(8) << "Time" << setw(15) << "Status\n";
            for (int t = 0; t < SLOTS_PER_DAY; t++) {
                int index = d * SLOTS_PER_DAY + t;
                cout << setw(8) << SlotTime(t)
                     << setw(15) << experts[expertIndex].slots[w][index] << "\n";
            }
        }
    }
}

// ===== Expert login & schedule view =====
void Expert() {
    string username;
    string password;

    clearInputBuffer();

    cout << "===== CHROMANAILS STUDIO EXPERT MENU =====\n";
    
    int loggedExpert = -1;
    while (true) {
        cout << "Enter Username: ";
        getline(cin, username);

        // uppercase the input for comparison
        for (char &c : username) c = toupper(static_cast<unsigned char>(c));

        // find matching expert
        loggedExpert = -1;
        for (int i = 0; i < 3; i++) {
            if (username == experts[i].username) {
                loggedExpert = i;
                break;
            }
        }

        if (loggedExpert == -1) {
            cout << "\nExpert Unidentified. Please Try Again\n";
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

    int option;
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "Welcome, Expert " << username << "!\n";
        cout << "What would you like to do today?" << endl;
        cout << "1. View Individual Schedule\n";
        cout << "2. View Assigned Customer List\n";
        cout << "3. View Earnings Bonus Entitlement\n";
        cout << "4. Exit to Main Menu\n" << endl;
        cout << "Selection: ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean newline after numeric input

        if (option == 1) {
            ShowExpertSchedule(loggedExpert);
        }
        else if (option == 2) {
            // TODO: implement
        }
        else if (option == 3) {
            // TODO: implement
        }
        else if (option == 4) {
            exitMenu = true;
            system("CLS");
        }
        else {
            cout << "[ERROR] Invalid Selection!\n";
        }
    }
}

    /*cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    cin >> password;

    for (int i = 0; i < 3; i++) {
        if (username == experts[i].username && password == experts[i].password) {
            cout << "\n[OK] Login successful!\n";
            ShowExpertSchedule(i);
            return;
        }
    }
    cout << "\n[ERROR] Invalid username or password.\n";
}*/
