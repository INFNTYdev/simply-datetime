
#include<iostream>
#include<cmath>

// Developer Includes:

// Core Functionality
#include"simplydt/common/range/int_range.hpp"
#include"simplydt/common/interval/interval.hpp"
#include"simplydt/common/sequence/linked_sequence.hpp"

// VDate Core
#include"simplydt/datetime/date/date_interval.hpp"
#include"simplydt/datetime/date/unit/dt_year.hpp"
#include"simplydt/datetime/date/unit/dt_month.hpp"
#include"simplydt/datetime/date/unit/dt_day.hpp"

// VTime Core
#include"simplydt/datetime/time/time_interval.hpp"
#include"simplydt/datetime/time/unit/dt_hour.hpp"
#include"simplydt/datetime/time/unit/dt_minute.hpp"
#include"simplydt/datetime/time/unit/dt_second.hpp"
#include"simplydt/datetime/time/unit/dt_millisecond.hpp"

// VDuration Core
#include"simplydt/duration/duration_interval.hpp"
#include"simplydt/duration/unit/dur_unit_def.hpp"

// VDatetime Core
#include"simplydt/datetime/sequence/dt_sequence.hpp"

// VDuration
#include"simplydt/duration/comp/dt_duration.hpp"

// VDate
#include"simplydt/datetime/date/comp/dt_date.hpp"

// VTime
// N/A

// VDatetime
// N/A



//#include"simplydt/datetime/time/comp/dt_time.hpp"
//#include"simplydt/datetime/time/comp/dt_stime.hpp"

//#include"simplydt/datetime/comp/sdt_datetime.hpp"
//#include"simplydt/datetime/comp/sdt_sdatetime.hpp"



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
* -> [X] Plan and implement VDuration class interface
* -> [X] Implement .millisecondsUntil() method in Time class
* -> [X] Implement .until() methods in VDate, Time, and STime classes
* -> [X] Implement Time constructor/=operators that accept STime
* -> [X] Implement VDate/Time/STime/VDuration .displace() method
* -> [X] Implement VDate/Time/STime/VDuration .operator+=()/.operator-=() methods
* -> [X] Implement VDate/Time/STime/VDuration .operator+()/.operator-() methods
* -> [X] Implement .toSTime() method in Time class
* -> [X] Determine highest possible number Range class can handle with an int type
* -> [X] Implement VDate .toTimePoint() method
* -> [] Plan and implement Datetime/SDatetime class interfaces
* -> [] Plan and implement library main header
* -> [] Test main library header
* 
* 
* (Some future point...)
* 
* -> [] Plan and implement DatetimeStub class
* -> [] Implement VDate/Time/STime class .toStub() method
* -> [] Implement VDate/Time/STime constructor that accepts DatetimeStub
* -> [] *Implement VDate/Time/STime .operator=() for std::chrono <- IMPORTANT
* -> [] *Provide all datetime sequence classes with pointers to intervals <- IMPORTANT
* -> [] Implement VDate/Time/STime/VDuration string parsing capability
* -> [] Implement iterator for Range class (for use with for-loops)
* -> [] Find new means to displace Day class
* -> [] Investigate why illegals are thrown in sequence classes
* -> [] Take a good look at this libraries structure and start improving
* 
\* /// \\\ /// \\\ ///  | END |  \\\ /// \\\ /// \\\ */



//void dateCompare(const VDate& date1, const VDate& date2) noexcept
//{
//	std::cout
//		<< "\nFrom " << date1.dateStr(VDate::Format::STANDARD)
//		<< " -> " << date2.dateStr(VDate::Format::STANDARD)
//		<< " = " << date1.until(date2) << std::endl;
//}
//
//void timeCompare(const Time& time1, const Time& time2) noexcept
//{
//	std::cout
//		<< "\nFrom " << time1.timeStr(Time::Format::STANDARD, Time::Layout::H_M_S_P)
//		<< " -> " << time2.timeStr(Time::Format::STANDARD, Time::Layout::H_M_S_P)
//		<< " = " << time1.until(time2) << std::endl;
//}
//
//void durationDisplace(VDuration& dur1, const VDuration& dur2) noexcept
//{
//	std::cout << "\n( " << dur1 << " ) + ( " << dur2 << " ) = ";
//
//	dur1.displace(dur2);
//
//	std::cout << dur1 << std::endl;
//}
//
//void datetimeOut(const Datetime& datetime) noexcept
//{
//	std::cout
//		<< '\n'
//		<< datetime.datetimeStr(
//			VDate::Format::STANDARD,
//			VDate::Layout::M_D_YYYY,
//			Time::Format::STANDARD,
//			Time::Layout::H_M_S_P
//		)
//		<< std::endl;
//}
//
//void dateOut(const VDate& date) noexcept
//{
//	std::cout
//		<< '\n'
//		<< date.dateStr(
//			VDate::Format::STANDARD,
//			VDate::Layout::M_D_YYYY
//		)
//		<< std::endl;
//}
//
//void timeOut(const Time& time) noexcept
//{
//	std::cout
//		<< '\n'
//		<< time.timeStr(
//			Time::Format::STANDARD,
//			Time::Layout::H_M_S_P
//		)
//		<< std::endl;
//}


