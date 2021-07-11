#pragma once
#include<string>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

namespace cookie
{
    class CookieMetadata
    {
    public:
        void SetId(std::string id);
        void SetAccessTime(boost::posix_time::ptime accessTime);

        std::string GetId();
        boost::gregorian::date GetAccessDate();

        std::string ToString();

    private:
        std::string m_identifier;
        boost::posix_time::ptime m_accessTime;
    };
}