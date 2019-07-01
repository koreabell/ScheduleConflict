#pragma once
#ifndef DATA_PROCESSOR
#define DATA_PROCESSOR

#include "main.h"
#include <string.h>

SCHEDLIST*GetFirstActivityInRange(SCHEDLIST*activity, RULE rule);

CONFLICT_STATUS ValidateConflict(SCHEDLIST*schedules, RULE rule);
CONFLICT_STATUS ValidateConflict(SCHEDLIST*schedules, RULE rule, int*ReturnedThreshold);


#endif