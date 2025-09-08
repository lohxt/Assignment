#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "mainheader.h"
using namespace std;

const char* getDayName(Day day) {
    switch (day) {
    case MON: return "Mon";
    case TUE: return "Tue";
    case WED: return "Wed";
    case THU: return "Thu";
    case FRI: return "Fri";
    default:  return "N/A";
    }
}

// --- Save bookings to text file (overwrite) ---
void savebookingstofile(Booking bookingList[], int bookingCount) {
    ofstream outfile("bookings.txt");
    if (!outfile) {
        cout << "[ERROR] Unable to open file.\n";
        return;
    }

    for (int i = 0; i < bookingCount; ++i) {
        // Fields separated by '|', one booking per line
        outfile << bookingList[i].customerName << '|'
            << bookingList[i].expertName << '|'
            << bookingList[i].service << '|'
            << bookingList[i].week << '|'
            << static_cast<int>(bookingList[i].day) << '|'
            << bookingList[i].slot << '|'
            << bookingList[i].amount << '|'
            << (bookingList[i].done ? 1 : 0) << '\n';
    }
    outfile.close();
}

// --- Load bookings from text file, return count ---
int loadbookingsfromfile(Booking bookingList[], int maxSize) {
    ifstream infile("bookings.txt");
    if (!infile) {
        return 0; // no file means no bookings
    }

    int count = 0;
    while (count < maxSize) {
        // Read customerName up to '|'
        if (!getline(infile, bookingList[count].customerName, '|')) break;
        if (!getline(infile, bookingList[count].expertName, '|')) break;
        if (!getline(infile, bookingList[count].service, '|')) break;

        int week, dayInt, slot, doneInt;
        double amount;

        if (!(infile >> week)) break;
        infile.ignore(1, '|');

        if (!(infile >> dayInt)) break;
        infile.ignore(1, '|');

        if (!(infile >> slot)) break;
        infile.ignore(1, '|');

        if (!(infile >> amount)) break;
        infile.ignore(1, '|');

        if (!(infile >> doneInt)) break;
        infile.ignore(1000, '\n'); // skip to end of line

        bookingList[count].week = week;
        bookingList[count].day = static_cast<Day>(dayInt);
        bookingList[count].slot = slot;
        bookingList[count].amount = amount;
        bookingList[count].done = false; // Reset status each startup

        ++count;
    }

    infile.close();
    return count;
}

int main() {
    int role;
    bool exitProgram = false;

    // Experts (initial usernames)
    ExpertInfo experts[3] = {
        {"JOSHUA LOKE", "123"},
        {"JOSEPH LEE",  "123"},
        {"CHAN KUM LONG","123"}
    };

    Booking bookingList[MAX_BOOKINGS];
    int bookingCount = 0;

    // Initialize schedules first
    InitSchedules(experts, 3);

    // Load bookings from file (if any) and mark loaded bookings into schedules
    bookingCount = loadbookingsfromfile(bookingList, MAX_BOOKINGS);
    //bookingCount = 0;

    for (int i = 0; i < bookingCount; ++i) {
        // find expert index by name
        int expertIndex = -1;
        for (int e = 0; e < 3; ++e) {
            if (bookingList[i].expertName == experts[e].username) {
                expertIndex = e;
                break;
            }
        }
        if (expertIndex == -1) continue; // unknown expert in file

        int w = bookingList[i].week - 1;                  // stored weeks are 1-based
        int dayInt = static_cast<int>(bookingList[i].day); // enum -> int
        int slot0 = bookingList[i].slot - 1;              // stored slot is 1-based
        if (w < 0 || w >= WEEKS) continue;
        int index = dayInt * SLOTS_PER_DAY + slot0;
        if (index >= 0 && index < DAYS * SLOTS_PER_DAY) {
            experts[expertIndex].slots[w][index] = "BOOKED";
        }
    }

    // Main menu loop (unchanged logic)
    do {
        cout << "===== CHROMANAILS STUDIO BOOKING SYSTEM =====\n" << endl;
        cout << "WELCOME TO CHROMANAILS STUDIO'S BOOKING SYSTEM!" << endl;
        cout << "Please select the following options below:\n" << endl;
        cout << "If you are an Admin, Choose 1\n"
            << "If you are an Expert, Choose 2\n"
            << "If you are a Customer, Choose 3\n"
            << "To exit the program, Choose 4\n" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Expert" << endl;
        cout << "3. Customer" << endl;
        cout << "4. Exit System" << endl;
        cout << "\nSelection: ";
        cin >> role;

        while ((role < 1 || role > 4) || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[ERROR] Invalid Selection! Please Choose (1-4) Only." << endl;
            cout << "\nSelection: ";
            cin >> role;
        }

        switch (role) {
        case 1:
            cout << "\n";
            admin(experts, 3, bookingList, bookingCount);
            // if admin modified bookings (e.g. marked done), save:
            savebookingstofile(bookingList, bookingCount);
            break;
        case 2:
            cout << "\n";
            Expert(experts, 3, bookingList, bookingCount);
            // experts may have marked bookings done; save:
            savebookingstofile(bookingList, bookingCount);
            break;
        case 3:
            cout << "\n";
            customer(experts, 3, bookingList, bookingCount);
            // customers may have added bookings; save:
            savebookingstofile(bookingList, bookingCount);
            break;
        case 4:
            exitProgram = true;
            system("CLS");
            break;
        }
    } while (!exitProgram);

    cout << "THANK YOU FOR USING CHROMANAILS STUDIO'S BOOKING SYSTEM! PLEASE COME AGAIN SOON!" << endl;
    return 0;
}
