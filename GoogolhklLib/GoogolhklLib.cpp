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
	printf("어제: %ws\n", CLOCK->Yesterday().c_str());
	printf("오늘: %ws\n", CLOCK->Today().c_str());
	printf("내일: %ws\n", CLOCK->Tomorrow().c_str());
	printf("오늘 요일은 %d입니다.\n", CLOCK->TodayOfWeek());
    return 0;
}

