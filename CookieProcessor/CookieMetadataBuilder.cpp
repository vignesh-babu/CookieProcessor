#include "CookieMetadataBuilder.h"
#include "CookieParseHelper.h"

namespace cookie {
    CookieMetadataBuilder::CookieMetadataBuilder()
    {
        m_cookieMetadata = new CookieMetadata();
    }

    CookieMetadataBuilder CookieMetadataBuilder::SetIdentifier(const std::string& cookieId)
    {
        m_cookieMetadata->SetId(cookieId);
        return *this;
    }

    CookieMetadataBuilder CookieMetadataBuilder::SetAccessTime(const std::string& time)
    {
        m_cookieMetadata->SetAccessTime(parse_helper::GetAccessTime(time));
        return *this;
    }

    CookieMetadata* CookieMetadataBuilder::GetCookie()
    {
        CookieMetadata* result = this->m_cookieMetadata;
        this->m_cookieMetadata = nullptr;
        return result;
    }
    CookieMetadataBuilder::~CookieMetadataBuilder()
    {
        m_cookieMetadata = nullptr;
    }
}