int to_jdn(int day, int month, int year) {
	if (month < 3) {
		--year;
		month += 12;
	}

	return day + std::floor((153 * month + 2) / 5) + 365 * year + std::floor(year / 4) - std::floor(year / 100) + std::floor(year / 400) - 32045;
}

void from_jdn(int jdn, int& day, int& month, int& year) {
	jdn += 32044;
	int n = 4 * jdn + 3 + 146097 * 3 / 4;
	int k = n % 146097 / 4;
	int m = 4000 * (k + 1) / 1461001;
	int jd = 5 * (k - 1461 * m / 4 + 31) / 153;
	day = (jd % 153 * 5 + 2) / 5;
	month = jd / 153 % 12 + 1;
	year = n / 146097 * 100 + m - 4800 + (month <= 2 ? 1 : 0);
}

int days_between(int day1, int month1, int year1, int day2, int month2, int year2) {
	return std::abs(to_jdn(day1, month1, year1) - to_jdn(day2, month2, year2));
}

void add_days(int& day, int& month, int& year, int days) {
	int jdn = to_jdn(day, month, year) + days;
	from_jdn(jdn, day, month, year);
}


int main(size_t argc, char* argv[])
{
	//VDate epochDate{ 1969, 12, 31 };
	//VDate epochNeig{ 1970, 1, 1 };
	//VDate todayDate{ std::chrono::system_clock::now() };

	//std::cout << "\nEpoch:";
	//dateOut(epochDate);

	//std::cout << "\nEpoch neighbor:";
	//dateOut(epochNeig);

	//std::cout << "\nToday:";
	//dateOut(todayDate);


	//// 19,916 days ago was epoch
	//// Updated (7/11/2024)


	//// This stuff is correct
	//std::cout
	//	<< "\n\nEpoch Date  --->  Today Date\n\n"
	//	<< std::setw(25) << "daysUntil(today): " << epochDate.daysUntil(todayDate) << '\n'
	//	<< std::setw(25) << "until(today): " << epochDate.until(todayDate) << '\n'
	//	<< std::setw(25) << "until(neighbor): " << epochDate.until(epochNeig) << '\n'
	//	<< std::endl;

	//std::cout << "\nJDN Number test:" << std::endl;
	//std::cout
	//	<< days_between(
	//		epochDate.day(),
	//		epochDate.month(),
	//		epochDate.year(),
	//		todayDate.day(),
	//		todayDate.month(),
	//		todayDate.year()
	//	)
	//	<< " days until" << std::endl;


	//// This stuff is incorrect
	//std::cout << '\n'
	//	<< std::setw(25) << "epoch + until today: ";
	//VDuration untilToday = epochDate.until(todayDate);
	//VDate expectToday = (epochDate + untilToday);
	//std::cout << expectToday << " (missing ";
	//// Extra day becase time not accounted
	//size_t daysMissing = expectToday.daysUntil(todayDate);
	//std::cout << daysMissing << " days)" << std::endl;

	//std::cout << std::setw(25) << "epoch + until neighb.: ";
	//VDuration untilNeig = epochDate.until(epochNeig);
	//VDate expectNeig = (epochDate + untilNeig);
	//std::cout << expectNeig << " (missing ";
	//// Extra day becase time not accounted
	//daysMissing = expectNeig.daysUntil(epochNeig);
	//std::cout << daysMissing << " days)" << std::endl;

	//std::cout << "\nSearching for day loss..." << std::endl;

	//while (daysMissing == 0) {

	//	epochNeig.getDay().increment();

	//	untilNeig = epochDate.until(epochNeig);

	//	if (untilNeig.days() == 59)
	//		std::cout << "\nNext loop" << std::endl;

	//	expectNeig = (epochDate + untilNeig);
	//	daysMissing = expectNeig.daysUntil(epochNeig);

	//}

	//std::cout << "\n\nDay loss started with:";
	//dateOut(expectNeig);
	//std::cout << "("
	//	<< epochDate.daysUntil(expectNeig)
	//	<< " days from epoch)"
	//	<< "\n(" << expectNeig.daysUntil(epochNeig) << " days missing)"
	//	<< std::endl;

	//// Seems like wrong method calls are happening
	// Day maximum was not updated during displace

	// ANALYSIS
	// -> (Must be careful with use of methods!)
	// -> VDate intervals need specialized control methods
	// 


	VDate demo_1{ 2024, 6 };

	VDate copyDate{ demo_1 };

	uint8_t dayTick{ 100 };

	while (dayTick != 0Ui8) {

		if (copyDate.day() == 1Ui16)
			std::cout << "\n\n" << copyDate.monthTitle() << " ->";

		std::cout << "\nDate: " << copyDate << " - " << copyDate.dayOfWeek();

		copyDate.displace(VDuration{ 1 });// Displace 1 day
		--dayTick;

	}

	std::cout << "\nComplete: " << copyDate << std::endl;

	return NULL;
}
