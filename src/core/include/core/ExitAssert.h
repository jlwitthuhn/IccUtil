#pragma once

#include <functional>
#include <string>

namespace ExitAssert
{
	[[noreturn]] void assert_failed(const char* file, int line, const char* msg);
	void set_assert_callback(std::function<void(const std::string&)> callback);
}

#define EXIT_ASSERT(COND, MSG) if (!static_cast<bool>(COND)) { ExitAssert::assert_failed(__FILE__, __LINE__, MSG); }
