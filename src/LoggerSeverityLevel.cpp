/**
* @file LoggerSeverityLevel.cpp
*/

#include "../include/LoggerSeverityLevel.hpp"

namespace ClustererBackend
{

std::string severityLevelToString(const SeverityLevel severityLevel)
{
    switch (severityLevel)
    {
        case SeverityLevel::ALL:
            return "ALL";
            break;
        case SeverityLevel::INFO:
            return "INFO";
            break;
        case SeverityLevel::WARNING:
            return "WARNING";
            break;
        case SeverityLevel::SEVERE:
            return "SEVERE";
            break;
        case SeverityLevel::ERROR:
            return "ERROR";
            break;
        case SeverityLevel::OFF:
            return "OFF";
            break;
        default:
            return "";
            break;
    }
}

bool checkSeverityTypeMatch(const SeverityLevel severityLevel, const SeverityType severityType)
{
    switch (severityLevel)
    {
        case SeverityLevel::ALL:
            if (severityType == SeverityType::DEBUG)
            {
                return true;
                break;
            }
        case SeverityLevel::INFO:
            if (severityType == SeverityType::INFO)
            {
                return true;
                break;
            }
        case SeverityLevel::WARNING:
            if (severityType == SeverityType::WARNING)
            {
                return true;
                break;
            }
        case SeverityLevel::SEVERE:
            if (severityType == SeverityType::SEVERE)
            {
                return true;
                break;
            }
        case SeverityLevel::ERROR:
            if (severityType == SeverityType::ERROR)
            {
                return true;
                break;
            }

        default:
            return false;
            break;
    }
}

}
