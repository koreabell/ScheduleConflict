#include "DataProcessor.h"


ACTIVITY * GetFirstActivityInRange(SCHEDLIST * activity, RULE rule)
{
	time_t compareFrom = 0;
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
			
			break;
		case TIMEUNIT_HOUR:
			break;
		case TIMEUNIT_DAY:
			break;
		case TIMEUNIT_WEEK:
			break;
		case TIMEUNIT_MONTH:
			break;
		case TIMEUNIT_CALMONTH:
			break;
	}
}
