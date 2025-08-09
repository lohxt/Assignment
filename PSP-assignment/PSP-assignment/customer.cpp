#include <iostream>
#include <iomanip>
#include <string>
#include "header.h"
using namespace std;

void clearInputBuffer() {
    char c;
    while ((c = cin.get()) != '\n' && c != EOF) {
        // just discard characters
    }
}

void customer() {
    string username, password;
    int option;

    clearInputBuffer(); // clear any leftover newline

    cout << "\n===== CHROMANAILS STUDIO BOOKING SYSTEM =====\n";
    cout << "Enter Username: ";
    getline(cin, username);
    cout << "Password: ";
    cin >> password;

    cout << "\nWelcome, " << username << "!\n";
    cout << "1. View All Experts & Availability\n";
    cout << "2. Book Appointment\n";
    cout << "3. Exit to Menu\n";
    cout << "Selection: ";
    cin >> option;

    if (option == 1) {
        ShowAllSchedules();
    }
    else if (option == 2) {
        int expertChoice, weekChoice, slotChoice;
        ShowAllSchedules();

        cout << "\nChoose Expert (1-3): ";
        cin >> expertChoice;
        cout << "Choose Week (1-4): ";
        cin >> weekChoice;
        cout << "Choose Slot (1-8): ";
        cin >> slotChoice;

        expertChoice--; weekChoice--; slotChoice--;

        if (expertChoice >= 0 && expertChoice < 3 &&
            weekChoice >= 0 && weekChoice < WEEKS &&
            slotChoice >= 0 && slotChoice < SLOTS_PER_DAY) {

            if (experts[expertChoice].slots[weekChoice][slotChoice] == "FREE") {
                experts[expertChoice].slots[weekChoice][slotChoice] = "BOOKED";
                cout << "[OK] Booking confirmed!\n";
            }
            else {
                cout << "[ERROR] Slot already booked.\n";
            }
        }
        else {
            cout << "[ERROR] Invalid selection.\n";
        }
    }
}
