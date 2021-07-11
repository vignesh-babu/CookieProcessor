#include<string>
#include <boost/date_time.hpp>

namespace cookie
{
	class CookieMetadata
	{
	public:
		void SetId(std::string id);
		void SetAccessTime(boost::posix_time::ptime accessTime);
		std::string GetId();
		std::string ToString();

	private:
		std::string m_identifier;
		boost::posix_time::ptime m_accessTime;
	};
}