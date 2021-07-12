#include "boost/test/included/unit_test.hpp"
#include "boost/test/parameterized_test.hpp"

#include "CookieProcessor.h"
#include "LogListHandler.h"
#include "TestJsonParser.h"

using namespace boost::unit_test;

namespace cookie {
    namespace test {
        std::ostream& boost_test_print_type(std::ostream& os, const cookie::test::CookieTestData& td)
        {
            os << td.ToString();
            return os;
        }
    }
}

void CookieProcessorTest(cookie::test::CookieTestData cookieTestData)
{
    std::shared_ptr<cookie::ILogHandler> logHandler = std::make_shared<cookie::test::LogListHandler>(cookieTestData.logs);

    cookie::CookieProcessor processor(logHandler);

    processor.process();
    auto actualResult = processor.GetActiveCookie(cookieTestData.date);

    for (auto& cookie : cookieTestData.result)
    {
        auto result = std::find(actualResult.begin(), actualResult.end(), cookie) != actualResult.end();
        BOOST_TEST(result);
    }
}

test_suite* init_unit_test_suite(int argc, char* argv[])
{
    std::string jsonFileName = argv[1];
    std::unique_ptr<cookie::test::TestJsonParser> parser(std::make_unique<cookie::test::TestJsonParser>(jsonFileName));
    auto testDatas = parser->GetTestData();
    framework::master_test_suite().
        add(BOOST_PARAM_TEST_CASE(&CookieProcessorTest, testDatas.begin(), testDatas.end()));
    
    return 0;
}