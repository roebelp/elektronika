/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"export.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	THREAD.CPP					(c)	YoY'01						WEB: search aestesis
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"thread.h"
#include						<windows.h>
#include						<assert.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static DWORD WINAPI ThreadProc(void *p)
{
	Athread	*t=(Athread *)p;
	t->run();
	CloseHandle(t->hThread);
	t->hThread=NULL;
	t->threadID=0;
	return 0;
}
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 ADLL Athread::Athread()
{
	hThread=NULL;
	threadID=0;
	priority=priorityNORMAL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Athread::~Athread()
{
	stop();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Athread::start()
{
	if(!hThread)
	{
		threadID=0;
		hThread=CreateThread(NULL, 0, ThreadProc, this, 0, &threadID);
		if(!hThread)
		{
			int err=GetLastError();
			assert(false);
		}
		return hThread!=NULL;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Athread::stop()
{
	if(hThread)
	{
		TerminateThread(hThread, 0);
		CloseHandle(hThread);
		hThread=NULL;
		threadID=0;
		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void Athread::sleep(int millis)
{
	Sleep(millis);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Athread::isRunning()
{
	return hThread!=NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void Athread::setPriority(int priority)
{
	switch(priority)
	{
		case priorityIDLE:
		if(SetThreadPriority(hThread, THREAD_PRIORITY_IDLE))
			this->priority=priority;
		break;
		case priorityLOW:
		if(SetThreadPriority(hThread, THREAD_PRIORITY_LOWEST))
			this->priority=priority;
		break;
		case priorityNORMAL:
		if(SetThreadPriority(hThread, THREAD_PRIORITY_NORMAL))
			this->priority=priority;
		break;
		case priorityHIGH:
		if(SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST))
			this->priority=priority;
		break;
		case prioritySPEED:
		if(SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL))
			this->priority=priority;
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL int Athread::getPriority()
{
	return priority;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void Athread::setAffinity(dword cpu)
{
	SetThreadAffinityMask(hThread, cpu);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void Athread::setClass(int c)
{
	HANDLE	hProcess=GetCurrentProcess();
	switch(c)
	{
		case classSLOW:
		SetPriorityClass(hProcess, BELOW_NORMAL_PRIORITY_CLASS);
		break;
		case classNORMAL:
		SetPriorityClass(hProcess, NORMAL_PRIORITY_CLASS);
		break;
		case classHIGH:
		SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
		break;
		case classREALTIME:
		SetPriorityClass(hProcess, REALTIME_PRIORITY_CLASS);
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL int Athread::getClass()
{
	HANDLE	hProcess=GetCurrentProcess();
	switch(GetPriorityClass(hProcess))
	{
		case IDLE_PRIORITY_CLASS:
		case BELOW_NORMAL_PRIORITY_CLASS:
		return classSLOW;
		
		default:
		case ABOVE_NORMAL_PRIORITY_CLASS:
		case NORMAL_PRIORITY_CLASS:
		return classNORMAL;
		
		case HIGH_PRIORITY_CLASS:
		return classHIGH;

		case REALTIME_PRIORITY_CLASS:
		return classREALTIME;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void Athread::setCurrentThreadPriority(int priority)
{
	HANDLE	hThread=GetCurrentThread();
	switch(priority)
	{
		case priorityIDLE:
		SetThreadPriority(hThread, THREAD_PRIORITY_IDLE);
		break;
		case priorityLOW:
		SetThreadPriority(hThread, THREAD_PRIORITY_LOWEST);
		break;
		case priorityNORMAL:
		SetThreadPriority(hThread, THREAD_PRIORITY_NORMAL);
		break;
		case priorityHIGH:
		SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST);
		break;
		case prioritySPEED:
		SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL double Athread::getCpuTime()
{
	FILETIME	create,exit,kernel,user;
	HANDLE		ht=GetCurrentThread();
	if(GetThreadTimes(ht, &create, &exit, &kernel, &user))
	{
		qword	t=QWORD(user.dwHighDateTime, user.dwLowDateTime)+QWORD(kernel.dwHighDateTime, kernel.dwLowDateTime);
		return (double)t*((100.0/1000000000.0)*1000.0);	// from 100 nanosecond to millisecond
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL double Athread::getTime()
{
	LARGE_INTEGER	freq;
	LARGE_INTEGER	time;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&time);
	return 1000.0*(double)time.QuadPart/(double)freq.QuadPart;
}

/*
	LARGE_INTEGER	freq;
	LARGE_INTEGER	time;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&time);
	double f=(double)freq.HighPart * 4294967296.0 + (double)freq.LowPart;
	double t=(double)time.HighPart * 4294967296.0 + (double)time.LowPart;
	return 1000.0*t/f;
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
