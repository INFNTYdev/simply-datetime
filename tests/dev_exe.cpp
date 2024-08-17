
#include<iostream>
#include<cmath>


// Library Includes:

// Core Functionality
#include"simplydt/common/range/int_range.hpp"
#include"simplydt/common/interval/interval.hpp"
#include"simplydt/common/sequence/linked_sequence.hpp"

// Virtual Date Core
#include"simplydt/datetime/date/date_interval.hpp"
#include"simplydt/datetime/date/unit/dt_year.hpp"
#include"simplydt/datetime/date/unit/dt_month.hpp"
#include"simplydt/datetime/date/unit/dt_day.hpp"

// Virtual Time Core
#include"simplydt/datetime/time/time_interval.hpp"
#include"simplydt/datetime/time/unit/dt_hour.hpp"
#include"simplydt/datetime/time/unit/dt_minute.hpp"
#include"simplydt/datetime/time/unit/dt_second.hpp"
#include"simplydt/datetime/time/unit/dt_millisecond.hpp"

// Virtual Duration Core
#include"simplydt/duration/duration_interval.hpp"
#include"simplydt/duration/unit/dur_unit_def.hpp"

// Virtual Datetime Core
#include"simplydt/datetime/sequence/dt_sequence.hpp"

// Virtual Duration
#include"simplydt/duration/comp/virtual/dt_vduration.hpp"

// Virtual Date
#include"simplydt/datetime/date/comp/virtual/dt_vdate.hpp"

// Virtual Time
#include"simplydt/datetime/time/comp/virtual/dt_vtime_ex.hpp"
#include"simplydt/datetime/time/comp/virtual/dt_vtime.hpp"

// Virtual Datetime
#include"simplydt/datetime/comp/virtual/vdatetime_ex.hpp"
//#include"simplydt/datetime/comp/virtual/vdatetime.hpp"




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
* -> [X] Implement .linkDate() method in VTimeEx/VTime class
* -> [X] Just fix VTime classes .secondsUntil() method
* -> [X] Start DurationInterval class (create preset type names)
* -> [X] Plan and implement VDuration class interface
* -> [X] Implement .msUntil() method in VTimeEx class
* -> [X] Implement .until() methods in VDate, VTimeEx, and VTime classes
* -> [X] Implement VTimeEx constructor/=operators that accept VTime
* -> [X] Implement VDate/VTimeEx/VTime/VDuration .displace() method
* -> [X] Implement VDate/VTimeEx/VTime/VDuration .operator+=()/.operator-=() methods
* -> [X] Implement VDate/VTimeEx/VTime/VDuration .operator+()/.operator-() methods
* -> [X] Implement .toSTime() method in VTimeEx class
* -> [X] Determine highest possible number Range class can handle with an int type
* -> [X] Implement VDate .toTimePoint() method
* -> [X] Determine max number of days between two VDate's for VDatetimeEx/VDatetime class
* -> [X] VDate large displace divergence test
* -> [] Plan and implement VDatetimeEx/VDatetime class interfaces
* -> [] Plan and implement library main header
* -> [] Test main library header
* 
* 
* (Some future point...)
* 
* -> [] Plan and implement DatetimeStub class
* -> [] Implement VDate/VTimeEx/VTime class .toStub() method
* -> [] Implement VDate/VTimeEx/VTime constructor that accepts DatetimeStub
* -> [X] *Implement VDate/VTimeEx/VTime .operator=() for std::chrono <- IMPORTANT
* -> [X] *Provide all datetime sequence classes with pointers to intervals <- IMPORTANT
* -> [] *Update VTimeEx class JDN system to account for milliseconds <- IMPORTANT
* -> [] Implement VDate/VTimeEx/VTime/VDuration string parsing capability
* -> [] Implement iterator for Range class (for use with for-loops)
* -> [X] Find new means to displace Day class
* -> [X] Investigate why illegals are thrown in sequence classes
* -> [] Take a good look at this libraries structure and start improving
* 
\* /// \\\ /// \\\ ///  | END |  \\\ /// \\\ /// \\\ */



void ProjectInfoOut() noexcept
{
	std::cout << '\n'
		<< "\n\tINFINITY Systems, LLC. 2024\n"
		<< "\n\t[ Simply Datetime Library ]"
		<< "\n\tDeveloper executable"
		<< "\n\tRelease: 4 Version: 0"
		<< "\n\t-> (dev_exe.exe)\n"
		<< "\n\tStandard: C++ 20+"
		<< "\n\n" << std::endl;
}

