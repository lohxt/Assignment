#pragma once
#include <string>
using namespace std;

// ===== Calendar settings =====
const int WEEKS = 4;
const int DAYS = 5;
const int SLOTS_PER_DAY = 2; // 2 sessions per day, 3 hours each (9am-12pm, 12pm-3pm)
const int TOTAL_SLOTS_WEEK = DAYS * SLOTS_PER_DAY; // 30 slots per week
const int MAX_BOOKINGS = 100;

// Structures
struct Booking {
    string customerName;   // NEW
    string expertName;
    string service;
    int week;
    int day;
    int slot;
    double amount;
};

struct ExpertInfo {
    string username;
    string password;
    string slots[WEEKS][DAYS * SLOTS_PER_DAY] = { "FREE" }; // all slots default to "FREE"
};

// ===== Admin functions =====
void admin(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount);
void Indi_schedule(ExpertInfo experts[], int count);
void Schedule(ExpertInfo experts[], int count);
void Customer_list(Booking bookingList[], int bookingCount);
void Generate_sales_rpt();
void Expert_bonus();

// ===== Expert functions =====
void Expert(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount);
void InitSchedules(ExpertInfo experts[], int count);
void ShowAllSchedules(ExpertInfo experts[], int count);
void ShowExpertSchedule(ExpertInfo experts[], int count, int expertIndex);
void ShowExpertCustomers(Booking bookingList[], int bookingCount, const string& expertName);

// ===== Customer functions =====
void customer(ExpertInfo experts[], int count, Booking bookingList[], int& bookingCount);
void clearInputBuffer();
