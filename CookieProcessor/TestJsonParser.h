#pragma once
#include <string>
#include <list>

#include "boost/property_tree/ptree.hpp"

namespace cookie {
    namespace test {

        struct CookieTestData
        {
            std::string date;
            std::list<std::string> result;
            std::list<std::string> logs;

            std::string ToString() const
            {
                std::string data;
                data.append("date : ").append(date);
                data.append(" | result : ");
                for (auto r : result)
                {
                    data.append(r + ",");
                }
                data.append(" | logs : ");
                for (auto r : logs)
                {
                    data.append(r + ",");
                }
                return data;
            }
        };

        class TestJsonParser
        {
        public:
            TestJsonParser(const std::string& jsonFile);
            std::list<CookieTestData> GetTestData();
            
        private:
            std::list<CookieTestData> m_cookieTestDatas;
        };
    }
}