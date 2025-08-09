#include <iostream>
#include <iomanip>
#include "header.h"
using namespace std;

// Define global data
ExpertInfo experts[3] = {
    {"Low Zihao", "123", {}},
    {"Lim Shi Ming", "123", {}},
    {"Chan Kum Long", "123", {}}
};

// ===== Helper: Initialize all slots as FREE =====
void InitSchedules() {
    for (int e = 0; e < 3; e++) {
        for (int w = 0; w < WEEKS; w++) {
            for (int s = 0; s < SLOTS_PER_DAY; s++) {
                experts[e].slots[w][s] = "FREE";
            }
        }
    }
}

// ===== Helper: Convert slot index to readable time =====
string SlotTime(int s) {
    int hour = 9 + s;
    string ampm = (hour >= 12) ? "pm" : "am";
    int displayHour = (hour > 12) ? hour - 12 : hour;
    return to_string(displayHour) + ampm;
}

// ===== Show all experts’ schedules =====
void ShowAllSchedules() {
    cout << "\n=== General December Schedule ===\n";
    for (int w = 0; w < WEEKS; w++) {
        cout << "\nWeek " << w + 1 << ":\n";
        cout << setw(8) << "Time";
        for (int e = 0; e < 3; e++) {
            cout << setw(15) << experts[e].username;
        }
        cout << "\n";

        for (int s = 0; s < SLOTS_PER_DAY; s++) {
            cout << setw(8) << SlotTime(s);
            for (int e = 0; e < 3; e++) {
                cout << setw(15) << experts[e].slots[w][s];
            }
            cout << "\n";
        }
    }
}

// ===== Show one expert’s schedule =====
void ShowExpertSchedule(int expertIndex) {
    cout << "\n=== Schedule for " << experts[expertIndex].username << " ===\n";
    for (int w = 0; w < WEEKS; w++) {
        cout << "\nWeek " << w + 1 << ":\n";
        cout << setw(8) << "Time" << setw(15) << "Status\n";
        for (int s = 0; s < SLOTS_PER_DAY; s++) {
            cout << setw(8) << SlotTime(s) << setw(15) << experts[expertIndex].slots[w][s] << "\n";
        }
    }
}

// ===== Expert login & schedule view =====
void Expert() {
    string username, password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
}
