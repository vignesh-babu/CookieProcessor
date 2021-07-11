#pragma once
#include <unordered_map>
#include "boost/date_time/gregorian/gregorian.hpp" 

#include "LogFileHandler.h"

namespace cookie
{
	struct CookieInfo
	{
		CookieMetadata m_metadata;
		int m_occurences;

		std::string ToString();
	};

	class CookieProcessor
	{
	public:
		CookieProcessor(ILogHandler* logHandler);
		void process();
		std::string GetActiveCookie(const std::string& date);

		std::string ToString();

	private:
		std::unique_ptr<ILogHandler> m_logHandler;
		std::unordered_map<boost::gregorian::date, std::vector<CookieInfo>> m_DateToCookieInfoMap;
	};
}