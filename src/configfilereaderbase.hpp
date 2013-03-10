#ifndef _CONFIGFILEREADERBASE_H_
#define _CONFIGFILEREADERBASE_H_

#include <string>
#include <cstdio>

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!! FONTOS!!!!												!!!!!
// !!!! A config fájlok sorai végén WINDOWS végzõdés van (\r\n) !!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

template <typename T>
class ConfigFileReaderBase
{
protected:

	FILE* m_pTheFile;

	ConfigFileReaderBase(): m_pTheFile(NULL) { }

	virtual ~ConfigFileReaderBase()
	{
		if (m_pTheFile != NULL)
		{
			fclose(m_pTheFile);
		}
	}

	virtual T ParseRecord(std::string str) = 0;

public:
	
	bool OpenFile(std::string filename);

	T GetNextRecord();

	bool HasNextRecord();
};

template <typename T>
bool ConfigFileReaderBase<T>::OpenFile(std::string filename)
{
	m_pTheFile = fopen(filename.c_str(), "rt");

	// file open FAILURE
	if (m_pTheFile == NULL) { return false; }

	return true;
}

template <typename T>
T ConfigFileReaderBase<T>::GetNextRecord()
{
	std::string buffer;

	char buf[200];
	fgets(buf, 200, m_pTheFile);

	buffer.append(buf);
	buffer.pop_back();
	
	return ParseRecord(buffer);
}

template <typename T>
bool ConfigFileReaderBase<T>::HasNextRecord()
{
	long pos = ftell(m_pTheFile);

	char c;
	fread(&c, sizeof(char), 1, m_pTheFile);

	bool result = (feof(m_pTheFile) == 0);

	fseek(m_pTheFile, pos, SEEK_SET);

	return result;
}

#endif // _CONFIGFILEREADERBASE_H_