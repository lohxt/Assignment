//#pragma once
//#include <string>
//using namespace std;
//
//// ===== Calendar settings =====
//const int WEEKS = 4;
//const int DAYS = 5;
//const int SLOTS_PER_DAY = 2; // 2 sessions per day, 3 hours each (9am-12pm, 12pm-3pm)
//const int TOTAL_SLOTS_WEEK = DAYS * SLOTS_PER_DAY; // 30 slots per week
//const int MAX_BOOKINGS = 100;
//
//// enum for days of the week
//enum Day {
//    MON = 0,
//    TUE,
//    WED,
//    THU,
//    FRI,
//    DAYS_COUNT
//};
//
//const char* getDayName(Day day);
//
//// Structures
//struct Booking {
//    string customerName;   
//    string expertName;
//    string service;
//    int week;
//    Day day;
//    int slot;
//    double amount;
//    bool done;
//};
//
//struct ExpertInfo {
//    string username;
//    string password;
//    string slots[WEEKS][DAYS * SLOTS_PER_DAY] = { "FREE" }; // all slots default to "FREE"
//};
//
//int loadbookingsfromfile(Booking bookingList[], int maxSize);
//void savebookingstofile(Booking bookinglist[], int bookingCount);
//
//// ===== Admin functions =====
//void admin(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount);
//void Indi_schedule(ExpertInfo experts[], int count);
//void Schedule(ExpertInfo experts[], int count);
//void Customer_list(Booking bookingList[], int bookingCount);
//void Expert_bonus(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount);
//void ViewCustomerFeedback();
//void markbookingdone(Booking bookingList[], int bookingCount);
//
//// ===== Expert functions =====
//void Expert(ExpertInfo experts[], int count, Booking bookingList[], int bookingCount);
//void InitSchedules(ExpertInfo experts[], int count);
//void ShowAllSchedules(ExpertInfo experts[], int count);
//void ShowExpertSchedule(ExpertInfo experts[], int count, int expertIndex);
//void ShowExpertCustomers(Booking bookingList[], int bookingCount, const string& expertName);
//void ShowExpertBonus(string username, Booking bookingList[], int bookingCount);
//
//// ===== Customer functions =====
//void customer(ExpertInfo experts[], int count, Booking bookingList[], int& bookingCount);
//void clearInputBuffer();
//void customerfeedback(const string& customername);
