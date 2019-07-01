#pragma once
#ifndef TIME_CALCULATION
#define TIME_CALCULATION
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"

WEEKDAY GetWeekday(time_t timeIn);
WEEKDAY GetWeekday(struct tm timeIn);

MONTH GetMonth(time_t timeIn);
MONTH GetMonth(struct tm timeIn);

short GetYear(time_t timeIn);
short GetYear(struct tm timeIn);

int GetDaysBetween(time_t first, time_t next);
int GetWeeksBetween(time_t first, time_t next);
int GetMonthsBetween(time_t first, time_t next);
int GetCalMonthsBetween(time_t first, time_t next);
int GetTimeBetween(ACTIVITY first, ACTIVITY next,TIME_UNIT unit);
int GetTimeBetween(time_t first, ACTIVITY next, TIME_UNIT unit);
int GetTimeBetween(ACTIVITY first, time_t next, TIME_UNIT unit);

time_t GetnDaysAgo(time_t time, int days);
time_t GetnWeeksAgo(time_t time, int weeks);
time_t GetnMonthsAgo(time_t time, int months);
time_t GetnCalMonthsAgo(time_t time, int calMonths);





#endif
