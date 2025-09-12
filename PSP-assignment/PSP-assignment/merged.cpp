#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

// ================== CONSTANTS ==================
const int WEEKS = 4;
const int DAYS = 5;
const int SLOTS_PER_DAY = 2;
const int MAX_BOOKINGS = 100;

// ================== ENUM ==================
enum Day { MON, TUE, WED, THU, FRI };

// ================== STRUCTS ==================
struct Booking {
    string customerName;
    string expertName;
    string service;
    int week;
    Day day;
    int slot;
    double amount;
    bool done = false;
};
struct ExpertInfo {
    string username;
    string password;
    string slots[WEEKS][DAYS * SLOTS_PER_DAY] = { "FREE" }; // all slots default to "FREE"
};

// ================== FUNCTION PROTOTYPES ==================
void clearInputBuffer();
void customer(ExpertInfo experts[], int count, Booking bookingList[], int& bookingCount);
void admin(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount);
void Expert(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount);
void InitSchedules(ExpertInfo experts[], int count);
void ShowExpertSchedule(ExpertInfo experts[], int count, int expertIndex);
void ShowAllSchedules(ExpertInfo experts[], int count);
void ShowExpertCustomers(Booking bookingList[], int count, const string& expertName);
void ShowExpertBonus(string username, Booking bookingList[], int bookingCount);
void markbookingdone_expert(Booking bookingList[], int bookingCount, const string& expertName);
void Indi_schedule(ExpertInfo experts[], int count);
void Schedule(ExpertInfo experts[], int count);
void Customer_list(Booking bookingList[], int bookingCount);
void Expert_bonus(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount);
void ViewCustomerFeedback();
void markbookingdone(Booking bookingList[], int bookingCount);
const char* getDayName(Day day);
void savebookingstofile(Booking bookingList[], int bookingCount);
int loadbookingsfromfile(Booking bookingList[], int maxSize);
void clearInputBuffer();
void customerfeedback(const string& customername);
int getValidatedInput(int min, int max, const string& prompt);
bool processPayment(double amount, string service);
string getExpertName(int serviceChoice);
void addBooking(Booking bookingList[], int& bookingCount, const string& customerName, const string& expertName, const string& service,
    int week, Day day, int slot, double amount);
void showBookings(ExpertInfo experts[], int expertCount, Booking bookingList[], int& bookingCount, const string& currentUser);

