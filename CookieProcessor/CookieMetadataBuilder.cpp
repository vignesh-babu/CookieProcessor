#include "CookieMetadataBuilder.h"

namespace cookie {
	
	void CookieMetadataBuilder::SetIdentifier(const std::string& cookieId)
	{
		m_cookieMetadata.SetId(cookieId);
	}
	
	void CookieMetadataBuilder::SetAccessTime(const std::string& time)
	{

	}

	CookieMetadata CookieMetadataBuilder::GetCookie()
	{
		return m_cookieMetadata;
	}
}