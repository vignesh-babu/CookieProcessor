#pragma once
#include <string>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/log/trivial.hpp"

namespace cookie {
    namespace parse_helper {

        inline boost::posix_time::ptime GetAccessTime(const std::string& accessTimeStr)
        {
            // remove +/- 00:00 as time is represented in UTC
            auto accessTimeStrFormated = accessTimeStr.substr(0, accessTimeStr.size() - 6);

            boost::posix_time::ptime cookieAccessTime = boost::posix_time::from_iso_extended_string(accessTimeStrFormated);
            BOOST_LOG_TRIVIAL(trace) << "parsing string - " << accessTimeStr << " as : " << boost::posix_time::to_iso_extended_string(cookieAccessTime);
            return cookieAccessTime;
        }

        inline boost::gregorian::date GetDate(const std::string& dateStr)
        {
            boost::gregorian::date cookieAccessDate = boost::gregorian::from_string(dateStr);
            BOOST_LOG_TRIVIAL(trace) << "parsing string - " << dateStr << " as : " << boost::gregorian::to_iso_extended_string(cookieAccessDate);
            return cookieAccessDate;
        }
    }
}