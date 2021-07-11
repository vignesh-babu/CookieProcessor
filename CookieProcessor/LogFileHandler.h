#pragma once
#include <string>
#include <fstream>

#include "ILogHandler.h"

namespace cookie {

	class LogFileHandler : public ILogHandler
	{
	public:
		LogFileHandler(const std::string& logFile);
		
		// Inherited via ILogHandler
		virtual bool next(CookieMetadata** metadata) override;
		
		~LogFileHandler();
	
	private:
		std::ifstream m_logFileHandle;
	};
}