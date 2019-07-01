#include "DataProcessor.h"


SCHEDLIST * GetFirstActivityInRange(SCHEDLIST * activity, RULE rule)
{
	SCHEDLIST*pCompare;
	time_t compareFrom = 0,rangeStart=0;
	tm compareFromtm;

	if (rule.bFromStart == TRUE) {
		compareFrom = activity->data.tStart;
	}
	else {
		compareFrom = activity->data.tEnd;
	}

	if (activity->pPrev == NULL) return NULL;

	switch (rule.RangeUnit) {
		case TIMEUNIT_MINUTE:
			rangeStart = compareFrom - (rule.uiRange * 60);		
			break;
		case TIMEUNIT_HOUR:
			rangeStart = compareFrom - (rule.uiRange * 3600);
			break;
		case TIMEUNIT_DAY:
			rangeStart = GetnDaysAgo(compareFrom, rule.uiRange);
			break;
		case TIMEUNIT_WEEK:
			rangeStart = GetnWeeksAgo(compareFrom, rule.uiRange);
			break;
		case TIMEUNIT_MONTH:
			rangeStart = GetnMonthsAgo(compareFrom, rule.uiRange);
			break;
		case TIMEUNIT_CALMONTH:
			rangeStart = GetnCalMonthsAgo(compareFrom, rule.uiRange);
			break;
	}

	while (1) {
		if (pCompare->data.tStart <= rangeStart) {
			return pCompare;
		}
		else {
			if (pCompare->pPrev = NULL) {
				return pCompare;
			}
			else {
				pCompare = pCompare->pPrev;
			}
		}
	}
}

