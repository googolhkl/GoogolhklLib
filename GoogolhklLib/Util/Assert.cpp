#include "Assert.h"

namespace spd = spdlog;
void Assert(int condition, const WCHAR *conditionStr, const WCHAR *fileName, int lineNo)
{
	if (condition)
	{
		return;
	}

	wstr_t msg;
	msg = L"Assert: ";
	msg += conditionStr;
	msg += L", file : ";
	msg += fileName;
	msg += L", line : ";

	WCHAR buf[16];
	_itow_s(lineNo, buf, 10);
	msg += buf;
	spd::get("console")->error(L"! error {}", msg);
}
