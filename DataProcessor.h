#pragma once
#ifndef DATA_PROCESSOR
#define DATA_PROCESSOR

#include "main.h"
#include <string.h>

ACTIVITY*GetFirstActivityInRange(SCHEDLIST*activity, RULE rule);

CONFLICT_STATUS ValidateConflict(ACTIVITY activity, RULE rule);
CONFLICT_STATUS ValidateConflict(ACTIVITY activity, RULE rule, int*Threshold);


#endif