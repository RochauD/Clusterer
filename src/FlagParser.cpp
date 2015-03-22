#include <getopt.h>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "../include/FlagParser.hpp"

namespace common {
namespace utils {


static void FlagParser::addFlag(const char shortOpt, const std::string& longOpt,
             bool optMandatory, bool argMandatory)
{

}

static int FlagParser::parse(const int argc, char* const argv[])
{
  return 0;
}

static bool FlagParser::hasArg(char shortOpt)
{
  return true;
}

static std::string FlagParser::getArg(char shortOpt)
{
  return shortOpt;
}

 static std::vector<std::string> FlagParser::getArgs(char shortOpt)
 {
  return shortOpt;
 }


static std::string FlagParser::getUsage()
{
  return "Usage message";
}

}  // namespace utils
}  // namespace common


