#pragma once
#include <unordered_map>

#include "boost/container_hash/hash.hpp"

#include "ILogHandler.h"


namespace cookie
{
    struct DateHash
    {
        size_t operator()(boost::gregorian::date const& date) const
        {
            return boost::hash_value(date.julian_day());
        }
    };

    struct CookieInfo
    {
        CookieMetadata m_metadata;
        int m_occurences;

        std::string ToString();
    };

    class CookieProcessor
    {
    public:
        CookieProcessor(std::shared_ptr<cookie::ILogHandler>& logHandler);
        void process();
        std::list<std::string> GetActiveCookie(const std::string& date);

        std::string ToString();

    private:
        std::shared_ptr<cookie::ILogHandler>  m_logHandler;
        std::unordered_map<boost::gregorian::date, std::vector<CookieInfo>, DateHash> m_DateToCookieInfoMap;
    };
}