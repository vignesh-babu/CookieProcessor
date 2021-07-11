#include <string>
#include <boost/date_time.hpp>

namespace cookie {
namespace parse_helper {
	
	boost::posix_time::ptime GetAccessTime(const std::string& accessTimeStr)
	{
		// remove +/- 00:00 as time is represented in UTC
		auto accessTimeStrFormated = accessTimeStr.substr(0, accessTimeStr.size() - 6);

		boost::posix_time::ptime cookieAccessTime = boost::posix_time::from_iso_extended_string(accessTimeStrFormated);
		// TODO: log it
		//std::cout << "Time : " << boost::posix_time::to_iso_extended_string(cookieAccessTime) << std::endl;
		return cookieAccessTime;
	}
}
}