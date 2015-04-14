/**
 * @file ConfigurationReaderWriter.cpp
 * @brief File in which the ConfigurationReaderWriter is implemented.
 */
#include "../include/ConfigurationReaderWriter.hpp"

// internal headers
#include "../include/GlobalFileLogger.hpp"

namespace clusterer
{
namespace backend
{

ConfigurationReaderWriter::ConfigurationReaderWriter(const std::string& fullPathName, char commentCharacter, std::string separatorString)
{
    this->fullPathName = fullPathName;
    this->commentCharacter = commentCharacter;
    this->separatorString = separatorString;
}

ConfigurationReaderWriter::~ConfigurationReaderWriter()
{

}

std::unordered_map<std::string, std::string> ConfigurationReaderWriter::readConfiguration()
{
    std::unordered_map<std::string, std::string> configMap;
    std::ifstream file(this->fullPathName);
    std::string buffer;

    while (file.is_open() && std::getline(file, buffer))
    {
        if (!buffer.empty() && buffer[0] != this->commentCharacter)
        {
            std::stringstream sstream(buffer);
            std::string keyString;
            std::string seperatorString;
            std::string valueString;
            if (sstream >> keyString && sstream >> seperatorString && sstream >> valueString)
            {
                configMap[keyString] = valueString;
            }
            else
            {
                file.close();
                clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Invalid formatting of configuration file.");
                throw std::runtime_error("Error! Invalid formatting of configuration file.");
            }
        }
    }
    file.close();
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "Read configuration file succesfully. File: ", this->fullPathName);
    return configMap;
}

void ConfigurationReaderWriter::writeConfiguration(const std::unordered_map<std::string, std::string>& outConfiguration)
{
    std::ofstream file(this->fullPathName);
    for (auto& e : outConfiguration)
    {
        if (!(file << e.first << this->separatorString << e.second << '\n'))
        {
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Failed writing configuration file due to invalid output configuration.");
            throw std::runtime_error("Error! Writing output file.");
        }
    }
    if (file.bad() || file.fail())
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Failed writing configuration file.");
        throw std::runtime_error("Error! Failed writing configuration file.");
    }
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "Wrote configuration file succesfully. File: ", this->fullPathName);
}

}
}
