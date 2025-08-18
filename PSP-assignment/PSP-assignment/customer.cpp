#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include "mainheader.h"
using namespace std;

void clearInputBuffer() {
    char c;
    while ((c = cin.get()) != '\n' && c != EOF) {
        // Just discard characters, it helps such that username and password don' t get stuck together
    }
}

void customer() {
    char username[50];
    string password, expectedpw;
    bool validUsername = false;

    clearInputBuffer(); // Clear leftover newline
    
    cout << "===== CHROMANAILS STUDIO BOOKING SYSTEM =====\n";

    while (!validUsername) {
        cout << "Enter Username: ";
        cin.getline(username, 50);

        if (username[0] == '\0' || username[1] == '\0') {
            cout << "\n[ERROR] Username must contain only letters and spaces. Please Try Again." << endl;
            continue;
        }
        
        validUsername = true; // Assume valid until proven otherwise

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
            cout << "\n[ERROR] Wrong Password! Please Try Again." << endl;
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
        cout << "Welcome, " << username << "!\n";
        cout << "What would you like to do today?" << endl;
        cout << "1. View Information About ChromaNails Studio\n";
        cout << "2. View Services & Experts\n";
        cout << "3. View My Bookings\n";
        cout << "4. Exit to Main Menu\n" << endl;
        cout << "Selection: ";
        cin >> option;

        system("CLS");

        if (option == 1) {
            cout << "..." << endl;
        }
        else if (option == 2) {
            char choice, decision;
            cout << "Service: Nail Care & Art\n" << endl;
            cout << "Expert 1: JOSHUA LOKE" << endl;
            cout << "Specialization: Nail Art" << endl;
            cout << "Availability: Weekdays 8AM - 8PM" << endl;         //Subject to change
            cout << "Service Price: RM600\n" << endl;

            cout << "Expert 2: JOSEPH LEE" << endl;
            cout << "Specialization: Manicure & Pedicure" << endl;
            cout << "Availability: MON - SAT 10AM - 8PM" << endl;       //Subject to change
            cout << "Service Price: RM300 Each\n" << endl;

            cout << "Expert 3: CHAN KUM LONG" << endl;
            cout << "Specialization: Acrylic Nails" << endl;
            cout << "Availability: Weekends 10AM - 4PM" << endl;        //Subject to change
            cout << "Service Price: RM750\n" << endl;

            cout << "Do you want to check appointment availability? (Y/N): ";
            cin >> choice;

            switch (choice) {
            case 'Y':
            case 'y':
                ShowAllSchedules();
                cout << "\nDo you want to book an appointment? (Y/N): ";
                cin >> decision;

                switch (decision) {
                case 'Y':
                case 'y':
                    int expertChoice, weekChoice, slotChoice;

                    cout << "\nChoose Expert (1-3): ";
                    cin >> expertChoice;
                    cout << "Choose Week (1-4): ";
                    cin >> weekChoice;
                    cout << "Choose Slot (1-8): ";
                    cin >> slotChoice;
                    system("CLS");

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
                        cout << "[ERROR] Invalid Selection!\n";
                    }
                    break;
                case 'N':
                case 'n':
                    system("CLS");
                    break;
                default:
                    cout << "Enter Y/y/N/n. Please Try Again." << endl;
                }
                break;
            case 'N':
            case 'n':
                system("CLS");
                break;
            default:
                cout << "Enter Y/y/N/n. Please Try Again." << endl;
                break;
            }
        }
        else if (option == 3) {
           
        }
        else if (option == 4) {
            exitMenu = true; // Leave customer menu
            system("CLS");
        }
        else {
            cout << "[ERROR] Invalid Selection!\n";
        }
    }
}
