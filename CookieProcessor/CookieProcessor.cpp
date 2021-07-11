#include "CookieProcessor.h"
#include "CookieParseHelper.h"

namespace cookie {

    CookieProcessor::CookieProcessor(ILogHandler* logHandler) :
        m_logHandler(std::unique_ptr<ILogHandler>(logHandler))
    {}

    void CookieProcessor::process()
    {
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
        }
    }

    std::string CookieProcessor::GetActiveCookie(const std::string& date)
    {
        auto iter = m_DateToCookieInfoMap.find(parse_helper::GetDate(date));

        if (iter != m_DateToCookieInfoMap.end())
        {
            auto info = std::max_element(iter->second.begin(), iter->second.end(), [](const CookieInfo& ci1, const CookieInfo& ci2) {
                return ci1.m_occurences < ci2.m_occurences;
                });
            if (info != iter->second.end())
            {
                return info->m_metadata.GetId();
            }
            else
            {
                return "No Active Cookies present for the give date";
            }
        }
        else
        {
            return "Date doesn't exist";
        }
    }

    std::string CookieProcessor::ToString()
    {
        std::string cookieProcessorState;
        cookieProcessorState.append("Cookies - ").append("\n");
        for (auto& dateToCookies : m_DateToCookieInfoMap)
        {
            cookieProcessorState.append("[")
                .append("Date : ").append(boost::gregorian::to_iso_extended_string(dateToCookies.first)).append(", ");
            for (auto& info : dateToCookies.second)
            {
                cookieProcessorState.append("\n").append(info.ToString());
            }
            cookieProcessorState.append("]").append("\n");
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