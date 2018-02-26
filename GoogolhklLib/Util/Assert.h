#pragma once
#include "stdafx.h"
#include "Util\spdlog\spdlog.h"
#include "Util\spdlog\details\logger_impl.h"

#undef ASSERT
#define ASSERT(x) Assert(x, _W(#x), _W(__FILE__), __LINE__)

void Assert(int condition, const WCHAR *conditionStr, const WCHAR *fileName, int lineNo);