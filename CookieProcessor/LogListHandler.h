#pragma once
#include <string>
#include <fstream>
#include <list>

#include "ILogHandler.h"

namespace cookie {
    namespace test {
        class LogListHandler : public ILogHandler
        {
        public:
            LogListHandler(std::list<std::string> cookieList);

            // Inherited via ILogHandler
            virtual bool next(CookieMetadata** metadata) override;

            ~LogListHandler();

        private:
            std::list<std::string> m_logLists;
            std::list<std::string>::iterator m_logListIter;
        };
    }
}