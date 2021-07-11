#pragma once
#include <unordered_map>
#include "boost/date_time/gregorian/gregorian.hpp" 

#include "LogFileHandler.h"

namespace cookie
{
	struct CookieInfo
	{
		CookieMetadata m_metadata;
		int occurences;
	};

	class CookieProcessor
	{
	public:
		CookieProcessor(std::string logFile);
		std::string GetActiveCookie(std::string date);

	private:
		LogFileHandler m_logFileHandler;
		std::unordered_map<boost::gregorian::date, std::vector<CookieInfo>> m_DateToCookieInfoMap;

	};
}