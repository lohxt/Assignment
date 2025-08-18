#pragma once
#include <string>

// ===== Calendar settings =====
const int WEEKS = 4;
const int DAYS = 7;
const int SLOTS_PER_DAY = 8; //9am - 4pm with 1-hour slots
const int TOTAL_SLOTS_WEEK = DAYS * SLOTS_PER_DAY; // 56

// Expert structure
struct ExpertInfo {
    std::string username;
    std::string password;
    // Flattened: each week has TOTAL_SLOTS_WEEK entries (7 days * 8 slots)
    std::string slots[WEEKS][TOTAL_SLOTS_WEEK]; // "FREE" or "BOOKED"
};

// ===== Global data =====
extern ExpertInfo experts[3];

// ===== Admin functions =====
void admin();
void Indi_schedule();
void Schedule();
void Customer_list();
void Generate_sales_rpt();
void Expert_bonus();

// ===== Expert functions =====
void Expert();
void InitSchedules();
void ShowAllSchedules();
void ShowExpertSchedule(int expertIndex);

// ===== Customer functions =====
void customer();
void clearInputBuffer();
