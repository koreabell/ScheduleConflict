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






#endif
