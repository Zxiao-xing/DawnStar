#include "dspch.h"
#include "FileManager.h"

namespace DawnStar {
	std::string FileManager::ReadFile(const std::string& filePath)
	{
		std::string result;
		std::ifstream fileReader(filePath, std::ios::in | std::ios::binary);
		if (fileReader) {
			fileReader.seekg(0, std::ios::end);
			result.resize(fileReader.tellg());
			fileReader.seekg(0, std::ios::beg);
			fileReader.read(&result[0], result.size());
			fileReader.close();
		}
		else {
			DebugHelper::PrintError("Could not open file: {0}", filePath);
		}
		return result;
	}

}
