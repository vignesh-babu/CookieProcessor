#include "CookieMetadataBuilder.h"
#include "CookieParseHelper.hpp"

namespace cookie {
	CookieMetadataBuilder::CookieMetadataBuilder()
	{
		m_cookieMetadata = new CookieMetadata();
	}

	CookieMetadataBuilder CookieMetadataBuilder::SetIdentifier(const std::string& cookieId)
	{
		m_cookieMetadata->SetId(cookieId);
	}
	
	CookieMetadataBuilder CookieMetadataBuilder::SetAccessTime(const std::string& time)
	{
		m_cookieMetadata->SetAccessTime(parse_helper::GetAccessTime(time));
	}

	CookieMetadata* CookieMetadataBuilder::GetCookie()
	{
		return m_cookieMetadata;
	}
}