CONFLICT_STATUS ValidateConflict(SCHEDLIST*schedules, RULE rule)
{
	CONFLICT_STATUS ret; 
	int i = 0, iX = 0, iY = 0; 
	tm*tmCalc; 
 
	switch (rule.CompareType) { 
		case COMPARE_DURATION: 
			switch (rule.Criteria) { 
				case CRITERIA_EQUAL: 
					if (schedules->data.uiDuration == rule.uiMax) return CONFLICT_NONE; 
					else if (schedules->data.uiDuration > rule.uiMax) return CONFLICT_ABOVE_MAX; 
					else return CONFLICT_BELOW_MIN; 
					break; 
					 
				case CRITERIA_WITHIN: 
					if (schedules->data.uiDuration >= rule.uiMin && schedules->data.uiDuration <= rule.uiMax) { 
						if (rule.bWarningEnabled == FALSE) return CONFLICT_NONE; 
						else { 
							if (schedules->data.uiDuration <= rule.uiMin + rule.uiMinThreshold) return CONFLICT_WARNING_MIN; 
							else if (schedules->data.uiDuration >= rule.uiMax - rule.uiMaxThreshold) return CONFLICT_WARNING_MAX; 
							else return CONFLICT_NONE; 
						} 
					} 
					else if (schedules->data.uiDuration < rule.uiMin) return CONFLICT_BELOW_MIN; 
					else return CONFLICT_ABOVE_MAX; 
					break; 
					 
				case CRITERIA_GREATER: 
					if (schedules->data.uiDuration > rule.uiMin) { 
						if (rule.bWarningEnabled == FALSE) return CONFLICT_NONE; 
						else { 
							if (schedules->data.uiDuration <= rule.uiMin + rule.uiMinThreshold) return CONFLICT_WARNING_MIN; 
							else return CONFLICT_NONE; 
						} 
					} 
					else return CONFLICT_BELOW_MIN; 
					break; 
					
				case CRITERIA_EQGREATER: 
					if (schedules->data.uiDuration >= rule.uiMin) { 
						if (rule.bWarningEnabled == FALSE) return CONFLICT_NONE; 
						else { 
							if (schedules->data.uiDuration <= rule.uiMin + rule.uiMinThreshold) return CONFLICT_WARNING_MIN; 
							else return CONFLICT_NONE; 
						} 
					} 
					else return CONFLICT_BELOW_MIN; 
					break; 
 
 				case CRITERIA_LESS:
 					if (schedules->data.uiDuration < rule.uiMax) {
 						if (rule.bWarningEnabled == FALSE) return CONFLICT_NONE;
 						else {
 							if (schedules->data.uiDuration >= rule.uiMax - rule.uiMaxThreshold) return CONFLICT_WARNING_MAX;
 							else return CONFLICT_NONE;
 						}
 					}
 					else return CONFLICT_ABOVE_MAX;
 					break;
					 
				case CRITERIA_EQLESS: 
 					if (schedules->data.uiDuration < rule.uiMax) {
 						if (rule.bWarningEnabled == FALSE) return CONFLICT_NONE;
 						else {
 							if (schedules->data.uiDuration >= rule.uiMax - rule.uiMaxThreshold) return CONFLICT_WARNING_MAX;
 							else return CONFLICT_NONE;
 						}
 					}
 					else return CONFLICT_ABOVE_MAX;
 					break;
 			}
 			break;
 		case COMPARE_TIME_BETWEEN:
 			iX = GetTimeBetween(schedules->pPrev->data, schedules->data, rule.RuleUnit);
			 
			switch (rule.Criteria) {
				case CRITERIA_EQUAL:
					if (iX == rule.uiMax) return CONFLICT_NONE;
					else if (iX < rule.uiMax) return CONFLICT_BELOW_MIN;
					else CONFLICT_ABOVE_MAX;
					break;

				case CRITERIA_WITHIN:
					if (iX >= rule.uiMin && iX <= rule.uiMax) {
						if (rule.bWarningEnabled == FALSE)return CONFLICT_NONE;
						else {
							if (iX <= rule.uiMin + rule.uiMinThreshold) return CONFLICT_WARNING_MIN;
							else if (iX >= rule.uiMax - rule.uiMaxThreshold) return CONFLICT_WARNING_MAX;
							else return CONFLICT_NONE;
						}
					}
					else if (iX < rule.uiMin) return CONFLICT_BELOW_MIN;
					else return CONFLICT_ABOVE_MAX;
					break;
					
				case CRITERIA_GREATER:
					if (iX > rule.uiMin) {
						if (rule.bWarningEnabled == FALSE) return CONFLICT_NONE;
						else {
							if (iX <= rule.uiMin + rule.uiMinThreshold) return CONFLICT_WARNING_MIN;
							else return CONFLICT_NONE;
						}
					}
					else return CONFLICT_BELOW_MIN;
					break;

				case CRITERIA_EQGREATER:
					if (iX >= rule.uiMin) {
						if (rule.bWarningEnabled == FALSE) return CONFLICT_NONE;
						else {
							if (iX <= rule.uiMin + rule.uiMinThreshold) return CONFLICT_WARNING_MIN;
							else return CONFLICT_NONE;
						}
					}
					else return CONFLICT_BELOW_MIN;
					break;
					
				case CRITERIA_LESS:
					if (iX < rule.uiMax) {
						if (rule.bWarningEnabled == FALSE) return CONFLICT_NONE;
						else {
							if (iX >= rule.uiMax - rule.uiMaxThreshold) return CONFLICT_WARNING_MAX;
							else return CONFLICT_NONE;
						}
					}
					else return CONFLICT_ABOVE_MAX;
					break;

				case CRITERIA_EQLESS:
					if (iX <= rule.uiMax) {
						if (rule.bWarningEnabled == FALSE) return CONFLICT_NONE;
						else {
							if (iX >= rule.uiMax - rule.uiMaxThreshold) return CONFLICT_WARNING_MAX;
							else return CONFLICT_NONE;
						}
					}
					else return CONFLICT_ABOVE_MAX;
					break;
			}
			break;
		case COMPARE_SINCE_CLOCKTIME:
			switch (rule.Criteria) {
			case CRITERIA_EQUAL:
				break;

			case CRITERIA_WITHIN:
				break;

			case CRITERIA_GREATER:
				break;

			case CRITERIA_EQGREATER:
				break;

			case CRITERIA_LESS:
				break;

			case CRITERIA_EQLESS:
				break;
			}
			break;
		case COMPARE_SINCE_ACTIVITY:
			switch (rule.Criteria) {
			case CRITERIA_EQUAL:
				break;

			case CRITERIA_WITHIN:
				break;

			case CRITERIA_GREATER:
				break;

			case CRITERIA_EQGREATER:
				break;

			case CRITERIA_LESS:
				break;

			case CRITERIA_EQLESS:
				break;
			}
			break;
		case COMPARE_BEFORE_CLOCKTIME:
			switch (rule.Criteria) {
			case CRITERIA_EQUAL:
				break;

			case CRITERIA_WITHIN:
				break;

			case CRITERIA_GREATER:
				break;

			case CRITERIA_EQGREATER:
				break;

			case CRITERIA_LESS:
				break;

			case CRITERIA_EQLESS:
				break;
			}
			break;
		case COMPARE_BEFORE_ACTIVITY:
			switch (rule.Criteria) {
			case CRITERIA_EQUAL:
				break;

			case CRITERIA_WITHIN:
				break;

			case CRITERIA_GREATER:
				break;

			case CRITERIA_EQGREATER:
				break;

			case CRITERIA_LESS:
				break;

			case CRITERIA_EQLESS:
				break;
			}
			break;
		case COMPARE_CUMUL_ACTIVITYTIME:
			switch (rule.Criteria) {
			case CRITERIA_EQUAL:
				break;

			case CRITERIA_WITHIN:
				break;

			case CRITERIA_GREATER:
				break;

			case CRITERIA_EQGREATER:
				break;

			case CRITERIA_LESS:
				break;

			case CRITERIA_EQLESS:
				break;
			}
			break;
	}
}
CONFLICT_STATUS ValidateConflict(SCHEDLIST*schedules, RULE rule, int*ReturnedThreshold);