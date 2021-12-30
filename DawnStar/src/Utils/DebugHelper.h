#pragma once
#include <iostream>
#include <sstream>
#include <stdarg.h>

class DebugHelper {
public:
	template<typename... Types>
	static void PrintMsg(const std::string& format, Types ...args) {
#if DEBUG
		m_argsCount = sizeof...(args) - 1;
		std::string temp = format;
		m_printColor = Color::Green;
		Print(temp, args...);
#endif
	}

	template<typename... Types>
	static void PrintWarning(const std::string& format, Types ...args) {
#if DEBUG
		m_argsCount = sizeof...(args) - 1;
		std::string temp = format;
		m_printColor = Color::Yellow;
		Print(temp, args...);
#endif
	}

	template<typename... Types>
	static void PrintError(const std::string& format, Types ...args) {
#if DEBUG
		m_argsCount = sizeof...(args) - 1;
		std::string temp = format;
		m_printColor = Color::Red;
		Print(temp, args...);
#endif
	}

private:
	template<typename T, typename... Types>
	static void Print(std::string& format, T& first, Types& ...args) {
		// 当前要匹配的参数
		std::string pattern;
		m_strStream << "{";
		m_strStream << m_argsCount - sizeof...(args);
		m_strStream << "}";
		m_strStream >> pattern;
		ClearStrStream();

		bool isExist = false;
		size_t pos;
		size_t lastPos = 0;
		while ((pos = format.find(pattern)) != std::string::npos) {
			isExist = true;
			m_strStream << format.substr(lastPos, pos - lastPos);
			m_strStream << first;
			lastPos += pos + pattern.size();

			m_strStream << format.substr(lastPos, format.size() - lastPos);
			format = m_strStream.str();
			ClearStrStream();
		}

		// 若不存在匹配的参数，则输出错误
		if (!isExist && m_argsCount != -1) {
			PrintError("error");
		}
		// 递归调用
		Print(format, args...);
	}

	static void Print(const std::string& format) {
		m_argsCount = -1;
		std::string result;
		m_strStream << m_colorHead << (int)m_printColor << "m" << format << m_colorTail;
		result = m_strStream.str();
		ClearStrStream();
		std::cout << result << std::endl;
	}

	static void ClearStrStream() {
		m_strStream.clear();
		m_strStream.str("");
	}

private:
	enum class Color {
		White = 0,
		Green = 32,
		Yellow = 33,
		Red = 31
	};
	static Color m_printColor;

	static std::string m_colorHead;
	static std::string m_colorTail;
private:
	static std::stringstream m_strStream;
	static int m_argsCount;
};

// condition 为 bool 表达式，format 为格式化字符串
#define DS_ASSERT_CORE(condition, format, ...)		\
if(!(condition)) {		\
	DebugHelper::PrintError((std::string("Core Assertion Failed, File:{0}, Line:{1}")), __FILE__, __LINE__); \
	DebugHelper::PrintError(format, __VA_ARGS__);		\
	__debugbreak();		\
}
//#define DS_ASSERT_CLIENT(condition, format, ...)	if(!(condition)) { DebugHelper::PrintError((std::string("Client Assertion Failed, File:{0}, Line:{1}") + format), __FILE__, __LINE__, __VA_ARGS__);	__debugbreak();}