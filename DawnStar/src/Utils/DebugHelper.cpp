#include "dspch.h"
#include "DebugHelper.h"

DebugHelper::Color DebugHelper::m_printColor = DebugHelper::Color::White;
std::string DebugHelper::m_colorHead = "\033[40;";
std::string DebugHelper::m_colorTail = "\033[0m";

std::stringstream DebugHelper::m_strStream;
int DebugHelper::m_argsCount = -1;