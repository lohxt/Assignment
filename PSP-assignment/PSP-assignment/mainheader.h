#pragma once
#include <string>

// ===== Calendar settings =====
const int WEEKS = 4;
const int DAYS = 5;
const int SLOTS_PER_DAY = 6; // 2 sessions per day, 3 hours each (9am-12pm, 12pm-3pm)
const int TOTAL_SLOTS_WEEK = DAYS * SLOTS_PER_DAY; // 30 slots per week

// Expert structure
struct ExpertInfo {
    std::string username;
    std::string password;
    std::string slots[WEEKS][DAYS * SLOTS_PER_DAY] = { "FREE" }; // all slots default to "FREE"
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