// ================== GENERAL FUNCTIONS ==================
void clearInputBuffer() {
    char c;
    while ((c = cin.get()) != '\n' && c != EOF) {
        // discard leftover input
    }
}
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
bool isNumber(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// ================== SAVE / LOAD BOOKINGS ==================
void savebookingstofile(Booking bookingList[], int bookingCount) {
    ofstream outfile("bookings.txt");
    if (!outfile) {
        cout << "[ERROR] Unable to open this file.\n";
        return;
    }

    for (int i = 0; i < bookingCount; ++i) {
        outfile << bookingList[i].customerName << '|'
            << bookingList[i].expertName << '|'
            << bookingList[i].service << '|'
            << bookingList[i].week << '|'
            << static_cast<int>(bookingList[i].day) << '|'
            << bookingList[i].slot << '|'
            << bookingList[i].amount << '|'
            << bookingList[i].done << '\n';
    }
    outfile.close();
}
int loadbookingsfromfile(Booking bookingList[], int maxSize) {
    ifstream infile("bookings.txt");
    if (!infile) {
        return 0;
    }

    int count = 0;
    while (count < maxSize) {
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
        infile.ignore(1000, '\n');

        bookingList[count].week = week;
        bookingList[count].day = static_cast<Day>(dayInt);
        bookingList[count].slot = slot;
        bookingList[count].amount = amount;
        bookingList[count].done = (doneInt != 0);

        ++count;
    }

    infile.close();
    return count;
}

// ================ EXPERT FUNCTIONS ==================
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
void ShowAllSchedules(ExpertInfo experts[], int count) {
    cout << "===== General December Schedule =====\n";
    // Add session notes
    cout << "\n[NOTE] Slot durations by service:\n";
    cout << "All services are 3 hours per session: 9am-12pm, 12pm-3pm\n";

    for (int w = 0; w < WEEKS; w++) {
        cout << "\n" << string(23, '=') << " Week " << (w + 1) << " " << string(24, '=');
        for (int d = 0; d < DAYS; d++) {
            cout << "\n" << getDayName((Day)d) << ":" << endl; // Header row 
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
            cout << "Day      : " << getDayName((Day)bookingList[i].day) << endl;
            cout << "Slot     : " << bookingList[i].slot << endl;
            cout << "Duration : 3 Hours" << endl;
            cout << fixed << setprecision(2);
            cout << "Amount   : RM" << bookingList[i].amount << " + RM100.00 (Service Charge)" << endl;
            cout << "Status   : " << (bookingList[i].done ? "DONE" : "PENING") << endl;
            cout << string(48, '-') << endl;
        }
    }

    if (count == 0) {
        cout << "[OOPS] No Customers Assigned Yet.\n";
    }
}
void ShowExpertBonus(string username, Booking bookingList[], int bookingCount) {
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
void markbookingdone_expert(Booking bookingList[], int bookingCount, const string& expertName) {
    if (bookingCount == 0) {
        cout << "No bookings available.\n";
        return;
    }

    cout << "===== Your Customer Bookings =====\n";
    int customerIndexes[MAX_BOOKINGS];
    int count = 0;

    for (int i = 0; i < bookingCount; i++) {
        if (bookingList[i].expertName == expertName) {
            customerIndexes[count] = i; // store index of this expert’s booking
            cout << count + 1 << ". "
                << bookingList[i].customerName << " | "
                << bookingList[i].service << " | Week " << bookingList[i].week
                << " | " << (bookingList[i].done ? "[DONE]" : "[PENDING]") << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "[OOPS] You have no customers assigned yet.\n";
        return;
    }

    int choice;
    cout << "\nSelect the booking to update (Enter 0 to cancel): ";
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[ERROR] Invalid input!\n";
        return;
    }
    if (choice == 0) {
        cout << "Returning to Expert Menu...\n";
        return;
    }
    if (choice < 1 || choice > count) {
        cout << "[ERROR] Invalid selection!\n";
        return;
    }

    int index = customerIndexes[choice - 1];
    cout << "\nCurrent status: "
        << (bookingList[index].done ? "[DONE]" : "[PENDING]") << endl;
    cout << "Do you want to mark it as:\n";
    cout << "1. DONE\n";
    cout << "2. PENDING\n";
    cout << "Selection: ";

    int statusChoice;
    cin >> statusChoice;

    if (statusChoice == 1) {
        bookingList[index].done = true;
        cout << "[OK] Booking marked as DONE.\n";
    }
    else if (statusChoice == 2) {
        bookingList[index].done = false;
        cout << "[OK] Booking marked as PENDING.\n";
    }
    else {
        cout << "[ERROR] Invalid choice. Returning without changes.\n";
        return;
    }

    savebookingstofile(bookingList, bookingCount);
}
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
        cout << "4. Mark Booking Status" << endl;
        cout << "5. Exit to Main Menu\n" << endl;
        cout << "Selection: ";
        cin >> option;

        while ((option < 1 || option > 5) || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[ERROR] Invalid Selection! Please Choose (1-5) Only." << endl;
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
            ShowExpertBonus(username, bookingList, bookingCount);
            cout << "\nPress [ENTER] to return to Expert Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 4:
            system("CLS");
            markbookingdone_expert(bookingList, bookingCount, experts[loggedExpert].username);
            cout << "\nPress [ENTER] to return to Expert Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 5:
            exitMenu = true;
            system("CLS");
            break;
        }
    } while (!exitMenu);
}

