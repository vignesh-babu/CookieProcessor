#include <iostream>
#include <fstream>

#include "nlohmann/json.hpp"

#include "TestJsonParser.h"

namespace cookie {
    namespace test {

        TestJsonParser::TestJsonParser(const std::string& jsonFile)
        {
            std::ifstream logFileHandle(jsonFile.c_str());

            if (!logFileHandle.good())
            {
                throw std::invalid_argument("Cannot open file : " + jsonFile);
            }

            nlohmann::json jsonContents;
            logFileHandle >> jsonContents;

            for (auto& testCase : jsonContents["TestCases"])
            {
                m_cookieTestDatas.push_back({ testCase["date"], testCase["result"],  testCase["logs"] });
            }
        }

        std::list<CookieTestData> TestJsonParser::GetTestData()
        {
            return m_cookieTestDatas;
        }
    }
}