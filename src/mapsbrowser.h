/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _MAPSBROWSER_H_
#define _MAPSBROWSER_H_

#include <vector>
#include <string>
#include <cassert>

class MapsBrowser
{
	// Constant storing the maps' path
	const char* m_searchPattern;

	// The strings with the map names
	std::vector<std::string> m_mapFiles;
public:

	static const char* MapsDirectory;

	MapsBrowser(void);
	~MapsBrowser(void);

	// Init the members
	void Initialize();

	// Get the number of maps
	int GetNumMaps() { return m_mapFiles.size(); }

	// Get a specific map
	std::string& GetMap(unsigned int index)
	{
		if (index < m_mapFiles.size())
		{
			return m_mapFiles[index];
		}
		
		assert(false);

		return m_mapFiles[0];
	}
};

#endif // _MAPSBROWSER_H_