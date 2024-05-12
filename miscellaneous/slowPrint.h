#include <thread>
#include <string>
#include <iostream>

struct slowly_printing_string
{
	std::string data;
	long int delay;
};

std::ostream& operator<<(std::ostream& out, const slowly_printing_string& s)
{
	for (const auto& c : s.data)
	{
		out << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(s.delay));
	}
	return out;
}