//void dateCompare(const VDate& date1, const VDate& date2) noexcept
//{
//	std::cout
//		<< "\nFrom " << date1.dateStr(VDate::Format::STANDARD)
//		<< " -> " << date2.dateStr(VDate::Format::STANDARD)
//		<< " = " << date1.until(date2) << std::endl;
//}
//
//void timeCompare(const VTimeEx& time1, const VTimeEx& time2) noexcept
//{
//	std::cout
//		<< "\nFrom " << time1.timeStr(VTimeEx::Format::STANDARD, VTimeEx::Layout::H_M_S_P)
//		<< " -> " << time2.timeStr(VTimeEx::Format::STANDARD, VTimeEx::Layout::H_M_S_P)
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
//void datetimeOut(const VDatetimeEx& datetime) noexcept
//{
//	std::cout
//		<< '\n'
//		<< datetime.datetimeStr(
//			VDate::Format::STANDARD,
//			VDate::Layout::M_D_YYYY,
//			VTimeEx::Format::STANDARD,
//			VTimeEx::Layout::H_M_S_P
//		)
//		<< std::endl;
//}

void dateOut(const VDate& date) noexcept
{
	std::cout
		<< '\n'
		<< date.dateStr(
			VDate::Format::STANDARD,
			VDate::Layout::M_D_YYYY
		)
		<< std::endl;
}

void timeOut(const VTimeEx& time) noexcept
{
	std::cout
		<< '\n'
		<< time.timeStr(
			VTimeEx::Format::STANDARD,
			VTimeEx::Layout::H_M_S_P
		)
		<< std::endl;
}

void timeOut(const VTime& time) noexcept
{
	std::cout
		<< '\n'
		<< time.timeStr(
			VTime::Format::STANDARD,
			VTime::Layout::H_M_S_P
		)
		<< std::endl;
}



int main(size_t argc, char* argv[])
{
	// Simply Datetime r4.v0
	ProjectInfoOut();

	VDatetimeEx nowSnapshot{ std::chrono::system_clock::now() };
	std::cout << "\nNow: "
		<< nowSnapshot.datetimeStr(VDate::Format::STANDARD)
		<< std::endl;

	// Project creation date: June 28th, 2024
	VDatetimeEx creationDate{ VDate{ 2024Ui16, 6Ui16, 28Ui16 } , VTimeEx{} };

	std::cout << "Elapsed dev time: "
		//<< creationDate.until(nowSnapshot) << std::endl
		<< "\n\n\nCONSOLE DEBUG:"
		<< std::endl;

	// DO NOT DELETE ABOVE



	//\\//

	VDatetimeEx::JDN dateJDN{ 2460729.5 };//2460729.5 (February 23, 2025)

	VDatetimeEx demo{ dateJDN };

	std::cout << '\n'
		<< demo.dayOfWeek() << ", "
		<< demo.monthTitle() << " " << (int)demo.day() << ", "
		<< demo.year() << '\n'
		<< demo.time().timeStr(VTimeEx::STANDARD, VTimeEx::H_M_S_P) << '\n'
		<< "Datetime: " << demo << '\n'
		<< "Julian Day Number: " << std::setprecision(17)
		<< demo.toJulianDayNumber() << '\n'
		<< std::endl;

	std::cout << '\n'
		<< "JDN provided: "
		<< std::setprecision(17) << dateJDN
		<< "\nJDN assumed: "
		<< std::setprecision(17) << demo.toJulianDayNumber()
		<< std::endl;

	//\\//



	// Ensure lossless conversion with VTime family JDN
	//VTimeEx t1{ (double).5208333335 };
	//VTimeEx t2{ (uint16_t)15Ui16, (uint16_t)30Ui16 };

	//std::cout << "\nTime 1: "
	//	<< t1.timeStr(VTimeEx::Format::STANDARD, VTimeEx::Layout::H_M_S_P)
	//	<< "\nJDN: " << t1.toJulianDayNumber()
	//	<< std::endl;

	//std::cout << "\nTime 2: "
	//	<< t2.timeStr(VTimeEx::Format::STANDARD, VTimeEx::Layout::H_M_S_P)
	//	<< "\nJDN: " << t2.toJulianDayNumber()
	//	<< std::endl;

	//std::cout << "\nTests:"
	//	<< "\nt1 until t2 (hrs): " << (long int)t1.hoursUntil(t2) << " hrs"
	//	<< "\nt1 until t2 (mins): " << (long int)t1.minutesUntil(t2) << " mins"
	//	<< "\nt1 until t2 (secs): " << (long int)t1.secondsUntil(t2) << " secs"
	//	<< "\nt1 until t2 (ms): " << (long long int)t1.msUntil(t2) << " ms"
	//	<< std::endl;

	//VTime tester{ (double)0.5 };
	//VTimeEx tester2{ tester };
	//tester.displace(VDuration{ 0, 0, 0, 3 });

	//std::cout << '\n' << tester.timeStr(VTime::Layout::H_M_S_P, VTime::Format::STANDARD) << std::endl;
	//std::cout << '\n' << tester2.timeStr(VTimeEx::Layout::H_M_S_P, VTimeEx::Format::STANDARD) << std::endl;

	return NULL;
}
