#pragma once
#include "stdafx.h"
#include <chrono>
#include <ctime>

#define CLOCK Clock::getInstance()
#define NOW_TICK CLOCK.systemTick
#define NOW_STRING CLOCK.nowTime

#define TICK_MIN (60)
#define TICK_HOUR (TICK_MIN * 60)
#define TICK_DAY (TICK_HOUR * 24)

#define TICK_TO_MIN(x) (x / TICK_MIN)
#define MIN_TO_TICK(x) (x * TICK_MIN)

#define TICK_TO_HOUR(x) (x / TICK_HOUR)
#define HOUR_TO_TICK(x) (x * TICK_HOUR)

#define TICK_TO_DAY(x) (x / TICK_DAY)
#define DAY_TO_TICK(x) (x * TICK_DAY)

typedef enum {
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

class Clock : public Singleton<Clock> {
private:
	tick_t serverStartTick_;
	wstr_t tickToStr(tick_t tick, WCHAR *fmt = DATETIME_FORMAT);

public:
	Clock();
	~Clock();

	tick_t serverStartTick();
	tick_t systemTick();
	tick_t strToTick(wstr_t str, WCHAR *fmt = DB_TIME_FORMAT);

	wstr_t nowTime(WCHAR *fmt = DATETIME_FORMAT);
	wstr_t nowTimeWithMilliSec(WCHAR *fmt = DATETIME_FORMAT);

	wstr_t today();
	wstr_t tomorrow();
	wstr_t yesterday();

	DayOfWeek todayOfWeek();
};