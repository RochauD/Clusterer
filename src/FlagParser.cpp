#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "../include/FlagParser.hpp"

namespace common
{
namespace utils
{


void FlagParser::addFlag(const char shortOpt, const std::string& longOpt,
                         bool optMandatory, bool argMandatory)
{

}

int FlagParser::parse(const int argc, char* const argv[])
{
    return 0;
}

bool FlagParser::hasArg(char shortOpt)
{
    return true;
}

std::string FlagParser::getArg(char shortOpt)
{
    return "";
}

std::vector<std::string> FlagParser::getArgs(char shortOpt)
{
    std::vector<std::string> a;
    return a;
}


std::string FlagParser::getUsage()
{
    return "Usage message";
}

}  // namespace utils
}  // namespace common


