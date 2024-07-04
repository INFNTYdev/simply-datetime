
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
* -> Implement .linkDate() method in Time/STime class
* -> Just fix STime classes .secondsUntil() method
* -> Start DurationInterval class (create preset type names)
* -> Plan and implement Duration class interface
* -> Implement DatetimeStub class
* -> Implement .until() methods in Date, Time, and STime classes
* -> Implement .toStub() methods in Date, Time, and STime classes
* -> Implement Time constructor/operators that accepts STime
* -> Implement Date/Time/STime constructor that accepts DatetimeStub
* -> Implement .toSTime() method in Time class
* -> Plan and implement Datetime/SDatetime class interfaces
* -> Plan and implement library main header
* 
\* /// \\\ /// \\\ ///  | END |  \\\ /// \\\ /// \\\ */



int main(size_t argc, char* argv[])
{
	//
	Date date_1{ 2024, 2, 9 };
	Date date_2{ 2024, 10, 9 };

	date_1 < date_2;

	size_t teee = date_2.daysUntil(date_1);

	std::cout
		<< std::boolalpha
		<< "\nD1: " << date_1
		<< "\nD2: " << date_2
		<< "\n\nLogic Tests:"
		<< "\nD1 > D2: " << (date_1 > date_2)
		<< "\nD1 < D2: " << (date_1 < date_2)
		<< "\nD1 == D2: " << (date_1 == date_2)
		<< std::endl;


	//
	Time time_2{ 5, 35, 10, 0 };
	Time time_1{ 4, 30, 00, 0 };
	STime stime_1{ std::chrono::system_clock::now() };

	std::cout << "\n\nOUT: " << time_1.secondsUntil(time_2);

	return NULL;
}
