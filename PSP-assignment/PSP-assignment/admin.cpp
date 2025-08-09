#include <iostream>
#include <string>
using namespace std;

void Indi_schedule() {
    int ex;
    cout << "Select an expert" << endl;
    cout << "1. ex1\n2. ex2\n3. ex3" << endl;
    cin >> ex;

    switch (ex) {
    case 1: cout << "schedule1"; break;
    case 2: cout << "schedule2"; break;
    case 3: cout << "schedule3"; break;
    default: cout << "Invalid expert"; break;
    }
}

void Schedule() { cout << "full schedule here"; }
void Customer_list() { cout << "full customer list"; }
void Generate_sales_rpt() { cout << "Generating sales report..."; }
void Expert_bonus() { cout << "Calculating expert bonus..."; }
