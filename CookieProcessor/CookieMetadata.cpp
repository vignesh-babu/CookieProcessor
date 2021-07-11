#include "CookieMetadata.h"

namespace cookie
{
	void CookieMetadata::SetId(std::string id)
	{
		m_identifier = id;
	}

	void CookieMetadata::SetAccessTime(boost::posix_time::ptime accessTime)
	{
		m_accessTime = accessTime;
	}

	std::string CookieMetadata::GetId()
	{
		return m_identifier;
	}

	boost::gregorian::date CookieMetadata::GetAccessDate()
	{
		return m_accessTime.date();
	}

	std::string CookieMetadata::ToString()
	{
		return std::string("[Cookie : Id - ").append(m_identifier)
			.append(", Access Time - ").append(boost::posix_time::to_iso_extended_string(m_accessTime))
			.append("]");
	}
}