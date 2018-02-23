// GoogolhklLib.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

// 테스트 코드
#include "GoogolhklLib.h"
#include "Util\Type.h"
#include "Util\Util.h"
#include "Util\Singleton.h"
#include "Util\Clock.h"

int main() {
	printf("어제: %ws\n", CLOCK->yesterday().c_str());
	printf("오늘: %ws\n", CLOCK->today().c_str());
	printf("내일: %ws\n", CLOCK->tomorrow().c_str());
	printf("오늘 요일은 %d입니다.\n", CLOCK->todayOfWeek());
    return 0;
}

