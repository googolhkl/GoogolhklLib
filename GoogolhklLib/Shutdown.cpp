#include "stdafx.h"
#include "Shutdown.h"

namespace spd = spdlog;
bool _shutdown = false;
void ShutdownServer()
{

	/* TODO
		현재 접속중 모든 유저 세션 종료
		서버 데이터 정리(랭킹등)
		std::thread core()
		core.join();
		DB 커넥션 종료
	*/
}
