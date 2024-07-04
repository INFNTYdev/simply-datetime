
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



// Range Class:
// Go back through all code and make sure boundless logic is accounted for
// Need safety checks when adding numbers to make sure they don't hit the ceiling



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
