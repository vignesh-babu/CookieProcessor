#include "CookieProcessor.h"
#include "CookieParseHelper.h"

namespace cookie {

    CookieProcessor::CookieProcessor(std::shared_ptr<cookie::ILogHandler>& logHandler) :
        m_logHandler(logHandler)
    {}

    void CookieProcessor::process()
    {
        BOOST_LOG_TRIVIAL(debug) << "Starting to process logs from log handler";
        CookieMetadata* cMd;
        while (m_logHandler->next(&cMd))
        {
            if (m_DateToCookieInfoMap.find(cMd->GetAccessDate()) != m_DateToCookieInfoMap.end())
            {
                auto& cookieOccurences = m_DateToCookieInfoMap[cMd->GetAccessDate()];
                auto iter = std::find_if(cookieOccurences.begin(), cookieOccurences.end(), [&cMd](CookieInfo& cMd1)
                    {
                        return cMd->GetId() == cMd1.m_metadata.GetId();
                    });
                if (iter != cookieOccurences.end())
                {
                    iter->m_occurences++;
                }
                else
                {
                    cookieOccurences.push_back({ *cMd, 1 });
                }
            }
            else
            {
                m_DateToCookieInfoMap.insert({ cMd->GetAccessDate(), { {*cMd, 1} } });
            }
            delete cMd;
        }
        BOOST_LOG_TRIVIAL(info) << "Processed all lines from log handler. Unique Date Count - " << m_DateToCookieInfoMap.size();
        BOOST_LOG_TRIVIAL(debug) << ToString();
    }

    std::list<std::string> CookieProcessor::GetActiveCookie(const std::string& date)
    {
        BOOST_LOG_TRIVIAL(info) << "checking for date - " << date;

        auto iter = m_DateToCookieInfoMap.find(parse_helper::GetDate(date));

        if (iter != m_DateToCookieInfoMap.end())
        {
            auto info = std::max_element(iter->second.begin(), iter->second.end(), [](const CookieInfo& ci1, const CookieInfo& ci2) {
                return ci1.m_occurences < ci2.m_occurences;
                });
            if (info != iter->second.end())
            {
                std::list<std::string> result;
                std::for_each(iter->second.begin(), iter->second.end(), [&result, &info](CookieInfo& ci1) {
                    if (ci1.m_occurences == info->m_occurences)
                    {
                        result.push_back(ci1.m_metadata.GetId());
                    }
                });
                return result;
            }
            else
            {
                BOOST_LOG_TRIVIAL(warning) << "No Active Cookies present for the give date : " << date;
                return std::list <std::string>({ "Not Found" });
            }
        }
        else
        {
            BOOST_LOG_TRIVIAL(warning) << "No Entry found for date : " << date;
            return std::list <std::string>({ "Not Found" });
        }
    }

    std::string CookieProcessor::ToString()
    {
        std::string cookieProcessorState;
        cookieProcessorState.append("Cookies - ");
        for (auto& dateToCookies : m_DateToCookieInfoMap)
        {
            cookieProcessorState.append("[")
                .append("Date : ").append(boost::gregorian::to_iso_extended_string(dateToCookies.first)).append(", ");
            for (auto& info : dateToCookies.second)
            {
                cookieProcessorState.append(", ").append(info.ToString());
            }
            cookieProcessorState.append("], ");
        }

        return cookieProcessorState;
    }

    std::string CookieInfo::ToString()
    {
        return std::string("[")
            .append("Occurences : ").append(std::to_string(m_occurences)).append(", ")
            .append(m_metadata.ToString()).append("]");
    }
}