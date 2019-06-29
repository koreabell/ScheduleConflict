#include "TimeCalc.h"

WEEKDAY GetWeekday(time_t timeIn)
{
	struct tm *Time = localtime(&timeIn);
	return (WEEKDAY)Time->tm_wday;
}
WEEKDAY GetWeekday(struct tm timeIn)
{
	return (WEEKDAY)timeIn.tm_wday;
}

MONTH GetMonth(time_t timeIn)
{
	struct tm*Time = localtime(&timeIn);
	return (MONTH)Time->tm_mon;
}
MONTH GetMonth(struct tm timeIn)
{
	return (MONTH)timeIn.tm_mon;
}

short GetYear(time_t timeIn)
{
	struct tm*Time = localtime(&timeIn);
	return (short)Time->tm_year + 1900;
}
short GetYear(struct tm timeIn)
{
	return (short)timeIn.tm_year + 1900;
}

int GetDaysBetween(time_t first, time_t next)
{
	return (int)ceil((double)(next - first) / 86400);
}

int GetWeeksBetween(time_t first, time_t next)
{
	struct tm*timeFirst, *timeNext;
	int ret = 0;
	timeFirst = localtime(&first);
	timeNext = localtime(&next);

	if (GetDaysBetween(first,next) < 7) {
		if (timeFirst->tm_wday > timeNext->tm_wday) {
			ret = 1;
		}
		else {
			ret = 0;
		}
	}
	else {
		ret = GetDaysBetween(first, next) / 7;
		if (timeFirst->tm_wday > timeNext->tm_wday) {
			ret += 1;
		}
	}

	return ret;
}

int GetMonthsBetween(time_t first, time_t next)
{
	return GetDaysBetween(first, next) / 30;
}

int GetCalMonthsBetween(time_t first, time_t next)
{
	struct tm*timeFirst, *timeNext;
	int ret = 0;
	timeFirst = localtime(&first);
	timeNext = localtime(&next);

	ret = 12 * (timeNext->tm_year - timeFirst->tm_year);

	if (timeFirst->tm_mon > timeNext->tm_mon) {
		ret -= timeFirst->tm_mon - timeNext->tm_mon;
	}
	else {
		ret += timeNext->tm_mon - timeFirst->tm_mon;
	}

	switch (timeNext->tm_mon) {
		case 0:
		case 2:
		case 4:
		case 6:
		case 7:
		case 9:
		case 11:
			if (timeNext->tm_mday != 31) {
				ret--;
			}
			break;
		case 3:
		case 5:
		case 8:
		case 10:
			if (timeNext->tm_mday != 30) {
				ret--;
			}
			break;
		case 1:
			if (timeNext->tm_mday < 28) {
				ret--;
			}
			break;
	}

	return ret;
}

int GetTimeBetween(ACTIVITY first, ACTIVITY next, TIME_UNIT unit)
{
	int ret = 0;

	switch (unit) {
		case TIMEUNIT_MINUTE:
			ret = (int)(next.tStart - first.tEnd) / 60;
			break;
		case TIMEUNIT_HOUR:
			ret = (int)(next.tStart - first.tEnd) / 3600;
			break;
		case TIMEUNIT_DAY:
			ret = GetDaysBetween(first.tEnd, next.tStart);					
			break;
		case TIMEUNIT_WEEK:
			ret = GetWeeksBetween(first.tEnd, next.tStart);
			break;
		case TIMEUNIT_MONTH:
			ret = GetMonthsBetween(first.tEnd, next.tStart);
			break;
		case TIMEUNIT_CALMONTH:
			ret = GetCalMonthsBetween(first.tEnd, next.tStart);
			break;
	}

	return ret;
}