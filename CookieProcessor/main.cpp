// This file contains the 'main' function.

#include <iostream>
#include <string>

#include "boost/program_options.hpp"
#include "boost/filesystem/path.hpp"

#include "LogFileHandler.h"
#include "CookieProcessor.h"

void to_cout(const std::vector<std::string>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>{
        std::cout, "\n"});
}

int main(int argc, const char* argv[])
{
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
        std::cerr << ex.what() << '\n';
    }

    if (logFile.empty() || date.empty())
    {
        std::cerr << "invalid args" << std::endl;
        exit(0);
    }
    cookie::ILogHandler* logHandler = new cookie::LogFileHandler(logFile);

    cookie::CookieProcessor processor(logHandler);

    processor.process();
    std::cout << processor.ToString() << std::endl;
    std::cout << processor.GetActiveCookie(date) << std::endl;
}