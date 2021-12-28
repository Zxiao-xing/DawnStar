#pragma once
#include <iostream>
#include <stdarg.h>

class DebugHelper {
public:

	static void PrintMsg(const std::string& format, ...) {
#if DEBUG
		va_list args;
		va_start(args, format);
		vprintf(("\033[40;32m" + format + "\033[0m\n").c_str(), args);
		va_end(args);
#endif
	}

	static void PrintWarning(const std::string& format, ...) {
#if DEBUG
		va_list args;
		va_start(args, format);
		vprintf(("\033[40;33m" + format + "\033[0m\n").c_str(), args);
		va_end(args);
#endif
	}

	static void PrintError(const std::string& format, ...) {
#if DEBUG
		va_list args;
		va_start(args, format);
		vprintf(("\033[40;31m" + format + "\033[0m\n").c_str(), args);
		va_end(args);
#endif
	}
};

// condition 为 bool 表达式，format 为格式化字符串
#define DS_ASSERT_CORE(condition, format, ...)		if(!(condition)) { DebugHelper::PrintError((std::string("Core Assertion Failed, File:{0}, Line:{1}\n\t") + format), __FILE__, __LINE__, __VA_ARGS__);	__debugbreak();}
#define DS_ASSERT_CLIENT(condition, format, ...)	if(!(condition)) { DebugHelper::PrintError((std::string("Client Assertion Failed, File:{0}, Line:{1}\n\t") + format), __FILE__, __LINE__, __VA_ARGS__);	__debugbreak();}