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

int GetTimeBetween(time_t first, ACTIVITY next, TIME_UNIT unit)
{
	int ret = 0;

	switch (unit) {
	case TIMEUNIT_MINUTE:
		ret = (int)(next.tStart - first) / 60;
		break;
	case TIMEUNIT_HOUR:
		ret = (int)(next.tStart - first) / 3600;
		break;
	case TIMEUNIT_DAY:
		ret = GetDaysBetween(first, next.tStart);
		break;
	case TIMEUNIT_WEEK:
		ret = GetWeeksBetween(first, next.tStart);
		break;
	case TIMEUNIT_MONTH:
		ret = GetMonthsBetween(first, next.tStart);
		break;
	case TIMEUNIT_CALMONTH:
		ret = GetCalMonthsBetween(first, next.tStart);
		break;
	}

	return ret;
}
int GetTimeBetween(ACTIVITY first, time_t next, TIME_UNIT unit)
{
	int ret = 0;

	switch (unit) {
	case TIMEUNIT_MINUTE:
		ret = (int)(next - first.tEnd) / 60;
		break;
	case TIMEUNIT_HOUR:
		ret = (int)(next - first.tEnd) / 3600;
		break;
	case TIMEUNIT_DAY:
		ret = GetDaysBetween(first.tEnd, next);
		break;
	case TIMEUNIT_WEEK:
		ret = GetWeeksBetween(first.tEnd, next);
		break;
	case TIMEUNIT_MONTH:
		ret = GetMonthsBetween(first.tEnd, next);
		break;
	case TIMEUNIT_CALMONTH:
		ret = GetCalMonthsBetween(first.tEnd, next);
		break;
	}

	return ret;
}

time_t GetnDaysAgo(time_t time, int days)
{
	time_t ret = 0;
	tm *ref;

	time -= days * 24 * 3600;
	ref = localtime(&time);

	ref->tm_hour = 0;
	ref->tm_min = 0;
	ref->tm_sec = 0;

	ret = mktime(ref);
	
	return ret;
}

time_t GetnWeeksAgo(time_t time, int weeks)
{
	return GetnDaysAgo(time, weeks * 7);
}
time_t GetnMonthsAgo(time_t time, int months)
{
	time_t ret = 0;
	tm*ref;

	ref = localtime(&time);

	ref->tm_hour = 0;
	ref->tm_min = 0;
	ref->tm_sec = 0;

	if (ref->tm_mon - months < 0) {
		ref->tm_year -= (int)ceil(months / 12);
		ref->tm_mon = (ref->tm_mon+(12 - (months % 12)))%12;
	}
	else {
		ref->tm_mon = ref->tm_mon - months;
	}

	if (ref->tm_mday > 28 && ref->tm_mon == 1) {
		if ((ref->tm_year % 4 == 0) && (ref->tm_year % 100 != 0) || (ref->tm_year % 400 == 0)) { //if leap year
			ref->tm_mday = 29;
		}
		else {
			ref->tm_mday = 28;
		}
	}
	else if(ref->tm_mday > 30){
		switch (ref->tm_mon) {
		case 3: //Apr
		case 5: //Jun
		case 8: //Sep
		case 10: //Nov
			ref->tm_mday = 30;
			break;
		}
	}

	ref->tm_wday = 0;
	ref->tm_yday = 0;

	ret = mktime(ref);

	return ret;
}

time_t GetnCalMonthsAgo(time_t time, int calMonths)
{
	time_t ret = 0;
	tm*ref;

	ref = localtime(&time);

	ref->tm_hour = 0;
	ref->tm_min = 0;
	ref->tm_sec = 0;

	if (ref->tm_mon - calMonths < 0) {
		ref->tm_year -= (int)ceil(calMonths / 12);
		ref->tm_mon = (ref->tm_mon + (12 - (calMonths % 12))) % 12;
	}
	else {
		ref->tm_mon = ref->tm_mon - calMonths;
	}

	ref->tm_mday = 1;
	ref->tm_wday = 0;
	ref->tm_yday = 0;

	ret = mktime(ref);

	return ret;
}