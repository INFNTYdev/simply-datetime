
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

#include"simplydt/datetime/comp/sdt_datetime.hpp"
#include"simplydt/datetime/comp/sdt_sdatetime.hpp"



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
* -> [X] Implement Date/Time/STime/Duration .displace() method
* -> [X] Implement Date/Time/STime/Duration .operator+=()/.operator-=() methods
* -> [X] Implement Date/Time/STime/Duration .operator+()/.operator-() methods
* -> [X] Implement .toSTime() method in Time class
* -> [X] Determine highest possible number Range class can handle with an int type
* -> [X] Implement Date .toChrono() method
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
* -> [] *Implement Date/Time/STime .operator=() for std::chrono <- IMPORTANT
* -> [] *Provide all datetime sequence classes with pointers to intervals <- IMPORTANT
* -> [] Implement Date/Time/STime/Duration string parsing capability
* -> [] Implement iterator for Range class (for use with for-loops)
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

void datetimeOut(const Datetime& datetime) noexcept
{
	std::cout
		<< '\n'
		<< datetime.datetimeStr(
			Date::Format::STANDARD,
			Date::Layout::M_D_YYYY,
			Time::Format::STANDARD,
			Time::Layout::H_M_S_P
		)
		<< std::endl;
}

void dateOut(const Date& date) noexcept
{
	std::cout
		<< '\n'
		<< date.dateStr(
			Date::Format::STANDARD,
			Date::Layout::M_D_YYYY
		)
		<< std::endl;
}

void timeOut(const Time& time) noexcept
{
	std::cout
		<< '\n'
		<< time.timeStr(
			Time::Format::STANDARD,
			Time::Layout::H_M_S_P
		)
		<< std::endl;
}


int main(size_t argc, char* argv[])
{
	//
	Datetime date_1{ Datetime{ Date(2024, 7, 10), Time(1, 6) } };
	Datetime date_2{ Datetime{ Date(2023, 7, 10), Time(1, 5) } };
	Duration fiveMin{ Duration::Sign::POSITIVE, 0, 0, 5 };

	//datetimeOut(date_1);

	//datetimeOut(date_2);

	// Information loss ocurring here
	// I think Time Chrono constructor is wrong
	//datetimeOut(Datetime{ date_1.toChrono() });

	

	// ISOLATE THE PROBLEM:

	Time dummyT{ std::chrono::system_clock::now() };
	Datetime dummyDT{ std::chrono::system_clock::now() };

	// Constructor works with non-epoch time point
	//std::cout << "Constructor works with non-epoch time point" << std::endl;
	//timeOut(dummyT);
	//datetimeOut(dummyDT);

	//Time problemT{ Time::Chrono{} };
	Datetime problemDT{ Datetime::Chrono{} };

	// Constructor doesn't work with epoch time point
	//std::cout << "\n\nConstructor doesn't work with epoch time point" << std::endl;
	//timeOut(problemT);
	datetimeOut(problemDT);

	std::cout << '\n'
		<< problemDT.until(dummyDT)
		<< std::endl;

	datetimeOut(dummyDT);
	datetimeOut((problemDT + problemDT.until(dummyDT)));

	// ISOLATE THE PROBLEM



	//std::cout << '\n' << NULL << std::endl;

	return NULL;
}
