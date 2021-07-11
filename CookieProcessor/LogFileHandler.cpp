#include "LogFileHandler.h"

namespace cookie {

	LogFileHandler::LogFileHandler(const std::string& logFile) :
		m_logFileHandle(logFile.c_str())
	{
		if (!m_logFileHandle.good())
		{
			throw std::invalid_argument("Cannot open file : " + logFile);
		}
	}

	bool LogFileHandler::next(CookieMetadata& metadata)
	{
		std::string currLine;
		if (std::getline(m_logFileHandle, currLine))
		{

			return true;
		}
		else
		{
			return false;
		}
	}

	LogFileHandler::~LogFileHandler()
	{
		m_logFileHandle.close();
	}
}