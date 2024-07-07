
#include<iostream>

// Developer Includes:
#include"simplydt/duration/duration_interval.hpp"
#include"simplydt/duration/unit/dur_unit_def.hpp"
#include"simplydt/datetime/date/unit/dt_year.hpp"
#include"simplydt/datetime/date/unit/dt_month.hpp"
#include"simplydt/datetime/date/unit/dt_day.hpp"

#include"simplydt/datetime/time/unit/dt_hour.hpp"
#include"simplydt/datetime/time/unit/dt_minute.hpp"
#include"simplydt/datetime/time/unit/dt_second.hpp"
#include"simplydt/datetime/time/unit/dt_millisecond.hpp"

#include"simplydt/common/sequence/linked_sequence.hpp"
#include"simplydt/datetime/sequence/dt_sequence.hpp"

#include"simplydt/datetime/date/comp/dt_date.hpp"
#include"simplydt/datetime/time/comp/dt_time.hpp"
#include"simplydt/datetime/time/comp/dt_stime.hpp"

#include"simplydt/duration/comp/dt_duration.hpp"



/* /// \\\ /// \\\ /// | TO-DO | \\\ /// \\\ /// \\\ *\
* 
* 6/31/2024
* 
* -> Make sure all boundless logic is accounted for in Range class
* -> Safety checks when adding numbers in Range class to ensure no overflows?
* 
* 
* 7/4/2024
* 
* -> [X] Implement .linkDate() method in Time/STime class
* -> [X] Just fix STime classes .secondsUntil() method
* -> [X] Start DurationInterval class (create preset type names)
* -> [X] Plan and implement Duration class interface
* -> [X] Implement .millisecondsUntil() method in Time class
* -> [X] Implement .until() methods in Date, Time, and STime classes
* -> [X] Implement Time constructor/=operators that accept STime
* -> [] Implement Date/Time/STime/Duration .displace() method
* -> [] Implement Date/Time/STime/Duration .operator+=()/.operator-=() methods
* -> [] Implement Date/Time/STime/Duration .operator+()/.operator-() methods
* -> [X] Implement .toSTime() method in Time class
* -> [] Determine highest possible number Range class can handle with an int type
* -> [] Plan and implement Datetime/SDatetime class interfaces
* -> [] Plan and implement library main header
* -> [] Test main library header
* 
* 
* (Some future point...)
* 
* -> [] Plan and implement DatetimeStub class
* -> [] Implement Date/Time/STime class .toStub() method
* -> [] Implement Date/Time/STime constructor that accepts DatetimeStub
* -> [] Provide all datetime sequence classes with pointers to intervals
* -> [] Find new means to displace Day class
* -> [] Investigate why illegals are thrown in sequence classes
* 
\* /// \\\ /// \\\ ///  | END |  \\\ /// \\\ /// \\\ */



void dateCompare(const Date& date1, const Date& date2) noexcept
{
	std::cout
		<< "\nFrom " << date1.dateStr(Date::Format::STANDARD)
		<< " -> " << date2.dateStr(Date::Format::STANDARD)
		<< " = " << date1.until(date2) << std::endl;
}

void timeCompare(const Time& time1, const Time& time2) noexcept
{
	std::cout
		<< "\nFrom " << time1.timeStr(Time::Format::STANDARD, Time::Layout::H_M_S_P)
		<< " -> " << time2.timeStr(Time::Format::STANDARD, Time::Layout::H_M_S_P)
		<< " = " << time1.until(time2) << std::endl;
}

void durationDisplace(Duration& dur1, const Duration& dur2) noexcept
{
	std::cout << "\n( " << dur1 << " ) + ( " << dur2 << " ) = ";

	dur1.displace(dur2);

	std::cout << dur1 << std::endl;
}


int main(size_t argc, char* argv[])
{
	//
	Date pastDate{ 2024, 7, 6 };
	Date futureDate{ 2025, 2, 23 };

	Time nowTime{ std::chrono::system_clock::now() };
	Time futureTime{ 0, 45 };

	Duration shortDuration{ 0, 0, 2 };
	Duration longDuration{ Duration::Sign::NEGATIVE, 0, 0, 3 };

	dateCompare(pastDate, futureDate);
	timeCompare(nowTime, futureTime);

	pastDate.displace(pastDate.until(futureDate));

	dateCompare(pastDate, futureDate);

	nowTime.displace(nowTime.until(futureTime));

	timeCompare(nowTime, futureTime);
	
	durationDisplace(longDuration, shortDuration);

	return NULL;
}
