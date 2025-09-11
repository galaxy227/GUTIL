#include "GUTIL_time.h"

#include <iomanip>
#include <sstream>

GUTIL::Time::Time() {
	// Time point
	time_point = std::chrono::steady_clock::now();
	// Timestamp (vibe coding slop)
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm tm = {};
	bool is_valid = true;
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
		localtime_s(&tm, &t);
	#elif defined(__linux__)
		localtime_r(&t, &tm);
	#else
		is_valid = false;
	#endif
	if (is_valid) {
		std::ostringstream oss;
		oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
		timestamp = oss.str();
	}
	else timestamp = "NULL";
}
GUTIL::Time::~Time() {}
GUTIL::Time::Time(const Time& other) : time_point(other.time_point), timestamp(other.timestamp) {}
GUTIL::Time& GUTIL::Time::operator=(const Time& other) {
	if (this != &other) {
		time_point = other.time_point;
		timestamp = other.timestamp;
	}
	return *this;
}

double GUTIL::Time::get_duration(const Time& start_time, const Time& end_time) {
	std::chrono::duration<double> difference = end_time.time_point - start_time.time_point;
	return difference.count();
}

std::string GUTIL::Time::get_timestamp() {
	return timestamp;
}
