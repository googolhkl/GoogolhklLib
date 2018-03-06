#pragma once
#include "stdafx.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#pragma comment(lib, "Winmm.lib")

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <MSWSock.h>
#include <mmsystem.h>
#include <WS2spi.h>
#include <mstcpip.h>

#include <Windows.h>
#include <iostream>
#include <io.h>
#include <cstdlib>
#include <stdio.h>
#include <cstdint>

#include <assert.h>
#include <fcntl.h>
#include <algorithm>
#include <functional>
#include <array>
#include <map>

#include <thread>
#include <mutex>
#include <memory>

#include <string>
#include <tchar.h>

#include <ctime>
#include <random>
#include <typeinfo>

#if _DEBUG
#define CONTEXT_SWITCH Sleep(1)
#else
#define CONTEXT_SWITCH ::SwitchToThread
#endif

typedef void(*Function)(void *);  // Function f; 와 같은 문장은 void(*f)(void *)와 같이 해석

// 필수 헤더파일
#include "./Util/Type.h"
#include "./Util/Util.h"
#include "./Util/Singleton.h"
#include "./Util/RandomMT.h"
#include "./Util/Clock.h"
#include "./Util/Lock.h"
#include "./Util/Thread.h"
#include "./Util/Assert.h"
#include "./Util/Minidump.h"
#include "./Util/GameObject.h"
#include "./Util/Task.h"
#include "./Util/Monitoring.h"

// 전역 변수
#include "Shutdown.h"