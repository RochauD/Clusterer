#ifndef _CONFIGURATION_READER_WRITER_HPP
#define _CONFIGURATION_READER_WRITER_HPP

#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <stdexcept>

class ConfigurationReaderWriter
{
public:
	ConfigurationReaderWriter(const std::string& fullPathName, char commentCharacter = '#');
	~ConfigurationReaderWriter();

	std::unordered_map<std::string, std::string> readConfiguration();
	void writeConfiguration(const std::unordered_map<std::string, std::string>& outConfiguration);

protected:
private:
	std::string fullPathName;
	char commentCharacter;
};

#endif
