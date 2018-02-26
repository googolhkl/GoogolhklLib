#pragma once
#include "stdafx.h"
#include <chrono>
#include <ctime>

#define CLOCK Clock::GetInstance()
#define NOW_TICK CLOCK->SystemTick
#define NOW_STRING CLOCK->NowTime

#define TICK_MIN (60)
#define TICK_HOUR (TICK_MIN * 60)
#define TICK_DAY (TICK_HOUR * 24)

#define TICK_TO_MIN(x) (x / TICK_MIN)
#define MIN_TO_TICK(x) (x * TICK_MIN)

#define TICK_TO_HOUR(x) (x / TICK_HOUR)
#define HOUR_TO_TICK(x) (x * TICK_HOUR)

#define TICK_TO_DAY(x) (x / TICK_DAY)
#define DAY_TO_TICK(x) (x * TICK_DAY)

typedef enum
{
	SUNDAY = 0,
	MONDAY = 1,
	TUESDAY = 2,
	WEDNESDAY = 3,
	THURSDAY = 4,
	FRIDAY = 5,
	SATURDAY = 6,
}DayOfWeek;

#define DATETIME_FORMAT L"%Y-%m-%d %H:%M:%S"
#define DATE_FORMAT L"%Y-%m-%d"
#define TIME_FORMAT L"%H:%M:%S"
#define DB_TIME_FORMAT L"%4d-%2d-%2d %2d:%2d:%2d"

using namespace std::chrono;
using namespace std;
typedef system_clock::time_point timePoint;

class Clock : public Singleton<Clock>
{
public:
	Clock();
	~Clock();

	tick_t GetServerStartTick();
	tick_t SystemTick();
	tick_t StrToTick(wstr_t str, WCHAR *fmt = DB_TIME_FORMAT);

	wstr_t NowTime(WCHAR *fmt = DATETIME_FORMAT);
	wstr_t NowTimeWithMilliSec(WCHAR *fmt = DATETIME_FORMAT);

	wstr_t Today();
	wstr_t Tomorrow();
	wstr_t Yesterday();

	DayOfWeek TodayOfWeek();
private:
	tick_t mServerStartTick;
	wstr_t tickToStr(tick_t tick, WCHAR *fmt = DATETIME_FORMAT);


};