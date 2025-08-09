#pragma once
#include <string>

// ===== Calendar settings =====
const int WEEKS = 4;
const int SLOTS_PER_DAY = 8; // 9am–4pm

// Expert structure
struct ExpertInfo {
    std::string username;
    std::string password;
    std::string slots[WEEKS][SLOTS_PER_DAY]; // "FREE" or "BOOKED"
};

// ===== Global data =====
extern ExpertInfo experts[3];

// ===== Admin functions =====
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
