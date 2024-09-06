#ifndef __TimeSoft_H
#define	__TimeSoft_H

#include <stdint.h>
#include <stdbool.h>

typedef int64_t  s64_Systime;


void MillisecondCount();
s64_Systime knlGetTargetTime(uint32_t msTime);
bool knlChkTimeOut(s64_Systime* targetTime);
#endif