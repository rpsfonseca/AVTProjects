#pragma once

#include "StringUtils.h"

#include <string>
#include <vector>

namespace AVTEngine
{
	class FileSystem
	{
	private:
		static std::string runningDir;
	public:
		FileSystem();

		static std::string getRunningDirectory(char* runningPath);
		static std::string getResourcesDirectory();
	};
}