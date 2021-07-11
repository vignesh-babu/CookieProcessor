#pragma once
#include <string>

#include "CookieMetadata.h"

namespace cookie
{
	class CookieMetadataBuilder
	{
	public:
		CookieMetadataBuilder();
		CookieMetadataBuilder SetIdentifier(const std::string& cookieId);
		CookieMetadataBuilder SetAccessTime(const std::string& time);
		CookieMetadata* GetCookie();

	private:
		CookieMetadata* m_cookieMetadata;
	};
}