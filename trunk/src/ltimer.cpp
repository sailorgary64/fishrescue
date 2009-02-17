/* ----------------------------------------------------------------------------
Copyright (c) 1999-2002, Lev Povalahev
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, 
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, 
      this list of conditions and the following disclaimer in the documentation 
      and/or other materials provided with the distribution.
    * The name of the author may not be used to endorse or promote products 
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------*/

#include "ltimer.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
//#include <stdio.h>
#include <string.h>
#include <math.h>
#endif

#include <stdio.h>

//----------------------------------------------------

static bool timerInitialized = false;
static LTimer globalTimer;

LTimer* Timer()
{
    if (!timerInitialized)
    {    
        globalTimer.Initialize();
        timerInitialized = true;
    }
    return &globalTimer;
}
    

//----------------------------------------------------


LTimer::LTimer()
{
    m_ticks = 0;
    m_frequency = 0;
}

LTimer::~LTimer()
{

}

/** update the rtdcs counter */
int64 LTimer::UpdateTicks()
{
#ifdef _WIN32
    LARGE_INTEGER i;
    QueryPerformanceCounter(&i);
    return i.QuadPart;
#else
    int64 x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
#endif
}

/** this is called to get the frequency, normally /proc/cpuinfo if used,
if this file cant be opened the func measures the time for 5 seconds to 
find out the resolution */
void LTimer::UpdateFrequency()
{
#ifdef _WIN32
    LARGE_INTEGER i;
    QueryPerformanceFrequency(&i);
    m_frequency = i.QuadPart;
    if (m_frequency == 0)
        printf("LTimer::UpdateFrequency: could not determine the timer frequency\n");
#else
    FILE *f;
    float tmp = 0;
    char s[256];

    if ((f = fopen("/proc/cpuinfo", "r")) != 0)
    {
        while(fgets(s,sizeof(s),f)!=0)
        {
            if(strstr(s,"cpu MHz"))
            {
		        sscanf(strchr(s,':')+1, "%e", &tmp);
		        break;
		    }
        }
    }

    if (f)
        fclose(f);

    if (fabs(tmp)<0.01)
        printf("Could not detect processor speed\n");
    else
        m_frequency = (int64)(tmp*1000000.0);
#endif
}

/** UpdateFrequency is called here */
void LTimer::Initialize()
{
    UpdateFrequency();
    m_oldTicks = UpdateTicks();
}

/** returns UpdateTicks() */
int64 LTimer::GetTicks()
{
    return UpdateTicks();
}

/** returns time in seconds */
float LTimer::GetTime()
{
    return ((float)(UpdateTicks())/(float)m_frequency);
}

/** returns time since last TimeElapsed call, in microseconds */
float LTimer::TimeElapsed()
{
    return (float)m_ticks/(float)m_frequency;
}

/** returns the processor frequency */
int64 LTimer::GetFrequency()
{
    return m_frequency;
}

/** returns the time elapsed from the last call in seconds */
int LTimer::GetFPS()
{
    return (int)(1/TimeElapsed());
}

void LTimer::NewFrame()
{
    m_ticks = UpdateTicks() - m_oldTicks;
    m_oldTicks = UpdateTicks();
}

void LTimer::SetReference()
{
	m_oldTicks = UpdateTicks();
}

float LTimer::SinceReference(){
	return (float)(UpdateTicks() - m_oldTicks)/(float)m_frequency;
}
