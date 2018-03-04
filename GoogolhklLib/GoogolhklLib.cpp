// GoogolhklLib.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <vld.h>  // 메모리 누수 체크
// 테스트 코드
#include "GoogolhklLib.h"
#include "Util\spdlog\spdlog.h"

namespace spd = spdlog;
int main() {
	// Clock 테스트
	printf("어제: %ws\n", CLOCK->Yesterday().c_str());
	printf("오늘: %ws\n", CLOCK->Today().c_str());
	printf("내일: %ws\n", CLOCK->Tomorrow().c_str());
	printf("오늘 요일은 %d입니다.\n", CLOCK->TodayOfWeek());

	// spdlog 테스트
	auto console = spd::stdout_color_mt("console");
	console->info("Welcome to spdlog!");
	console->error("Some error message with arg{}..", 1);
	console->warn("Easy padding in numbers like {:08d}", 12);
	console->critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
	console->info("Support for floats {:03.2f}", 1.23456);
	console->info("Positional args are {1} {0}..", "too", "supported");
	console->info("{:<30}", "left aligned");


	ASSERT(1 != 1);
    return 0;
}

