#ifndef _CONFIGURATION_READER_WRITER_HPP
#define _CONFIGURATION_READER_WRITER_HPP

// standard headers
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <stdexcept>
// external headers

// internal headers

/**
* @class ConfigurationReaderWriter
* @brief Reads a configuration map from a file or writes it to a file.
* @details The class ConfigurationReaderWriter provides a convenient abstraction
* for reading and writing configuration files. A configuration file has the following
* form: (key separator value), where each of the three components is a string.
* Example configuration file line: value = 0
*/
class ConfigurationReaderWriter
{
public:
    /**
    * @brief Constructor for ConfigurationReaderWriter.
    * @param fullPathName The full path name.
    * @param commentCharacter The character which indicates a comment.
    * @param separatorString The string which indicates the separation between key and value.
    */
    ConfigurationReaderWriter(const std::string& fullPathName, char commentCharacter = '#', std::string separatorString = " = ");
    /**
    * @brief Default destructor for the ConfigurationReaderWriter.
    */
    ~ConfigurationReaderWriter();

    /**
    * @brief Loads the key value map from the file.
    * @return A unordered map with each key value pair which was found in 
    * the file.
    * @throws std::runtime_error
    */
    std::unordered_map<std::string, std::string> readConfiguration();
    /**
    * @brief Saves a key value map to the file.
    * @param outConfiguration The unordered map with each key value pair that should be saved
    * to the configuration file.
    * @return void
    * @throws std::runtime_error
    */
    void writeConfiguration(const std::unordered_map<std::string, std::string>& outConfiguration);

protected:
private:
    /**
    * @var fullPathName
    * @brief The full path name.
    * @details The full path to a file. This should include both the
    * absolute or relative directory and the filename and file extension of the
    * file.
    */
    std::string fullPathName;
    /**
    * @var commentCharacter
    * @brief The character which indicates a comment.
    * @details The character that indicates a comment. If this character is the
    * first character in a line then the line is disregarded.
    */
    char commentCharacter;
    /**
    * @var separatorString
    * @brief The string which indicates the separation between key and value.
    * @details This string is only used when outputting the file again. For input
    * any separation string is valid.
    */
    std::string separatorString;
};

#endif
