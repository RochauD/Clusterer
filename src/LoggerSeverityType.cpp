/**
* @file LoggerSeverityType.cpp
*/

#include "../include/LoggerSeverityType.hpp"

std::string severityTypeToString(const SeverityType severityType)
{
    switch (severityType)
    {
        case SeverityType::INFO:
            return "INFO";
            break;
        case SeverityType::DEBUG:
            return "DEBUG";
            break;
        case SeverityType::WARNING:
            return "WARNING";
            break;
        case SeverityType::SEVERE:
            return "SEVERE";
            break;
        case SeverityType::ERROR:
            return "ERROR";
            break;
        default:
            return "";
            break;
    }
}
