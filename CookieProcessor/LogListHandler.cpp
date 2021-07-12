#include "boost/algorithm/string.hpp"
#include "boost/log/trivial.hpp"

#include "LogListHandler.h"
#include "CookieMetadataBuilder.h"

namespace cookie {
    namespace test {
        
        LogListHandler::LogListHandler(std::list<std::string> cookieList) :
            m_logLists(cookieList),
            m_logListIter(m_logLists.begin())
        {
            m_logListIter++;
        }

        bool LogListHandler::next(CookieMetadata** metadata)
        {
            std::string currLine;
            if (m_logListIter != m_logLists.end())
            {
                currLine = *m_logListIter;
                m_logListIter++;

                std::vector<std::string> details;
                boost::split(details, currLine, boost::is_any_of(","));
                if (details.size() != 2)
                {
                    BOOST_LOG_TRIVIAL(error) << "error encountered while parsing line : " << currLine;
                    throw std::length_error(std::string("Cannot parse line : " + currLine));
                }

                *metadata = cookie::CookieMetadataBuilder().SetIdentifier(details[0]).SetAccessTime(details[1]).GetCookie();
                return true;
            }
            return false;
        }

        LogListHandler::~LogListHandler()
        {

        }
    }
}