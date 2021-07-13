#include "boost/test/included/unit_test.hpp"
#include "boost/test/parameterized_test.hpp"
#include "boost/log/core.hpp"
#include "boost/log/trivial.hpp"
#include "boost/log/expressions.hpp"
#include "boost/log/utility/setup/file.hpp"
#include "boost/log/utility/setup/common_attributes.hpp"

#include "CookieProcessor.h"
#include "LogListHandler.h"
#include "TestJsonParser.h"

using namespace boost::unit_test;

namespace cookie {
    namespace test {
        std::ostream& boost_test_print_type(std::ostream& os, const std::list<cookie::test::CookieTestData>::iterator& td)
        {
            os << td->ToString();
            return os;
        }
    }
}

void init_test_logging()
{
    boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);
    boost::log::add_common_attributes();
}

void CookieProcessorTest(cookie::test::CookieTestData cookieTestData)
{
    std::shared_ptr<cookie::ILogHandler> logHandler = std::make_shared<cookie::test::LogListHandler>(cookieTestData.logs);

    cookie::CookieProcessor processor(logHandler);

    processor.process();
    auto actualResult = processor.GetActiveCookie(cookieTestData.date);

    for (auto& cookie : cookieTestData.result)
    {
        BOOST_TEST((std::find(actualResult.begin(), actualResult.end(), cookie) != actualResult.end()));
    }
}

test_suite* init_unit_test_suite(int argc, char* argv[])
{
    init_test_logging();

    if (framework::master_test_suite().argc != 2)
    {
        BOOST_LOG_TRIVIAL(error) << "error : usage - {test.exe} -- json file" << std::endl;
        return 0;
    }

    boost::unit_test::results_reporter::set_stream(std::cout);
    std::string jsonFileName = argv[1];
    std::unique_ptr<cookie::test::TestJsonParser> parser(std::make_unique<cookie::test::TestJsonParser>(jsonFileName));
    auto testDatas = parser->GetTestData();
    framework::master_test_suite().
        add(BOOST_PARAM_TEST_CASE(&CookieProcessorTest, testDatas.begin(), testDatas.end()));
    return 0;
}