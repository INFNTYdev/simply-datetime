
#include<iostream>

// Developer Includes:
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
* -> [] Start DurationInterval class (create preset type names)
* -> [] Plan and implement Duration class interface
* -> [] Implement DatetimeStub class
* -> [] Implement .until() methods in Date, Time, and STime classes
* -> [] Implement .toStub() methods in Date, Time, and STime classes
* -> [] Implement Time constructor/operators that accepts STime
* -> [] Implement Date/Time/STime constructor that accepts DatetimeStub
* -> [] Implement .toSTime() method in Time class
* -> [] Plan and implement Datetime/SDatetime class interfaces
* -> [] Plan and implement library main header
* 
\* /// \\\ /// \\\ ///  | END |  \\\ /// \\\ /// \\\ */



int main(size_t argc, char* argv[])
{
	//
	uint16_t hour{ 17 };
	uint16_t minute{ 43 };
	uint16_t second{ 0 };

	Time t1{ hour };
	Time t2{ hour, minute, second };

	STime st1{ hour };
	STime st2{ hour, minute, second };

	std::cout
		<< "\nTime 1: " << t1.timeStr(Time::Format::STANDARD)
		<< "\nTime 2: " << t2.timeStr(Time::Format::STANDARD)
		<< "\n\nSeconds until T1 -> T2: "
		<< t1.secondsUntil(t2) << " seconds"
		<< std::endl;

	std::cout
		<< "\nSTime 1: " << st1.timeStr(STime::Format::STANDARD)
		<< "\nSTime 2: " << st2.timeStr(STime::Format::STANDARD)
		<< "\n\nSeconds until ST1 -> ST2: "
		<< st1.secondsUntil(st2) << " seconds"
		<< std::endl;

	return NULL;
}
