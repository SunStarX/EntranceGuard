#include "TimeSoft.h"

s64_Systime OSTime = 0;


void MillisecondCount()
{
	OSTime++;
}

bool knlChkTimeOut(s64_Systime* targetTime)
{
    bool res;
    if(*targetTime == 0)return true;
    res = (OSTime - *targetTime) >= 0 ? true : false;
    if(res)*targetTime = 0;
    return res;
}

s64_Systime knlGetTargetTime(uint32_t msTime)
{
    s64_Systime tmp;
    tmp = OSTime + msTime;
    if(tmp == 0)tmp = 1;
    return tmp;
}

