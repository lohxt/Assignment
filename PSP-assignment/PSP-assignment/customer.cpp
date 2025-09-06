#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include "mainheader.h"
using namespace std;

void clearInputBuffer() {
    char c;
    while ((c = cin.get()) != '\n' && c != EOF) {
        // Just discard characters, it helps such that username and password don't get stuck together
    }
}

int getValidatedInput(int min, int max, const string& prompt) {
    int input;

    while (true) {
        cout << prompt << " (" << min << "-" << max << "): ";
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[ERROR] Invalid Selection! Please Enter Digits Only.\n" << endl;
            continue;
        }

        if (input < min || input > max) {
            cout << "[ERROR] Invalid Selection! Please Try Again.\n" << endl;
            continue;
        }
        return input;
    }
}

bool processPayment(double amount, string service) {
    string cardNumber, cvv, expiry, confirmCheck;
    char confirmValid;
    const double SERVICE_CHARGE = 100.00;
    double total;

    cout << "=== Payment Gateway ===" << endl;
    cout << "Service\t: " << service << endl;
    cout << fixed << setprecision(2);
    cout << "Amount to Pay: RM" << amount << " (Service Price) + " << "RM" << SERVICE_CHARGE << " (Service Charge)" << endl;
    total = amount + SERVICE_CHARGE;
    cout << "Total Payment: RM" << total << endl;

    // Validate Card Number
    while (true) {
        cout << "Enter Card Number (16 digits): ";
        cin >> cardNumber;

        bool validCard = (cardNumber.length() == 16);
        if (validCard) {
            for (int i = 0; i < 16; ++i) {
                if (!isdigit(cardNumber[i])) { validCard = false; break; }
            }
        }

        if (validCard) break;

        cout << "[ERROR] Invalid Card Number! Please enter exactly 16 digits.\n" << endl;
    }

    // Validate Expiry Date
    while (true) {
        cout << "Enter Expiry Date (MM/YY): ";
        cin >> expiry;

        // Check format first
        if (expiry.length() == 5 &&
            isdigit(expiry[0]) && isdigit(expiry[1]) &&
            expiry[2] == '/' &&
            isdigit(expiry[3]) && isdigit(expiry[4]))
        {
            // Extract month
            string monthStr = expiry.substr(0, 2);
            int month = stoi(monthStr);

            // Handle invalid months first
            if (month <= 0 || month > 12) {
                cout << "[ERROR] Invalid month in Expiry Date! Must be between 01 - 12.\n" << endl;
            }
            else {
                break;  //Valid expiry date 
            }
        }
        else {
            cout << "[ERROR] Invalid Expiry Date! Format must be MM/YY.\n" << endl;
        }
    }

    // Validate CVV
    while (true) {
        cout << "Enter CVV (3 digits): ";
        cin >> cvv;

        bool validCVV = (cvv.length() == 3);
        if (validCVV) {
            for (int i = 0; i < 3; ++i) {
                if (!isdigit(cvv[i])) { validCVV = false; break; }
            }
        }

        if (validCVV) break;

        cout << "[ERROR] Invalid CVV! Please enter exactly 3 digits.\n" << endl;
    }

    // Confirm Payment
    while (true) {
        cout << "\nConfirm Payment? (Y/N): ";
        cin >> confirmCheck;

        if (confirmCheck.length() == 1) {
            confirmValid = confirmCheck[0];
            if (confirmValid == 'Y' || confirmValid == 'y') {
                cout << "\n[OK] Payment Successful!" << endl;
                return true;
            }
            else if (confirmValid == 'N' || confirmValid == 'n') {
                cout << "\n[OOPS] Payment Cancelled!" << endl;
                return false;
            }
            else {
                cout << "[ERROR] Invalid Selection! Please Enter (Y/y/N/n) Only." << endl;
            }
        }
        else {
            cout << "[ERROR] Invalid Selection! Please Enter (Y/y/N/n) Only." << endl;
        }
    }
}

