#include "boost/algorithm/string.hpp"
#include "boost/log/trivial.hpp"

#include "LogFileHandler.h"
#include "CookieMetadataBuilder.h"

namespace cookie {

    LogFileHandler::LogFileHandler(const std::string& logFile) :
        m_logFileHandle(logFile.c_str())
    {
        if (!m_logFileHandle.good())
        {
            BOOST_LOG_TRIVIAL(error) << "Cannot open log file : " << logFile;
            throw std::invalid_argument("Cannot open file : " + logFile);
        }
        // skip first line
        std::string currLine;
        std::getline(m_logFileHandle, currLine);
    }

    bool LogFileHandler::next(CookieMetadata** metadata)
    {
        std::string currLine;
        if (std::getline(m_logFileHandle, currLine))
        {
            std::vector<std::string> details;
            boost::split(details, currLine, boost::is_any_of(","));
            if (details.size() != 2)
            {
                BOOST_LOG_TRIVIAL(error) << "error encountered while parsing line : " << currLine;
                throw std::length_error(std::string("Cannot parse line : " + currLine));
            }

            *metadata = CookieMetadataBuilder().SetIdentifier(details[0]).SetAccessTime(details[1]).GetCookie();
            return true;
        }
        else
        {
            return false;
        }
    }

    LogFileHandler::~LogFileHandler()
    {
        m_logFileHandle.close();
    }
}