// This file contains the 'main' function.

#include <iostream>
#include <string>

#include "boost/program_options.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/log/core.hpp"
#include "boost/log/trivial.hpp"
#include "boost/log/expressions.hpp"
#include "boost/log/utility/setup/file.hpp"
#include "boost/log/utility/setup/common_attributes.hpp"

#include "LogFileHandler.h"
#include "CookieProcessor.h"

void to_cout(const std::vector<std::string>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>{
        std::cout, "\n"});
}

void init_logging()
{
    boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");

    boost::log::add_file_log(
        boost::log::keywords::file_name = "cookie_processor_all.log",
        boost::log::keywords::format = "[%TimeStamp%] [%Severity%] [%ThreadID%] %Message%"
    );

    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);
    boost::log::add_common_attributes();
}

int main(int argc, const char* argv[])
{
    // initialize logging
    init_logging();

    // parse cmdline args
    std::string logFile, date;

    try
    {
        boost::program_options::options_description desc{ "Options" };
        desc.add_options()
            ("help,h", "Help screen")
            ("file,f", boost::program_options::value<boost::filesystem::path>(), "logfile")
            ("date,d", boost::program_options::value<std::string>(), "date");

        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);

        if (vm.count("help"))
        {
            std::cout << desc << std::endl;
            exit(0);
        }
        else
        {
            if (vm.count("file"))
            {
                logFile = vm["file"].as<boost::filesystem::path>().string();
            }
            if (vm.count("date"))
            {
                date = vm["date"].as<std::string>();
            }
        }
    }
    catch (const boost::program_options::error& ex)
    {
        BOOST_LOG_TRIVIAL(fatal) << "Error on parsing cmd args : " << ex.what();
    }

    if (logFile.empty() || date.empty())
    {
        BOOST_LOG_TRIVIAL(error) << "Error on parsing cmd args : logFile name or date params are empty";
        exit(0);
    }

    std::shared_ptr<cookie::ILogHandler> logHandler = std::make_shared<cookie::LogFileHandler>(logFile);

    cookie::CookieProcessor processor(logHandler);

    processor.process();
    auto result = processor.GetActiveCookie(date);
    
    for (auto& cookie : result)
    {
        std::cout << cookie << std::endl;
    }
}