string getExpertName(int serviceChoice) {
    switch (serviceChoice) {
    case 0: 
        return "JOSHUA LOKE";     // Nail Art
    case 1: 
        return "JOSEPH LEE";      // Pedicure & Manicure
    case 2: 
        return "CHAN KUM LONG";   // Acrylic Nails
    default: 
        return "Unknown Expert";
    }
}

void addBooking(Booking bookingList[], int& bookingCount,
    const string& customerName,
    const string& expertName,
    const string& service,
    int week, Day day, int slot, double amount)
{
    if (bookingCount < MAX_BOOKINGS) {
        bookingList[bookingCount].customerName = customerName; // Store Customer Name
        bookingList[bookingCount].expertName = expertName;     // Store Expert Name
        bookingList[bookingCount].service = service;           // Store Service Name
        bookingList[bookingCount].week = week;                 // Store The Week Chosen
        bookingList[bookingCount].day = day;                   // Store The Day Chosen
        bookingList[bookingCount].slot = slot;                 // Store The Slot Chosen (3hrs)
        bookingList[bookingCount].amount = amount;             // Store The Amount of Money Paid
        bookingCount++;
    }
    else {
        cout << "[ERROR] Booking list is full!" << endl;
    }
}

void showBookings(ExpertInfo experts[], int expertCount, Booking bookingList[], int& bookingCount, const string& currentUser) {
    cout << string(17, '=') << " My Bookings " << string(17, '=') << endl;

    int customerIndices[100]; // assume max 100 bookings per customer
    int customerCount = 0;

    // Display customer bookings
    for (int i = 0; i < bookingCount; i++) {
        if (bookingList[i].customerName == currentUser) {
            customerIndices[customerCount] = i;
            customerCount++;

            cout << "\n[" << customerCount << "] Booking ID #" << i + 1 << endl;
            cout << "Expert  : " << bookingList[i].expertName << endl;
            cout << "Service : " << bookingList[i].service << endl;
            cout << "Week    : " << bookingList[i].week << endl;
            cout << "Day     : " << getDayName((Day)bookingList[i].day) << endl;
            cout << "Slot    : " << bookingList[i].slot << endl;
            cout << fixed << setprecision(2);
            cout << "Amount  : RM" << bookingList[i].amount << " + RM100.00 (Service Charge)" << endl;
            cout << string(47, '-') << endl;
        }
    }

    if (customerCount == 0) {
        cout << "\nNo Bookings Found For " << currentUser << "." << endl;
        return;
    }

    string cancelChoice;
    do {
        cout << "\nDo you want to cancel a booking? (Y/N): ";
        cin >> cancelChoice;

        if (cancelChoice.length() == 1) {
            if (cancelChoice[0] == 'Y' || cancelChoice[0] == 'y') {
                int choice = getValidatedInput(1, customerCount, "Select Booking to Cancel");
                int bookingIndex = customerIndices[choice - 1];

                // Find expert index
                int expertIndex = -1;
                for (int i = 0; i < expertCount; i++) {
                    if (experts[i].username == bookingList[bookingIndex].expertName) {
                        expertIndex = i;
                        break;
                    }
                }

                if (expertIndex != -1) {
                    // Free old slot first
                    int oldWeek = bookingList[bookingIndex].week - 1;
                    int oldDay = (int)bookingList[bookingIndex].day;
                    int oldSlot = bookingList[bookingIndex].slot - 1;
                    int oldIndex = oldDay * SLOTS_PER_DAY + oldSlot;
                    experts[expertIndex].slots[oldWeek][oldIndex] = "FREE";

                    // Ask if reschedule
                    string rescheduleChoice;
                    do {
                        cout << "\nDo you wish to reschedule this booking instead? (Y/N): ";
                        cin >> rescheduleChoice;
                        if (rescheduleChoice.length() == 1) {
                            if (rescheduleChoice[0] == 'Y' || rescheduleChoice[0] == 'y') {
                                system("CLS");
                                ShowExpertSchedule(experts, expertCount, expertIndex);
                                bool success = false;
                                while (!success) {
                                    cout << "\n--- Rescheduling ---" << endl;
                                    int newWeek = getValidatedInput(1, 4, "Choose New Week") - 1;
                                    int newDay = getValidatedInput(1, 5, "Choose New Day") - 1;
                                    int newSlot = getValidatedInput(1, 2, "Choose New Slot") - 1;
                                    int newIndex = newDay * SLOTS_PER_DAY + newSlot;

                                    if (experts[expertIndex].slots[newWeek][newIndex] == "FREE") {
                                        experts[expertIndex].slots[newWeek][newIndex] = "BOOKED";

                                        // Update booking
                                        bookingList[bookingIndex].week = newWeek + 1;
                                        bookingList[bookingIndex].day = (Day)newDay;
                                        bookingList[bookingIndex].slot = newSlot + 1;

                                        cout << "\n[OK] Booking Rescheduled Successfully!" << endl;
                                        success = true;
                                        break;
                                    }
                                    else {
                                        cout << "\n[OOPS] Slot Already Booked! Please Try Again." << endl;
                                        continue;
                                    }
                                } return;
                            }
                            else if (rescheduleChoice[0] == 'N' || rescheduleChoice[0] == 'n') {
                                // If no reschedule, remove booking completely
                                for (int i = bookingIndex; i < bookingCount - 1; i++) {
                                    bookingList[i] = bookingList[i + 1];
                                }
                                bookingCount--;

                                cout << "\n[OK] Booking Cancelled Successfully!" << endl;
                                break;
                            }
                        }
                        cout << "[ERROR] Invalid Selection! Please Enter (Y/y/N/n) Only." << endl;
                    } while (true);
                    return;
                }
            }
            else if (cancelChoice[0] == 'N' || cancelChoice[0] == 'n') {
                cout << "Returning Without Cancelling....." << endl;
                break;
            }
        }
        cout << "[ERROR] Invalid Selection! Please Enter (Y/y/N/n) Only." << endl;
    } while (true);
    return;
}