// ================== ADMIN FUNCTIONS ==================
void Indi_schedule(ExpertInfo experts[], int count) {
    int expertselect;
    cout << "Select an expert:\n";
    cout << "1. " << experts[0].username << endl;
    cout << "2. " << experts[1].username << endl;
    cout << "3. " << experts[2].username << endl;

    while (true) {
        cout << "\nSelection: ";
        cin >> expertselect;

        if (expertselect >= 1 && expertselect <= 3) {
            system("CLS");
            ShowExpertSchedule(experts, count, expertselect - 1);
            break;
        }
        else if (cin.fail() || (expertselect < 1 || expertselect > 3)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[ERROR] Invalid Expert Selection! Please Select Expert 1-3 Only." << endl;
        }
    }
}
void Schedule(ExpertInfo experts[], int count) {
    ShowAllSchedules(experts, count);
}
void Customer_list(Booking bookingList[], int bookingCount) {
    string dayNames[5] = { "Mon", "Tue", "Wed", "Thu", "Fri" };
    cout << string(12, '=') << " All Customer Bookings " << string(12, '=') << "\n" << endl;
    if (bookingCount == 0)
    {
        cout << "No Customers Have Booked Yet." << endl;
        return;
    }
    for (int i = 0; i < bookingCount; i++)
    {
        cout << "Customer : " << bookingList[i].customerName << endl;
        cout << "Service  : " << bookingList[i].service << endl;
        cout << "Expert   : " << bookingList[i].expertName << endl;
        cout << "Week     : " << bookingList[i].week << endl;
        cout << "Day      : " << getDayName((Day)bookingList[i].day) << endl;
        cout << "Slot     : " << bookingList[i].slot << endl;
        cout << fixed << setprecision(2);
        cout << "Amount   : RM" << bookingList[i].amount << " + RM100.00 (Service Charge)" << endl;
        cout << string(48, '-') << endl;
    }
}
void Expert_bonus(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount) {
    cout << string(11, '=') << " Expert Bonus Entitlements " << string(11, '=') << "\n\n";

    if (bookingCount == 0) {
        cout << "No Bookings available. Cannot Calculate Bonuses.\n";
        return;
    }

    // Loop through each expert
    for (int e = 0; e < count; e++) {
        string expertName = experts[e].username;
        int hoursWorked = 0;
        double totalCharges = 0.0;
        double bonusRate = 0.0;
        double bonusEarned = 0.0;
        double SERVICE_CHARGE = 100.00;

        // Go through bookings to accumulate hours & value
        for (int i = 0; i < bookingCount; i++) {
            if (bookingList[i].expertName == expertName) {
                hoursWorked += 3; // Each slot is 3 hours
            }
        }

        // Apply bonus rules
        if (hoursWorked < 25) {
            bonusRate = 0.0;
        }
        else if (hoursWorked < 30) {
            bonusRate = 0.25;
        }
        else if (hoursWorked >= 30) {
            bonusRate = 0.5;
        }

        totalCharges = SERVICE_CHARGE * hoursWorked / 3;
        bonusEarned = totalCharges * bonusRate;

        // Print entitlement details
        cout << "Expert: " << expertName << endl;
        cout << "Total Hours Worked     : " << hoursWorked << " hrs" << endl;
        cout << fixed << setprecision(2);
        cout << "Total Service Charges  : RM" << totalCharges << endl;
        cout << "Bonus Rate             : " << (bonusRate * 100) << "%" << endl;
        cout << "Bonus Amount Earned    : RM" << bonusEarned << endl;
        cout << string(49, '-') << "\n" << endl;
    }
}
void ViewCustomerFeedback() {
    system("CLS");
    cout << string(15, '=') << " CUSTOMER FEEDBACK " << string(15, '=') << "\n\n";

    ifstream outfbfile("feedback.txt");
    if (!outfbfile.is_open()) {
        cout << "No feedback is available. (File unable to open)\n";
        return;
    }

    string line;
    bool hasFeedback = false;

    while (getline(outfbfile, line)) {
        if (line.empty()) continue;

        // Each feedback entry is stored as "customerName|feedback"
        // Find the separator "|" position
        size_t sep = line.find('|');
        if (sep != string::npos) { // If separator found, split the string into customer name and feedback
            string customername = line.substr(0, sep);
            string feedback = line.substr(sep + 1);

            cout << "Customer: " << customername << endl;
            cout << "Feedback: " << feedback << endl;
            cout << "------------------------------------------\n";
            hasFeedback = true;
        }
    }

    outfbfile.close();

    if (!hasFeedback) {
        cout << "No feedback has been submitted yet.\n";
    }
}
void markbookingdone(Booking bookingList[], int bookingCount) {
    if (bookingCount == 0)
    {
        cout << "No bookings available.\n";// exit if there are no bookings
        return;
    }
    cout << "===== Booking List =====\n";
    for (int i = 0; i < bookingCount; i++) // Display all booking status
    {
        cout << i + 1 << ". "
            << bookingList[i].customerName << " | "
            << bookingList[i].service << " | "
            << bookingList[i].expertName
            << " | Week " << bookingList[i].week
            << " | " << (bookingList[i].done ? "[DONE]" : "[PENDING]")
            << endl;
    }
    int choice;
    cout << "\nSelect the booking that needs to be marked (Enter 0 to cancel):\n";
    cin >> choice;

    // input validation
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[ERROR] Invalid input!\n";
        return;
    }
    if (choice == 0)
    {
        cin.ignore(1000, '\n');
        cout << "Returning to Admin Menu.....\n";
        return;
    }

    if (choice < 1 || choice > bookingCount)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[ERROR] Invalid choice!\n";
        return;
    }

    int index = choice - 1;// Map selection to match array index

    cout << "\nCurrent status: "
        << (bookingList[index].done ? "[DONE]" : "[PENDING]") << endl;
    cout << "Do you want to mark it as:\n";
    cout << "1. DONE\n";
    cout << "2. PENDING\n";
    cout << "Selection: ";

    int statusChoice;
    cin >> statusChoice;

    // update booking based on the choice
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[ERROR] Invalid Choice! ";
    }
    else if (statusChoice == 1) {
        bookingList[index].done = true;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[OK] Booking marked as DONE.\n";
    }
    else if (statusChoice == 2) {
        bookingList[index].done = false;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[OK] Booking marked as PENDING.\n";
    }
    else {
        cout << "[ERROR] Invalid selection. Returning without changes.\n";
        clearInputBuffer();
        return;
    }

    savebookingstofile(bookingList, bookingCount);// Save updated data to file
}
void admin(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount) {
    char username[50];
    string password, expectedpw;
    bool validUsername = false, validPassword = false;

    clearInputBuffer();

    // Login section
    cout << "===== CHROMANAILS STUDIO ADMIN MENU =====\n";

    do {
        cout << "Enter Username: ";
        cin.getline(username, 50);

        if (username[0] == '\0' || username[1] == '\0') {
            cout << "\n[ERROR] Username must contain only letters and spaces. Please Try Again." << endl;
            continue;
        }

        validUsername = true;

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

        string lowerusername = username;
        for (int i = 0; i < username[i]; i++)
        {
            lowerusername[i] = tolower(lowerusername[i]);
        }

        expectedpw = lowerusername + "123";

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

    // ===== Admin Menu =====
    do {
        cout << "Welcome, Admin " << username << "!" << endl;
        cout << "What do you want to look at?" << endl;
        cout << "1. View Individual Expert Schedule" << endl;
        cout << "2. View Overall Schedule" << endl;
        cout << "3. View Customer List" << endl;
        cout << "4. View Generate Sales Reports" << endl;
        cout << "5. View Expert Bonus Entitlements" << endl;
        cout << "6. View Customer Feedback" << endl;
        cout << "7. Mark Booking as Done" << endl;
        cout << "8. Exit to Main Menu\n" << endl;
        cout << "Selection: ";
        cin >> option;

        while ((option < 1 || option > 8) || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[ERROR] Invalid Selection! Please Choose (1-8) Only." << endl;
            cout << "\nSelection: ";
            cin >> option;
        }

        switch (option) {
        case 1:
            system("CLS");
            Indi_schedule(experts, 3);
            cout << "\nPress [ENTER] to return to Admin Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 2:
            system("CLS");
            Schedule(experts, 3);
            cout << "\nPress [ENTER] to return to Admin Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 3:
            system("CLS");
            Customer_list(bookingList, bookingCount);
            cout << "\nPress [ENTER] to return to Admin Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 4: {
            system("CLS");
            int selection;
            bool exitSalesReport = false;
            do {
                cout << string(10, '=') << " SALES REPORT MENU " << string(10, '=') << "\n" << endl;
                cout << "1. View Sales Report By Date Range" << endl;
                cout << "2. View Sales Report By Service Category" << endl;
                cout << "3. View Sales Report By Expert" << endl;
                cout << "4. Exit to Admin Menu\n" << endl;
                cout << "Selection: ";
                cin >> selection;

                while (cin.fail() || (selection < 1 || selection > 4)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "[ERROR] Invalid Selection! Please Choose (1-4) Only." << endl;
                    cout << "\nSelection: ";
                    cin >> selection;
                }

                cout << fixed << setprecision(2);
                switch (selection) {
                case 1: {
                    system("CLS");
                    // ==== Sales by Week Range ====
                    double totalSalesInRange = 0.0;

                    cout << "===== SALES REPORT (Weeks 1-" << WEEKS << ") =====\n" << endl;
                    cout << left << setw(10) << "Week" << setw(15) << "Sales (RM)" << endl;
                    cout << "--------------------------\n";

                    for (int week = 1; week <= WEEKS; week++) {
                        double weeklySales = 0.0;     // reset per week
                        for (int i = 0; i < bookingCount; i++) {
                            if (bookingList[i].week == week) {
                                weeklySales += bookingList[i].amount + 100; // base + service charge
                            }
                        }
                        cout << left << setw(10) << week << setw(15) << weeklySales << "\n";
                        totalSalesInRange += weeklySales;
                    }

                    cout << "--------------------------\n";
                    cout << left << setw(10) << "TOTAL" << setw(15) << totalSalesInRange << "\n" << endl;
                    cout << "Press [ENTER] to return to Admin Menu.....";
                    clearInputBuffer();
                    cin.get();
                    system("CLS");
                    break;
                }
                case 2: {
                    system("CLS");
                    // ==== Total Treatment Sales (By Service Type) ====
                    double NailArtSales = 0.0;
                    double ManicureSales = 0.0;
                    double PedicureSales = 0.0;
                    double AcrylicNailsSales = 0.0;
                    double totalSales = 0.0;
                    cout << "===== SALES REPORT (By Service) =====\n" << endl;

                    for (int i = 0; i < bookingCount; i++) {
                        double value = bookingList[i].amount + 100; // ensure consistent service charge
                        const string& svc = bookingList[i].service;

                        if (svc == "Nail Art") {
                            NailArtSales += value;
                        }
                        else if (svc == "Manicure") {
                            ManicureSales += value;
                        }
                        else if (svc == "Pedicure") {
                            PedicureSales += value;
                        }
                        else if (svc == "Acrylic Nails") {
                            AcrylicNailsSales += value;
                        }
                    }

                    cout << "Nail Art      : RM" << NailArtSales << endl;
                    cout << "Manicure      : RM" << ManicureSales << endl;
                    cout << "Pedicure      : RM" << PedicureSales << endl;
                    cout << "Acrylic Nails : RM" << AcrylicNailsSales << endl;

                    totalSales = NailArtSales + ManicureSales + PedicureSales + AcrylicNailsSales;
                    cout << "-------------------------------------" << endl;
                    cout << "TOTAL SALES   : RM" << totalSales << "\n" << endl;
                    cout << "Press [ENTER] to return to Admin Menu.....";
                    clearInputBuffer();
                    cin.get();
                    system("CLS");
                    break;
                }
                case 3: {
                    system("CLS");
                    // ==== Sales by Expert ====
                    cout << "===== SALES REPORT (By Expert) =====\n" << endl;

                    double totalSales = 0.0;  // <-- reset per run

                    for (int e = 0; e < count; e++) {
                        double expertSales = 0.0; // <-- reset per expert
                        for (int i = 0; i < bookingCount; i++) {
                            if (bookingList[i].expertName == experts[e].username) {
                                expertSales += bookingList[i].amount + 100; // base + service charge
                            }
                        }
                        cout << "Expert " << experts[e].username << "\t: RM" << expertSales << endl;
                        totalSales += expertSales;
                    }

                    cout << "------------------------------------" << endl;
                    cout << "TOTAL SALES" << string(13, ' ') << ": RM" << totalSales << "\n" << endl;
                    cout << "Press [ENTER] to return to Admin Menu.....";
                    clearInputBuffer();
                    cin.get();
                    system("CLS");
                    break;
                }
                case 4:
                    exitSalesReport = true;
                    system("CLS");
                    break;
                }
            } while (!exitSalesReport);
            break;
        }
        case 5:
            system("CLS");
            Expert_bonus(experts, count, bookingList, bookingCount);
            cout << "\nPress [ENTER] to return to Admin Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 6:
            system("CLS");
            ViewCustomerFeedback();
            cout << "\nPress [ENTER] to return to Admin Menu.....\n";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 7:
            system("CLS");
            markbookingdone(bookingList, bookingCount);
            cout << "\nPress [ENTER] to return to Admin Menu.....\n";
            clearInputBuffer();
            system("CLS");
            break;
        case 8:
            exitMenu = true;
            system("CLS");
            break;
        }
    } while (!exitMenu);
}

