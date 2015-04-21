/**
 * @file FlagParser.hpp
 * @brief General purpose command line parsing utilities
 */
#ifndef CLUSTERER_COMMON_FLAG_PARSER_HPP
#define CLUSTERER_COMMON_FLAG_PARSER_HPP

// standard headers
#include <cstdint>
#include <map>
#include <string>
#include <vector>
// external headers

// internal headers


/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace backend
* @brief The namespace backend is the namespace for all backend components of the
* project.
*/
namespace common
{

/**
 * @struct FlagOpt
 * @brief characteristics of each flag passed to the program
 */
struct FlagOpt
{
    std::string longOpt;
    bool optMandatory;
    bool argMandatory;
    bool parsed;
};

/**
 * @class FlagParser
 * @brief a command line utility class for flag parsing
 */
class FlagParser
{
    private:
        static std::string _progName;
        static std::map<char, FlagOpt> _flagOpts;
        static std::map<char, std::vector<std::string>> _parsedArgs;
        static std::vector<std::string> _params;
        static uint32_t _minNumParams;
    public:
        /**
         * @brief add an expected flag
         * @param shortOpt short option
         * @param longOpt long optioon
         * @optMandatory true if the flag is mandatory, false otherwise
         * @argMandatory true if the flag requires an argument, false otherwise
         */
        static void addFlag(const char shortOpt, const std::string& longOpt,
                            bool optMandatory, bool argMandatory);
        /**
         * @brief set the minimum number of flags
         * @param minNumParams -1 if no flags are allowed
         *                      0 if flags are optional
         *                     >0 minimum number of flags
         */
        inline
        static void setMinNumParams(uint32_t minNumParams)
        {
            _minNumParams = minNumParams;
        }

        /**
         * @brief parse the command line arguments and check them against
         * previously addded flags
         * @param argc the argument count
         * @param argv the array of C strings containing the flags
         * @return 0 on success and non-zero on failure
         *
         * Note: this method will print usage and exit successfully if the "help"
         * flag is encountered
         */
        static int parse(const int argc, char* const argv[]);

        /**
         * @brief check if an argument was encountered for a flag
         * @param shortOpt the short option
         * @return true if the argument was encountered and false otherwise
         */
        static bool hasArg(char shortOpt);

        /**
         * @brief retrieve argument of a flag
         * @param shortOpt the short option for the flag
         * @return the argument
         */
        static std::string getArg(char shortOpt);

        /**
         * @brief retrieve arguments of a flag
         * @param shortOpt the short option for the flag
         * @return the arguments
         */
        static std::vector<std::string> getArgs(char shortOpt);

        /**
         * @brief get usage message
         * @return a string containing the usage message
         */
        static std::string getUsage();
};

}
}

/**
* @namespace clc
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clc = clusterer::common;

#endif
