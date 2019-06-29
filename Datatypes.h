#pragma once
#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include "main.h"
#include <time.h>

typedef enum {
	DAY_SUN=0,
	DAY_MON,
	DAY_TUE,
	DAY_WED,
	DAY_THU,
	DAY_FRI,
	DAY_SAT
} WEEKDAY;

typedef enum {
	MONTH_JAN=0,
	MONTH_FEB,
	MONTH_MAR,
	MONTH_APR,
	MONTH_MAY,
	MONTH_JUN,
	MONTH_JUL,
	MONTH_AUG,
	MONTH_SEP,
	MONTH_OCT,
	MONTH_NOV,
	MONTH_DEC
} MONTH;

typedef struct {
	unsigned int uiActivityID;
	unsigned int uiType;
	wchar_t strName[51];
	wchar_t strDescription[501];
	time_t tStart;
	time_t tEnd;
	unsigned int uiDuration;
} ACTIVITY;

typedef struct SCHEDLIST{
	SCHEDLIST*pPrev;
	ACTIVITY data;
	SCHEDLIST*pNext;
};

typedef enum {
	RULE_EQUAL,					//Value being compared should be equal to specified value
	RULE_WITHIN,				//Value being compared should be within specified range
	RULE_GREATER,				//Value being compared should be greater than specified value
	RULE_EQGREATER,				//Value being compared should be equal to or greater than specified value
	RULE_LESS,					//Value being compared should be less than specified value
	RULE_EQLESS,				//Value being compared should be equal to or less than specified value
	RULE_RESERVED				//RESERVED FOR FUTURE USE
} RULE_CRITERIA;

typedef enum {
	CONFLICT_NONE,				//No conflicts
	CONFLICT_BELOW_MIN,			//Below minimum specified
	CONFLICT_ABOVE_MAX,			//Above maximum specified
	CONFLICT_WARNING_MIN,		//Below minimum threshold (but greater than minimum limit)
	CONFLICT_WARNING_MAX,		//Above maximum threshold (but less than maximum limit)
	CONFLICT_RESERVED			//RESERVED FOR FUTURE USE
} CONFLICT_STATUS;

typedef enum {
	COMPARE_DURATION,			//Duration of activity
	COMPARE_TIME_BETWEEN,		//Time between end of last activity and beginning of current activity
	COMPARE_SINCE_CLOCKTIME,	//Time since specified time
	COMPARE_SINCE_ACTIVITY,		//Time since specified activity
	COMPARE_BEFORE_CLOCKTIME,	//Time until specified time
	COMPARE_BEFORE_ACTIVITY,	//Time until specified activity
	COMPARE_CUMUL_ACTIVITYTIME,	//Cumulative activity time within specified range
	COMPARE_RESERVED			//RESERVED FOR FUTURE USE
} COMPARE_TYPE;

typedef enum {
	TIMEUNIT_MINUTE,
	TIMEUNIT_HOUR,
	TIMEUNIT_DAY,
	TIMEUNIT_WEEK,
	TIMEUNIT_MONTH,
	TIMEUNIT_CALMONTH,
	TIMEUNIT_RESERVED
} TIME_UNIT;


typedef struct {
	unsigned int uiRuleID;
	RULE_CRITERIA Criteria;
	COMPARE_TYPE CompareType;
	unsigned int uiActivityType;
	unsigned int uiMin;
	unsigned int uiMax;
	unsigned int uiMinThreshold;
	unsigned int uiMaxThreshold;
	unsigned int uiRange;
	TIME_UNIT RangeUnit;
	BOOL bFromStart;
	BOOL bFutureRange;
	BOOL bThresholdEnabled;
	BOOL bWarningEnabled;
	BOOL bConsecutive;
	BOOL bCumulative;
	wchar_t strRuleName[51];
	wchar_t strRuleDescription[501];
} RULE;

/*********************************************************************************
********************************	FILE HEADERS	******************************
**********************************************************************************/

typedef struct {
	unsigned short uiVersion;
	unsigned short uiOldestCompatibleVersion;
	unsigned int uiActivityUnitSize;
	unsigned int uiNumOfActivities;
	char strValidity[11];
} SCHEDULE_FILE_HEADER;

typedef struct {
	unsigned short uiVersion;
	unsigned short uiOldestCompatibleVersion;
	unsigned int uiRuleUnitSize;
	unsigned int uiNumOfRules;
	char strValidity[11];
} RULE_FILE_HEADER;


#endif
