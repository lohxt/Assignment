#pragma once
#include <string>

// ===== Calendar settings =====
const int WEEKS = 4;
const int DAYS = 5;
const int SLOTS_PER_DAY = 6; // 9am - 3pm with 1-hour slots
const int TOTAL_SLOTS_WEEK = DAYS * SLOTS_PER_DAY; // 30

// Expert structure
struct ExpertInfo {
    std::string username;
    std::string password;
    std::string slots[WEEKS][TOTAL_SLOTS_WEEK]; // "FREE" or "BOOKED"
};

// ===== Admin functions =====
void admin(ExpertInfo experts[], int count);
void Indi_schedule(ExpertInfo experts[], int count);
void Schedule(ExpertInfo experts[], int count);
void Customer_list();
void Generate_sales_rpt();
void Expert_bonus();

// ===== Expert functions =====
void Expert(ExpertInfo experts[], int count);
void InitSchedules(ExpertInfo experts[], int count);
void ShowAllSchedules(ExpertInfo experts[], int count);
void ShowExpertSchedule(ExpertInfo experts[], int count, int expertIndex);

// ===== Customer functions =====
void customer(ExpertInfo experts[], int count);
void clearInputBuffer();
