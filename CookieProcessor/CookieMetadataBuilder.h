#pragma once
#include <string>

#include "CookieMetadata.h"

namespace cookie
{
	class CookieMetadataBuilder
	{
	public:
		CookieMetadataBuilder() = default;
		void SetIdentifier(const std::string& cookieId);
		void SetAccessTime(const std::string& time);
		CookieMetadata GetCookie();

	private:
		CookieMetadata m_cookieMetadata;
	};
}