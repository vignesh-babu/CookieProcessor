#pragma once

#include "CookieMetadata.h"

namespace cookie
{
	class ILogHandler
	{
	public:
		virtual bool next(CookieMetadata* metadata) = 0;
	};
}