/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "mapsbrowser.h"

#ifdef _WIN32
#include <Windows.h>
#endif

MapsBrowser::MapsBrowser(void):
	m_searchPattern("Content/Maps/*.map")	
{
}


MapsBrowser::~MapsBrowser(void)
{
}

void MapsBrowser::Initialize()
{
#ifdef _WIN32
	WIN32_FIND_DATAA findData;

	HANDLE hFind = FindFirstFileA(m_searchPattern, &findData);

	do
	{
		m_mapFiles.push_back(findData.cFileName);
	}
	while (FindNextFileA(hFind, &findData) != 0);

	FindClose(hFind);
#endif
}

const char* MapsBrowser::MapsDirectory = "Content/Maps/";