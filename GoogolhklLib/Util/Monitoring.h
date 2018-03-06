#pragma once
#include "stdafx.h"
#include "psapi.h"

class Monitoring : public Singleton<Monitoring>
{
public:
	Monitoring()
	{
		SYSTEM_INFO sysInfo;
		FILETIME ftime, fsys, fuser;

		GetSystemInfo(&sysInfo);
		mNumProcessors = sysInfo.dwNumberOfProcessors;

		GetSystemTimeAsFileTime(&ftime);
		memcpy(&mLastCPU, &ftime, sizeof(FILETIME));

		mSelf = GetCurrentProcess();
		GetProcessTimes(mSelf, &ftime, &ftime, &fsys, &fuser);
		memcpy(&mLastSysCPU, &fsys, sizeof(FILETIME));
		memcpy(&mLastUserCPU, &fuser, sizeof(FILETIME));
	}

	double processCpuUsage()
	{
		FILETIME ftime, fsys, fuser;
		ULARGE_INTEGER now, sys, user;
		double percent;

		GetSystemTimeAsFileTime(&ftime);
		memcpy(&now, &ftime, sizeof(FILETIME));

		GetProcessTimes(mSelf, &ftime, &ftime, &fsys, &fuser);
		memcpy(&sys, &fsys, sizeof(FILETIME));
		memcpy(&user, &fuser, sizeof(FILETIME));
		percent = (double)((sys.QuadPart - mLastSysCPU.QuadPart) + (user.QuadPart - mLastUserCPU.QuadPart));
		percent /= (now.QuadPart - mLastCPU.QuadPart);
		percent /= mNumProcessors;
		//		lastCPU = now;
		//		lastUserCPU = user;
		//		lastSysCPU = sys;
		percent = percent * 100;
		return fixInRange(0, percent, 100);
	}

	SIZE_T processMemUsage()
	{
		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		return (size_t)pmc.WorkingSetSize;
	}

	SIZE_T physyicMemUsage()
	{
		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);

		return (size_t)memInfo.ullTotalPhys - memInfo.ullAvailPhys;
	}
private:
	ULARGE_INTEGER mLastCPU, mLastSysCPU, mLastUserCPU;
	int mNumProcessors;
	HANDLE mSelf;
};
