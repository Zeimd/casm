
#include <windows.h>

#include "timerlib.h"

double Timer()
{
	LARGE_INTEGER ticks_sec;
	LARGE_INTEGER ticks;
	double result;
	double ticksec;
	double tickcount;
		
	QueryPerformanceFrequency(&ticks_sec);
	QueryPerformanceCounter(&ticks);
		
	tickcount = ticks.QuadPart;
	ticksec = ticks_sec.QuadPart;
	result = tickcount/ticksec;
	return result;
}
	
void Wait(double seconds)
{
	double starttime;
	double time;
	
	starttime = Timer();
	do
	{
		time = Timer();			
	}while(time <= starttime+seconds);
}

