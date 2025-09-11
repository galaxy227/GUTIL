#ifndef GUTIL_TIME_H
#define GUTIL_TIME_H

#include <string>
#include <chrono>

namespace GUTIL {

/*
 * Constructing a Time object automatically captures the current time.
*/
class Time {
public:
	Time();
	~Time();
	Time(const Time& other);
	Time& operator=(const Time& other);
	Time(Time&& other) noexcept;
	Time& operator=(Time&& other) noexcept;

	static double get_duration(const Time& start_time, const Time& end_time);

	std::string get_timestamp();
private:
	std::chrono::steady_clock::time_point time_point;
	std::string timestamp;
};
} // GUTIL

#endif
