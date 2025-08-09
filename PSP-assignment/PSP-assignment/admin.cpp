#include <iostream>
#include "header.h"
using namespace std;

void Indi_schedule() {
    int ex;
    cout << "Select an expert:\n";
    cout << "1. " << experts[0].username << "\n";
    cout << "2. " << experts[1].username << "\n";
    cout << "3. " << experts[2].username << "\n";
    cin >> ex;

    if (ex >= 1 && ex <= 3) {
        ShowExpertSchedule(ex - 1);
    }
    else {
        cout << "Invalid expert selection.\n";
    }
}

void Schedule() {
    ShowAllSchedules();
}

void Customer_list() {
    cout << "Displaying customer list... (Feature pending)\n";
}

void Generate_sales_rpt() {
    cout << "Generating sales report... (Feature pending)\n";
}

void Expert_bonus() {
    cout << "Calculating expert bonus... (Feature pending)\n";
}