// ================== Customer Login & Menu ==================
void customer(ExpertInfo experts[], int count, Booking bookingList[], int& bookingCount) {
    char username[50];
    string password, expectedpw;
    bool validUsername = false, validPassword = false;

    string payment, service;
    string choice, decision, paymentchoice;

    clearInputBuffer(); // Clear leftover newline

    cout << "===== CHROMANAILS STUDIO BOOKING SYSTEM =====\n";

    do {
        cout << "Enter Username: ";
        cin.getline(username, 50);

        if (username[0] == '\0' || username [1] == '\0') {
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

    // ===== Customer Menu =====
    do {
        cout << "Welcome, " << username << "!" << endl;
        cout << "What would you like to do today?" << endl;
        cout << "1. View Information About ChromaNails Studio" << endl;
        cout << "2. View Services & Experts" << endl;
        cout << "3. View My Bookings" << endl;
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
            cout << string(80, '=') << endl;
            cout << right << setw(58) << "CHROMANAILS STUDIO - NAIL CARE & ART" << endl;
            cout << string(80, '=') << "\n" << endl;

            cout << "About Us:\n";
            cout << "At ChromaNails Studio, we turn nails into a canvas of beauty and creativity.\n";
            cout << "Whether you are after elegant simplicity, bold trends, or long-lasting styles,\n";
            cout << "our professional nail artists deliver precision and care.\n\n";

            cout << "Vision:\n";
            cout << "To be the go-to nail studio where beauty meets artistry,\n";
            cout << "inspiring confidence through creative nail designs and quality care.\n\n";

            cout << "Mission:\n";
            cout << "- Provide top-quality nail care and art with attention to detail.\n";
            cout << "- Ensure a relaxing, clean, and welcoming experience for all clients.\n";
            cout << "- Use safe, high-quality products for healthy and lasting results.\n";
            cout << "- Bring clients' ideas to life through innovative nail artistry.\n\n";

            cout << "Operating Hours:\n";
            cout << "Monday - Friday : 10:00 AM - 8:00 PM\n";
            cout << "Saturday - Sunday: 11:00 AM - 9:00 PM\n";
            cout << "Closed on Public Holidays\n\n";

            cout << "Contact Details:\n";
            cout << "Address : Lot 12, Glamour Street, City Center, Kuala Lumpur\n";
            cout << "Phone   : +60 12-345 6789\n";
            cout << "Email   : hello@chromanails.com\n";
            cout << "Website : www.chromanails.com\n";
            cout << "Instagram / Facebook: @ChromaNailsStudio\n\n";

            cout << "Available Categories of Services:\n";
            cout << "1. Nail Art" << endl;
            cout << "   - Hand-painted Designs\n";
            cout << "   - Gel Polish Art\n";
            cout << "   - Custom & Seasonal Themes\n";
            cout << "\n2. Manicure & Pedicure" << endl;
            cout << "   - Classic Manicure & Pedicure\n";
            cout << "   - Spa Treatment for Hands & Feet\n";
            cout << "\n3. Acrylic Nails" << endl;
            cout << "   - Full Set Acrylic Extensions\n";
            cout << "   - Acrylic Nail Refills\n";
            cout << "   - Acrylic Nail Art Add-ons\n";

            cout << "\nPress [ENTER] to return to Customer Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 2:
            system("CLS");
            cout << "Service: Nail Care & Art\n" << endl;
            cout << "Expert 1: JOSHUA LOKE" << endl;
            cout << "Specialization: Nail Art" << endl;
            cout << "Availability: Weekdays 9AM - 3PM" << endl;
            cout << "Service Price: RM600\n" << endl;

            cout << "Expert 2: JOSEPH LEE" << endl;
            cout << "Specialization: Manicure & Pedicure" << endl;
            cout << "Availability: Weekdays 9AM - 3PM" << endl;
            cout << "Service Price: RM300 Each\n" << endl;

            cout << "Expert 3: CHAN KUM LONG" << endl;
            cout << "Specialization: Acrylic Nails" << endl;
            cout << "Availability: Weekdays 9AM - 3PM" << endl;
            cout << "Service Price: RM750" << endl;

            do {
                cout << "\nDo you want to check appointment availability? (Y/N): ";
                cin >> choice;

                if (choice.length() != 1) {
                    cout << "[ERROR] Invalid Selection! Please Enter (Y/y/N/n) Only." << endl;
                    continue;
                }
                switch (choice[0]) {
                case 'Y':
                case 'y':
                    int serviceChoice, expertIndex;
                    serviceChoice = getValidatedInput(1, 3, "Choose Service");
                    expertIndex = serviceChoice - 1;
                    cout << "\n";
                    ShowExpertSchedule(experts, count, expertIndex);

                    do {
                        cout << "\nDo you want to book an appointment? (Y/N): ";
                        cin >> decision;

                        if (decision.length() != 1) {
                            cout << "[ERROR] Invalid Selection! Please Enter (Y/y/N/n) Only." << endl;
                            continue;
                        }
                        switch (decision[0]) {
                        case 'Y':
                        case 'y':
                            int weekChoice, dayChoice, slotChoice;

                            weekChoice = getValidatedInput(1, 4, "Choose Week");
                            dayChoice = getValidatedInput(1, 5, "Choose Day");
                            slotChoice = getValidatedInput(1, 2, "Choose Slot");

                            //Post-Decrement
                            serviceChoice--; weekChoice--; dayChoice--; slotChoice--;
                            while (true) {
                                int index = dayChoice * SLOTS_PER_DAY + slotChoice;
                                if (experts[serviceChoice].slots[weekChoice][index] == "FREE") {
                                    cout << "\nSlot is Available" << endl;

                                    double amount = 0.00;
                                    const double NAIL_ART_PRICE = 600.00;
                                    const double PEDI_MANICURE_PRICE = 300.00;
                                    const double ACRYLIC_PRICE = 750.00;
                                    switch (serviceChoice) {
                                    case 0:
                                        amount = NAIL_ART_PRICE;
                                        service = "Nail Art";
                                        break;
                                    case 1:
                                        int subChoice;
                                        do {
                                            cout << "\nSelect Specific Service:" << endl;
                                            cout << "1. Manicure (RM300)\n";
                                            cout << "2. Pedicure (RM300)\n";
                                            cout << "\nSelection: ";
                                            cin >> subChoice;

                                            if (cin.fail() || (subChoice != 1 && subChoice != 2)) {
                                                cin.clear();
                                                cin.ignore(1000, '\n');
                                                cout << "[ERROR] Invalid Selection! Please Enter 1 or 2." << endl;
                                                continue;
                                            }

                                            if (subChoice == 1) {
                                                amount = PEDI_MANICURE_PRICE;
                                                service = "Manicure";
                                            }
                                            else {
                                                amount = PEDI_MANICURE_PRICE;
                                                service = "Pedicure";
                                            }
                                            break;
                                        } while (true);
                                        break;
                                    case 2:
                                        amount = ACRYLIC_PRICE;
                                        service = "Acrylic Nails";
                                        break;
                                    }

                                    cout << "You have selected the service: " << service << endl;
                                    cout << "The amount to be payed is RM" << amount << endl;
                                    cout << "Proceed with payment to confirm booking? (Y/N): ";
                                    cin >> paymentchoice;

                                    if (paymentchoice.length() == 1) {
                                        if (paymentchoice[0] == 'Y' || paymentchoice[0] == 'y') {
                                            system("CLS");
                                            if (processPayment(amount, service)) {
                                                experts[serviceChoice].slots[weekChoice][index] = "BOOKED";
                                                cout << "\n[OK] Booking Confirmed!" << endl;

                                                Day chosenDay = (Day)dayChoice;

                                                addBooking(bookingList, bookingCount,
                                                    string(username),        // pass logged-in customer name
                                                    getExpertName(expertIndex),
                                                    service,
                                                    weekChoice + 1,
                                                    chosenDay,
                                                    slotChoice + 1,
                                                    amount);

                                                cout << "\nPress [ENTER] to return to Customer Menu.....";
                                                clearInputBuffer();
                                                cin.get();
                                                system("CLS");
                                            }
                                            break;
                                        }
                                        else if (paymentchoice[0] == 'N' || paymentchoice[0] == 'n') {
                                            cout << "[OOPS] Booking Cancelled! Returning to Menu......" << endl;
                                            break;
                                        }
                                    }
                                    cout << "[ERROR] Invalid Selection! Please Enter (Y/y/N/n) Only." << endl;
                                }
                                else {
                                    cout << "[OOPS] Slot Already Booked! Please Try Again.\n" << endl;
                                    weekChoice = getValidatedInput(1, 4, "Choose Week") - 1;
                                    dayChoice = getValidatedInput(1, 5, "Choose Day") - 1;
                                    slotChoice = getValidatedInput(1, 2, "Choose Slot") - 1;
                                }
                            }
                            break;
                        case 'N':
                        case 'n':
                            system("CLS");
                            break;
                        default:
                            cout << "[ERROR] Invalid Selection! Please Enter (Y/y/N/n) Only." << endl;
                            continue;
                        }
                        break;
                    } while (true);
                    break;
                case 'N':
                case 'n':
                    system("CLS");
                    break;
                default:
                    cout << "[ERROR] Invalid Selection! Please Enter (Y/y/N/n) Only." << endl;
                    continue;
                }
                break;
            } while (true);
            break;
        case 3:
            system("CLS");
            showBookings(experts, count, bookingList, bookingCount, string(username));
            cout << "\nPress [ENTER] to return to Customer Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 4:
            exitMenu = true; // Leave customer menu
            system("CLS");
            break;
        }
    }while (!exitMenu);
}