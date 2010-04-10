#include "ResourceManager.h"

namespace OOS
{
	
	ResourceManager::ResourceManager(std::string RootScanDirectory, bool AutomaticallyLoadResources)
	{
		//Get the total available memory
		LPMEMORYSTATUS MemoryStatus;
		GlobalMemoryStatus(MemoryStatus);
		m_MaxMemoryUsage = MemoryStatus->dwAvailPhys;

		//Scan the root directory for all objects and load them into memory if
		//they can be parsed
		char tempPath[MAX_PATH];
		WIN32_FIND_DATA FindData;
		sprintf(tempPath, "%s\\*", RootScanDirectory.c_str());
		HANDLE Find = FindFirstFile(tempPath, &FindData);

		do
		{
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// Print the directory names
			}
			else
			{
				// Found a file, add it to the vector of files and parse the file
			}
		}
		while (FindNextFile(Find, &FindData) != 0);

		if (GetLastError() != ERROR_NO_MORE_FILES) 
		{
			//An error has occured whilst scaning the directory
		}

		//Close the file now that we are done with it
		FindClose(Find);

	}

	ResourceManager::~ResourceManager()
	{

	}
}