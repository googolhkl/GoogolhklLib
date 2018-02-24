#include "stdafx.h"
#include "Clock.h"

Clock::Clock()
{
	mServerStartTick = this->SystemTick();
}

Clock::~Clock() {}

tick_t Clock::GetServerStartTick()
{
	return mServerStartTick;
}

tick_t Clock::SystemTick()
{
	return system_clock::to_time_t(system_clock::now());
}

tick_t Clock::StrToTick(wstr_t str, WCHAR *fmt)
{
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;

	swscanf_s(str.c_str(), fmt, &year, &month, &day, &hour, &minute, &second);

	tm time = { second, minute, hour, day, month - 1, year - 1900 };

	return mktime(&time);
}

wstr_t Clock::NowTime(WCHAR *fmt)
{
	return this->tickToStr(this->SystemTick(), fmt);
}

wstr_t Clock::NowTimeWithMilliSec(WCHAR *fmt)
{
#if 0
	timePoint now = system_clock::now();
	timePoint oldSecond = system_clock::from_time_t(this->systemTick());

	duration<double> milliSecond = now - oldSecond;
	array<WCHAR, SIZE_8> milliStr;
	snwprintf(milliStr, L"%03d", (int)(milliSecond.count() * 1000));
#else
	high_resolution_clock::time_point point = high_resolution_clock::now();
	milliseconds ms = duration_cast<milliseconds>(point.time_since_epoch());

	seconds s = duration_cast<seconds>(ms);
	tick_t t = s.count();
	std::size_t fractionalSeconds = ms.count() % 1000;
	array<WCHAR, SIZE_8> milliStr;
	snwprintf(milliStr, L"%03d", (int)(fractionalSeconds));
#endif
	wstr_t timeString = this->tickToStr(this->SystemTick(), fmt);
	timeString += L".";
	timeString += milliStr.data();
	return timeString;
}

wstr_t Clock::Today()
{
	return this->tickToStr(this->SystemTick(), DATE_FORMAT);
}

wstr_t Clock::Tomorrow()
{
	return this->tickToStr(this->SystemTick() + DAY_TO_TICK(1), DATE_FORMAT);
}

wstr_t Clock::Yesterday()
{
	return this->tickToStr(this->SystemTick() - DAY_TO_TICK(1), DATE_FORMAT);
}

DayOfWeek Clock::TodayOfWeek()
{
	tm time;
	tick_t tick = this->SystemTick();
	localtime_s(&time, &tick);
	return (DayOfWeek)time.tm_wday;
}

wstr_t Clock::tickToStr(tick_t tick, WCHAR *fmt)
{
	array<WCHAR, SIZE_128> timeStr;

	tm time;
	localtime_s(&time, &tick);
	wcsftime(timeStr.data(), timeStr.size(), fmt, &time);

	WCHAR* a = timeStr.data();
	return a;
}