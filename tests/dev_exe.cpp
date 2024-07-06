
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
* -> [] Implement Date/Time/STime/Duration .operator+=()/.operator-=() methods
* -> [] Implement Date/Time/STime/Duration .operator+()/.operator-() methods
* -> [] Implement Date/Time/STime/Duration .increment()/.decrement() method
*	    that accepts Duration
* -> []* Implement .toSTime() method in Time class
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
* -> [] Investigate why illegals are thrown in sequence classes
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

	std::cout << "\n\n" << t1.millisecondsUntil(t2) << " ms" << std::endl;

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
		<< "\n\nConversion: " << st1.convertedTo(STime::TimeUnit::SECOND) << " sec"
		<< std::endl;


	//
	DurationInterval test{ 10, 1 };

	ArbMonth ggg{ 0, 0 };


	//
	Duration aggy{ Duration::Sign::POSITIVE, 0, 0, 2, 0, 0 };
	Duration ughh{ 104, 0, 3, 25 };

	std::cout << ughh.until(aggy);


	//
	Date bday{ 2001, 2, 23 };
	Date other{ 2005, 6, 17 };

	std::cout << "\n\nFrom " << bday << " -> " << other << " = " << bday.until(other);
	std::cout << "\nFrom " << t1 << " -> " << t2 << " = " << t1.until(t2) << std::endl;
	std::cout << "\nFrom* " << st1 << " -> " << st2 << " = " << st1.until(st2) << std::endl;


	//
	Time gorilla{};

	gorilla = std::move(st1);

	return NULL;
}
