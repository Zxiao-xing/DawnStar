#pragma once

#include <fstream>

namespace DawnStar {
	class FileManager {
	public:
		static std::string ReadFile(const std::string& filePath);
	};
}