// ================== CUSTOMER FUNCTIONS ==================
void customerfeedback(const string& customername) {
    string feedback;

    cout << "==== Feedback Form ====\n"
        << "We value your feedback, " << customername << "! Let us know if there are any improvements we can make.\n";
    cout << "Please enter your feedback about our service.(Enter 0 to cancel and return) \n";
    getline(cin, feedback);

    if (feedback == "0")
    {
        cout << "\nFeedback canceled. Returning to Menu.....\n";
        return;
    }

    ofstream fbfile("feedback.txt", ios::app); // open file in append mode
    if (!fbfile) {
        cout << "[ERROR] Unable to open feedback file.";
        return;
    }

    // save feedback in the format of: customer|feedback
    fbfile << customername << "|" << feedback << endl;

    fbfile.close(); // close the file 

    cout << "\nThank you for your feedback, we appreciate your opinion.\n";
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
void addBooking(Booking bookingList[], int& bookingCount, const string& customerName, const string& expertName, const string& service, 
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
        
        if (strlen(username) == 0)
        {
            cout << "[ERROR] Username cannot be Empty!\n";
            continue;
        }

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
    } while (!validUsername);

    do {
        cout << "Password: ";
        getline(cin, password);

        if (password.empty())
        {
            cout << "[ERROR] Password cannot be Empty!\n";
            continue;
        }

        for (int i = 0; password[i] != '\0'; i++) {
            password[i] = tolower(password[i]);
        }

        string lowerusername = username;
        for (int i = 0; i < username[i]; i++)
        {
            lowerusername[i] = tolower(lowerusername[i]);
        }

        expectedpw = lowerusername + "123";

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
    string input;
    bool exitMenu = false;

    // ===== Customer Menu =====
    do {
        cout << "Welcome, " << username << "!" << endl;
        cout << "What would you like to do today?" << endl;
        cout << "1. View Information About ChromaNails Studio" << endl;
        cout << "2. View Services & Experts" << endl;
        cout << "3. View My Bookings" << endl;
        cout << "4. Submit Feedback" << endl;
        cout << "5. Exit to Main Menu\n" << endl;
        cout << "Selection: ";
        getline(cin, input);

        if (input.empty())
        {
            cout << "[ERROR] Empty Input! Please Select a choice(1-5).\n\n";
            continue;
        }

        bool isNumber = true;
        for (int i = 0; i < input.length(); i++) {
            if (!isdigit(input[i])) {
                isNumber = false;
                break;
            }
        }
        if (!isNumber) {
            cout << "[ERROR] Invalid Input! Please Enter Digits Only.\n";
            continue;
        }

        option = stoi(input);

        // --- Range check ---
        if (option < 1 || option > 5) {
            cout << "[ERROR] Invalid Selection! Please Choose (1-5) Only.\n";
            continue;
        }

        switch (option) {
        case 1: {
            system("CLS");
            cout << string(80, '=') << endl;
            cout << right << setw(58) << "CHROMANAILS STUDIO - NAIL CARE & ART" << endl;
            cout << string(80, '=') << "\n" << endl;

            cout << "About Us:\n";
            cout << "At ChromaNails Studio, we combine creativity and care to craft stylish, long-lasting nails.\n\n";

            cout << "Operating Hours:\n";
            cout << "Mon-Fri : 9:00 AM - 3:00 PM\n";
            cout << "Closed on Weekends and Public Holidays\n\n";

            cout << "Contact:\n";
            cout << "Lot 12, Glamour Street, KL | +60 12-345 6789\n";
            cout << "Email: hello@chromanails.com | www.chromanails.com\n";
            cout << "Instagram/Facebook: @ChromaNailsStudio\n\n";

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
            system("CLS");
            break;
        }
        case 2: {
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

                            //Post-Decrement to match with array 
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
        }
        case 3:
            system("CLS");
            showBookings(experts, count, bookingList, bookingCount, string(username));
            cout << "\nPress [ENTER] to return to Customer Menu.....";
            clearInputBuffer();
            cin.get();
            system("CLS");
            break;
        case 4:
            system("CLS");
            customerfeedback(string(username));
            cout << "Press [ENTER] to return to customer menu.....";
            cin.get();
            system("CLS");
            break;
        case 5:
            exitMenu = true; // Leave customer menu
            system("CLS");
            break;
        }
    } while (!exitMenu);
}

// ================== MAIN ==================
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

    // Main menu loop 
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