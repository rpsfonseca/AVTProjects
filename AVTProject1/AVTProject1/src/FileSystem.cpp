#include "FileSystem.h"

namespace AVTEngine
{
	std::string FileSystem::runningDir = "";

	FileSystem::FileSystem() {}

	std::string FileSystem::getRunningDirectory(char* runningPath)
	{
		std::string runningDirectory;
		std::vector<std::string> splittedString = splitString(runningPath, '\\');
		for (int i = 0; i < splittedString.size() - 1; i++)
		{
			runningDirectory += (splittedString[i] + "\\");
		}
		runningDir = runningDirectory;
		return runningDirectory;
	}

	std::string FileSystem::getResourcesDirectory()
	{
		std::string resourcesDir = runningDir + "..\\..\\..\\AVTProject1\\resources\\";
		return resourcesDir;
	}
}